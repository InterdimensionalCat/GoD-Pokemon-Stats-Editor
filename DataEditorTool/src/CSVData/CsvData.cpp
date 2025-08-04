#include "include.h"

#include "CSVData/CsvData.h"
#include "GoD-UI-Windows.h"

using namespace csv;

CSVData::CSVData()
{

}

bool CSVData::Init()
{
	std::cout << "Reading Csv file at " << Path.string() << "...\n";

	if (!std::filesystem::exists(Path))
	{
		// Return fail if path does not exist.
		std::cout << "Csv file does not exist: " << Path.string() << "\n";
		return false;
	}

	std::shared_ptr<CSVReader> ItemCSVReader;
	CSVFormat ItemCSVFormat;

	ItemCSVFormat.delimiter({ '\t', ',' })
		.header_row(0)
		.quote(false)
		.variable_columns(VariableColumnPolicy::KEEP);

	try {
		ItemCSVReader = std::make_shared<CSVReader>(Path.string(), ItemCSVFormat);

		HeaderArray = ItemCSVReader->get_col_names();

		for (CSVRow& row : *ItemCSVReader) {
			ProcessRow(row);
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cout << "Error reading Csv file: " << e.what() << "\n";
		return false;
	}

	std::cout << std::format("CSV data read, num Rows: {}", DataObject.size()) << "\n";

	return true;
}

void CSVData::ProcessRow(CSVRow& row)
{
	//std::cout << row.to_json() << std::endl;
	std::shared_ptr<json> NextRow = std::make_shared<json>();
	uint32_t currentField = 0;

	if (row.size() != HeaderArray.size())
	{
		std::cout << "Row is too large, there could be a string with a comma" << "\n";
		// if the row is bigger than the header, then there is a string with a comma in it
		for (auto FieldItr = row.begin(); FieldItr != row.end(); FieldItr++)
		{
			CSVField field = *FieldItr;
			std::string PotentialQuoteData = field.get<>();
			std::cout << "Checking field:" << PotentialQuoteData << "\n";

			// Count the number of quotes in the field.
			int32_t NumQuote = CountQuoteOccurances(PotentialQuoteData);

			// If the num quotes is odd (and not zero) then we know this is a string that was cut off due to a comma
			bool bFoundMismatchedQuotes = false;
			if (NumQuote % 2 != 0 && NumQuote != 0)
			{
				bFoundMismatchedQuotes = true;
				std::cout << "Found field with odd quotes: " << PotentialQuoteData << "\n";
			}
			// Keep concatinating fields until the num quotes is even again
			while (NumQuote % 2 != 0 && NumQuote != 0)
			{
				std::cout << "Concatinating next field..." << "\n";
				// Get the next quote and combine them.
				FieldItr++;
				CSVField NextField = *FieldItr;
				PotentialQuoteData += ",";
				PotentialQuoteData += NextField.get<>();

				std::cout << "Field concatinated: " << PotentialQuoteData << "\n";

				// If we have found the whole quote str, then the occurances of " will be even, if not there is more than 1 comma in this quote
				NumQuote = CountQuoteOccurances(PotentialQuoteData);
			}

			if (bFoundMismatchedQuotes)
			{
				std::cout << "Quote with comma(s) fixed: " << PotentialQuoteData << "\n";
			}

			// Check if this is Nidoran M/F
			if (PotentialQuoteData.find("NIDORAN") != std::string::npos)
			{
				std::stringstream Stream;
				Stream.imbue(std::locale("en_US.UTF-8"));
				Stream << PotentialQuoteData;
				Stream >> PotentialQuoteData;
			}

			(*NextRow)[(std::string)HeaderArray.at(currentField)] = PotentialQuoteData;
			currentField++;
		}
	}
	else {
		for (CSVField& field : row)
		{
			std::string FieldData = field.get<>();
			// Check if this is Nidoran M/F
			if (FieldData.find("NIDORAN") != std::string::npos)
			{
				std::stringstream Stream;
				Stream.imbue(std::locale("en_US.UTF-8"));
				Stream << FieldData;
				Stream >> FieldData;
			}

			(*NextRow)[(std::string)HeaderArray.at(currentField)] = field.get<>();
			currentField++;
		}
	}

	//std::cout << NextRow["Entry Name"] << "\n";

	DataObject.push_back(NextRow);
}

std::vector<std::string> CSVData::GetAllEntriesOfKey(const std::string& key, const bool bConvertFormat)
{
	std::vector<std::string> Entries;
	for (std::shared_ptr<json> row : DataObject) {
		std::string NextEntry = (*row)[key];

		if (bConvertFormat) {
			// convert from ["ENTRY"  - #] format to [ENTRY (#)] format

			// remove all " occurances
			NextEntry.erase(std::remove(NextEntry.begin(), NextEntry.end(), '\"'), NextEntry.end());
			std::size_t DashPos = NextEntry.find_last_of("-");
			if (DashPos == std::string::npos)
			{
				throw std::runtime_error("Data at Key does not require bConvertFormat.");
			}

			// Seperate into Text and number along the '-' character.
			std::string EntryText = NextEntry.substr(0, DashPos - 2);
			std::string EntryNumber = NextEntry.substr(DashPos + 2, NextEntry.length());

			// Re-format as [ENTRY (#)]
			std::string CorrectFormat = std::format("{} ({})", EntryText, EntryNumber);

			Entries.push_back(CorrectFormat);
		}
		else
		{
			Entries.push_back(NextEntry);
		}
	}

	return Entries;
}

std::string CSVData::GetStringAtKeyAndIndex(uint32_t index, const std::string& key)
{
	auto RowJson = DataObject.at(index);
	return (*RowJson)[key];
}

int32_t CSVData::GetIntAtKeyAndIndex(uint32_t index, const std::string& key)
{
	auto RowJson = DataObject.at(index);
	return (int32_t)stoi((std::string)(*RowJson)[key]);
}

bool CSVData::GetboolAtKeyAndIndex(uint32_t index, const std::string& key)
{
	auto RowJson = DataObject.at(index);
	std::string BoolStr = (*RowJson)[key];
	std::transform(BoolStr.begin(), BoolStr.end(), BoolStr.begin(), ::toupper);
	if (BoolStr == "TRUE")
	{
		return true;
	}

	if (BoolStr == "FALSE")
	{
		return false;
	}

	throw std::runtime_error("Value at key and index was not a bool");

	return false;
}

int32_t CSVData::CountQuoteOccurances(const std::string& PotentialQuoteString)
{
	// count occurances of " character
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

std::vector<std::shared_ptr<json>> CSVData::GetDataObject()
{
	return DataObject;
}

std::vector<std::string> CSVData::GetHeaderArray() const
{
	return HeaderArray;
}
