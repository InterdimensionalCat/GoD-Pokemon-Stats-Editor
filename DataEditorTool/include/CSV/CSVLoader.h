#pragma once

namespace GoDCSV
{
	using LoadedCSVData = std::pair<std::vector<std::string>, std::vector<json>>;

	class CSVLoader
	{

	public:

		static LoadedCSVData TryLoadCSV(const std::string& CSVFileName);

		static void TrySaveCSV(const std::string& CSVFileName, LoadedCSVData CSVData);

		static std::filesystem::path GetCSVFileDir();

	private:

		static json ProcessRow(csv::CSVRow& Row, std::vector<std::string> HeaderRow, const int32_t RowNum);

		static void FixEscapedCommasInRow(csv::CSVRow& Row, std::vector<std::string> HeaderRow, const int32_t RowNum, json& OutNextRow, int32_t& OutCurrentField);

		static int32_t CountQuoteOccurances(const std::string& PotentialQuoteString);

		static void ConvertFieldToUTF8(std::string& FieldDataToConvert);


		// TODO: make a function to remove quote character from fields that
		// have a comma in them
	};
}
