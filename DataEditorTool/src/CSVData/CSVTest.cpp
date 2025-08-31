#include "include.h"
#include "CSVData/CSVTest.h"

using namespace csv;

void TestCSV::Test()
{
	CSVFormat ItemCSVFormat;

	CSVFormat format;
	format.header_row(0)
		.trim({ '\t', ' ' })
		.delimiter(',');

	ItemCSVFormat.header_row(0)
		.delimiter({ ',' })
		.variable_columns(VariableColumnPolicy::KEEP);

	//std::string csv_string = "Pokemon,Level,Description\r\n"
	//	"Bulbasaur,100,\"Funny\"(0xA)\r\n"
	//	"Nidoran♂,55,\"Uses the \"male\" symbol\"(0xB)\r\n"
	//	"Medicham,1,\"Has, A delimiter in the description\"(0xC)\r\n";

	//std::string csv_string = "A,B,C\r\n" // Header row
	//	"123,\"234,345\",456\r\n";

	std::filesystem::path InPath = std::filesystem::current_path();

	InPath /= "TestIn.csv";

	//auto ItemCSVReader = parse(csv_string, ItemCSVFormat);
	auto ItemCSVReader = CSVReader(InPath.string(), ItemCSVFormat);

	std::vector<std::string> HeaderArray;
	HeaderArray = ItemCSVReader.get_col_names();
	std::vector<json> JsonRows;

	uint32_t currentField = 0;
	uint32_t CurrentRow = 0;
	json NextRow;

	std::stringstream my_json;

	for (CSVRow& row : ItemCSVReader) 
	{
		CurrentRow++;
		NextRow.clear();
		currentField = 0;

		my_json << row.to_json() << std::endl;
		my_json >> NextRow;

		//ICLogger::Warn("{}", row["Description"].get<std::string>());

		//for (CSVField& field : row)
		//{
		//	//std::string FieldData = field.get<>();
		//	//// Check if this is Nidoran M/F
		//	//if (FieldData.find("NIDORAN") != std::string::npos)
		//	//{
		//	//	std::stringstream Stream;
		//	//	Stream.imbue(std::locale("en_US.UTF-8"));
		//	//	Stream << FieldData;
		//	//	Stream >> FieldData;
		//	//}


		//	NextRow[HeaderArray.at(currentField)] = field.get<>();
		//	currentField++;
		//}

		ICLogger::Info("Row {}: {}", CurrentRow, NextRow.dump(4));
		JsonRows.push_back(NextRow);
	}


	std::filesystem::path Path = std::filesystem::current_path();

	Path /= "Test.csv";

	std::ofstream CSVStream(Path);
	DelimWriter<std::ofstream, ',', '~', true> CSVWriter(CSVStream);

	if (CSVStream.fail())
	{
		throw std::exception("Error saving Pokemon Stats.csv file, do you have permission to write to this file?");
	}

	// First write the header array
	CSVWriter << HeaderArray;

	// Then write in each row
	for (int32_t i = 0; i < JsonRows.size(); i++)
	{
		// The json data is stored in alphabetical order, not in key order, so we need to 
		// iterate through individual fields to put it back in order using the header array.
		json RowJsonData = JsonRows.at(i);

		std::vector<std::string> RowFields;
		RowFields.reserve(HeaderArray.size());

		for (int32_t j = 0; j < HeaderArray.size(); j++)
		{
			const std::string FieldValueAtKey = RowJsonData[HeaderArray.at(j)];
			//std::cout << FieldValueAtKey << "\n";
			RowFields.push_back(FieldValueAtKey);
		}

		CSVWriter << RowFields;
	}
}
