/*****************************************************************//**
 * \file   CSVLoader.h
 * \brief  Helper class for loading and saving CSV files in the GoD tool format.
 *
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

namespace GoDCSV
{
	using LoadedCSVData = std::pair<std::vector<std::string>, std::vector<json>>;

	/** \brief  Helper class for loading and saving CSV files in the GoD tool format. */
	class CSVLoader
	{

	public:

		/**
		 * Attempt to load the CSV file with the specified name from disk.
		 * This will throw if loading fails.
		 * 
		 * Returns a pair of:
		 * {header list vector}, {rows json vector}
		 * 
		 * \param CSVFileName The name of the CSV file to load, without the ".csv" extension.
		 * \return A pair of {header list vector}, {rows json vector}
		 */
		static LoadedCSVData TryLoadCSV(const std::string& CSVFileName);

		/**
		 * Attempt to save the supplied CSV data to a CSV file with the specified name.
		 * This will throw if saving fails.
		 * 
		 * The supplied CSV data must be in the format:
		 * {header list vector}, {rows json vector}
		 * 
		 * \param CSVFileName The name of the CSV file to save, without the ".csv" extension.
		 * \param CSVData The CSV data to save.
		 */
		static void TrySaveCSV(const std::string& CSVFileName, LoadedCSVData CSVData);

		/**
		 * Get the directory where CSV files are stored for the current project root.
		 * 
		 * \return The directory where CSV files are stored for the current project root.
		 */
		static std::filesystem::path GetCSVFileDir();

	private:

		/**
		 * Process a single row from a CSV file and convert it to a JSON object.
		 * This will throw if the row is malformed.
		 * 
		 * \param Row The CSV row to process.
		 * \param HeaderRow The header row for the CSV file.
		 * \param RowNum The row number of the row being processed, for error reporting.
		 * \return A JSON object representing the row.
		 */
		static json ProcessRow(csv::CSVRow& Row, std::vector<std::string> HeaderRow, const int32_t RowNum);

		/**
		 * Fix fields in a row that have escaped commas in them.
		 * This will modify the supplied Row in place.
		 * 
		 * This is necessary because the GoD tool uses a strange
		 * and inconsistent quoting scheme for fields with commas
		 * in them.
		 * 
		 * This function will attempt to fix these issues by
		 * counting quote characters and merging fields as necessary.
		 * 
		 * \param Row The CSV row to fix.
		 * \param HeaderRow The header row for the CSV file.
		 * \param RowNum The row number of the row being processed, for error reporting.
		 * \param OutNextRow The JSON object to populate with the fixed row data.
		 * \param OutCurrentField The current field index being processed, will be updated as fields are added to OutNextRow.
		 */
		static void FixEscapedCommasInRow(csv::CSVRow& Row, std::vector<std::string> HeaderRow, const int32_t RowNum, json& OutNextRow, int32_t& OutCurrentField);

		/**
		 * Count the number of quote characters in the supplied string.
		 * 
		 * \param PotentialQuoteString The string to count quote characters in.
		 * \return The number of quote characters in the string.
		 */
		static int32_t CountQuoteOccurrences(const std::string& PotentialQuoteString);

		/**
		 * Convert the supplied field data to UTF-8 if it is not already.
		 * This will modify the supplied string in place.
		 * 
		 * \param FieldDataToConvert The field data to convert to UTF-8.
		 */
		static void ConvertFieldToUTF8(std::string& FieldDataToConvert);
	};
}
