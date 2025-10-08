#include "include.h"
#include "CSV/CSVLoader.h"
#include "MainEditor/ProjectRoot.h"
#include <filesystem>

using namespace GoDCSV;

using LoadedCSVData = std::pair<std::vector<std::string>, std::vector<json>>;

LoadedCSVData CSVLoader::TryLoadCSV(const std::string& CSVFileName)
{
	fs::path CSVFilePath = GetCSVFileDir() / CSVFileName;
	CSVFilePath += ".csv";

	ICLogger::Debug("Attempting to load CSV File {}.csv at {}", CSVFileName, CSVFilePath.string());

	if (!std::filesystem::exists(CSVFilePath))
	{
		// CSV file does not exist, loading fails.
		ICLogger::Error("CSV file not found at path {}", CSVFilePath.string());
		throw std::exception(std::format("CSV file {} does not exist, did you decode it using the GoD tool?", CSVFileName).c_str());
	}

	std::shared_ptr<csv::CSVReader> ItemCSVReader;
	csv::CSVFormat ItemCSVFormat;

	// GoD tool files are comma ',' separated,
	// and the header row is always the first row.
	// However, the quoting scheme is strange and inconsistent,
	// so we need to handle commas escaped with quotes manually.
	// This means that we disable quotes for the csv reader, and keep
	// rows with variable columns. We will then consolidate those
	// rows with variable columns in ProcessRow.
	ItemCSVFormat.delimiter(',')
		.header_row(0)
		.quote(false)
		.variable_columns(csv::VariableColumnPolicy::KEEP);

	std::vector<std::string> HeaderRow;
	std::vector<json> DataRows;

	try {
		
		// This will perform the initial parsing of the CSV file, generate the header row,
		// and allow us to access individual rows of the CSV file.
		ItemCSVReader = std::make_shared<csv::CSVReader>(CSVFilePath.string(), ItemCSVFormat);

		// The header row is the same as the CSV's column names.
		HeaderRow = ItemCSVReader->get_col_names();

		
		// Process each row individually and add it to the data rows in sequence.
		// If processing for any row fails it will throw.
		int32_t RowNum = 1;
		for (csv::CSVRow& Row : *ItemCSVReader) {
			json NewRow = ProcessRow(Row, HeaderRow, RowNum);
			DataRows.push_back(NewRow);
			RowNum++;
		}
	}
	catch (const std::runtime_error& e)
	{
		ICLogger::Error("Error Reading CSV File {}: {}", CSVFileName, e.what());
		throw std::exception("CSV file {} could not be parsed, the file may not be a valid CSV file.");
	}

	// If no exceptions occurred then the CSV file was loaded successfully.
	ICLogger::Debug("CSV file {}.csv loaded successfully, Num Columns: {}, Num Rows: {}", CSVFileName, HeaderRow.size(), DataRows.size());

	return LoadedCSVData{ HeaderRow, DataRows };
}

void CSVLoader::TrySaveCSV(const std::string& CSVFileName, LoadedCSVData CSVData)
{
	fs::path CSVFilePath = GetCSVFileDir() / CSVFileName;
	CSVFilePath += ".csv";

	ICLogger::Debug("Attempting to save CSV File {}.csv at {}", CSVFileName, CSVFilePath.string());

	auto& HeaderRow = CSVData.first;
	auto& DataRows = CSVData.second;

	// This delim writer will make a CSV file delimited by commas. It will use "~" as the
	// quote character, but quotes should never actually be used.
	std::ofstream CSVStream(CSVFilePath);
	csv::DelimWriter<std::ofstream, ',', '~', true> CSVWriter(CSVStream);

	if (CSVStream.fail())
	{
		throw std::exception(std::format("Error saving CSV file {}.csv, do you have permission to write to this file?", CSVFileName).c_str());
	}

	// First write the header array
	CSVWriter << HeaderRow;

	// Then write in each row
	// The json data is stored in alphabetical order, not in key order, so we need to 
	// iterate through individual fields and put it back in order using the header array.
	for (int32_t i = 0; i < DataRows.size(); i++)
	{

		const json& RowJsonData = DataRows.at(i);

		std::vector<std::string> RowFields;
		RowFields.reserve(HeaderRow.size());

		// Push each field in header array order to RowFields
		for (int32_t j = 0; j < HeaderRow.size(); j++)
		{
			const std::string FieldValueAtKey = RowJsonData[HeaderRow.at(j)];
			RowFields.push_back(FieldValueAtKey);
		}

		// Write this data row.
		CSVWriter << RowFields;
	}

	/** If no exceptions occurred the CSV file saved successfully */
	ICLogger::Debug("CSV file {}.csv saved successfully", CSVFileName);
}


fs::path GoDCSV::CSVLoader::GetCSVFileDir()
{
	fs::path CSVFileDir;

	CSVFileDir = ProjectRoot::Get()->GetProjectRootPath();

	CSVFileDir /= "Reference";
	CSVFileDir /= "CSV Data";

	return CSVFileDir;
}

json CSVLoader::ProcessRow(csv::CSVRow& Row, std::vector<std::string> HeaderRow, const int32_t RowNum)
{
	json NextRow;
	int32_t CurrentField = 0;

	// All rows in the CSV file should have the same number of fields as the header row.
	// If a row has more fields than the header row, this might indicate that there were
	// commas in quoted strings that should have been escaped.
	if (Row.size() != HeaderRow.size())
	{
		// The above case is only true if the Row has more fields than the Header.
		// If the Row has less fields, then the CSV file is not valid.
		if (Row.size() < HeaderRow.size())
		{
			throw std::exception(std::format("Row {} has too few fields. CSV file is invalid", RowNum).c_str());
		}

		// Otherwise the row is bigger than the header, there should be 1 or more quoted strings with commas.
		ICLogger::Trace("Row {} has too many fields, there could be a quoted string with a comma.", RowNum);

		// This will concatenate
		FixEscapedCommasInRow(Row, HeaderRow, RowNum, NextRow, CurrentField);

	}
	else 
	{
		// If row is the correct length, just add all its
		// fields to the NextRow.
		for (csv::CSVField& field : Row)
		{
			std::string FieldData = field.get<>();

			// Convert this field to UTF-8 if needed
			ConvertFieldToUTF8(FieldData);

			NextRow[HeaderRow.at(CurrentField)] = FieldData;
			CurrentField++;
		}
	}

	return NextRow;
}

void CSVLoader::FixEscapedCommasInRow(csv::CSVRow& Row, std::vector<std::string> HeaderRow, const int32_t RowNum, json& OutNextRow, int32_t& OutCurrentField)
{
	// Check each individual field for quotes. If any field has an odd number of quotes, that
	// means the final quote was never finished, which in turn indicates that the next field
	// was supposed to be part of this field, and this is a string with a comma.
	// Example:
	// Field 1: "This is a,
	// Field 2: string with a comma"
	// The original field was "This is a, string with a comma", but it was
	// broken up into two fields by the parser, since Field 1 has an odd
	// number of quotes, Field 2 is the other half of the field.
	int32_t RowKey = 0;
	for (auto FieldItr = Row.begin(); FieldItr != Row.end(); FieldItr++)
	{
		csv::CSVField Field = *FieldItr;
		std::string PotentialQuoteData = Field.get<>();
		ICLogger::Trace("Checking field [{}]: {}", HeaderRow.at(RowKey), PotentialQuoteData);
		RowKey++;

		// Count the number of quotes in the field.
		int32_t NumQuote = CountQuoteOccurrences(PotentialQuoteData);

		// If the num quotes is odd (and not zero) then we know this is a string that was cut off due to a comma
		if (NumQuote % 2 != 0 && NumQuote != 0)
		{
			ICLogger::Trace("Found field with mismatched quotes: {}", PotentialQuoteData);

			// Keep concatenating fields until the num quotes is even again.
			// This is needed because we could have a field with two escaped commas, which
			// would look like this:
			// Field 1: "This is a,
			// Field 2: field with,
			// Field 3: two commas"
			// The intended field is "This is a, field with, two commas", but if we only
			// concatenate Field 1 and 2, we won't achieve that result. However, after
			// concatenating those two fields, the combined field will still only have 1
			// quote, so we can check for this case by re-checking the number of quotes
			// and continuing to concatenate until we have an even number of quotes.
			while (NumQuote % 2 != 0 && NumQuote != 0)
			{
				// Get the next quote and combine them.
				FieldItr++;
				csv::CSVField NextField = *FieldItr;
				std::string NextFieldData = NextField.get<>();

				ICLogger::Trace("Concatinating next field: {}", NextFieldData);

				// Add back in the comma that was removed when the fields were separated
				PotentialQuoteData += ",";
				PotentialQuoteData += NextFieldData;

				ICLogger::Trace("Field concatinated: {}", PotentialQuoteData);

				// If this is the full original field, 
				// then the occurrences of quote will be even, 
				// if not then we need to concatenate more fields.
				NumQuote = CountQuoteOccurrences(PotentialQuoteData);
			}

			ICLogger::Trace("Field with escaped comma(s) fixed: {}", PotentialQuoteData);
		}

		// Convert string to UTF-8 (if needed) before adding it
		ConvertFieldToUTF8(PotentialQuoteData);

		// Add the field to the row Json.
		OutNextRow[HeaderRow.at(OutCurrentField)] = PotentialQuoteData;
		OutCurrentField++;
	}
}

int32_t CSVLoader::CountQuoteOccurrences(const std::string& PotentialQuoteString)
{
	// count occurrences of " character
	int32_t NumQuote = 0;
	for (auto character : PotentialQuoteString)
	{
		if (character == '"' || character == '\"')
		{
			NumQuote++;
		}
	}

	return NumQuote;
}

void CSVLoader::ConvertFieldToUTF8(std::string& FieldDataToConvert)
{
	// This may not actually be needed.

	// Check if this is Nidoran M/F
	//if (FieldDataToConvert.find("NIDORAN") != std::string::npos)
	//{
	//	// Convert this field to UTF-8, as Nidoran's have the male/female character
	//	// in their field data.
	//	std::stringstream Stream;
	//	Stream.imbue(std::locale("en_US.UTF-8"));
	//	Stream << FieldDataToConvert;
	//	Stream >> FieldDataToConvert;
	//}
}
