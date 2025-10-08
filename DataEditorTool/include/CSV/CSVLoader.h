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
		 */
		static LoadedCSVData TryLoadCSV(const std::string& CSVFileName);

		/**
		 * Attempt to save the supplied CSV data to a CSV file with the specified name.
		 * This will throw if saving fails.
		 * 
		 * The supplied CSV data must be in the format:
		 * {header list vector}, {rows json vector}
		 */
		static void TrySaveCSV(const std::string& CSVFileName, LoadedCSVData CSVData);

		/** Get the directory where CSV files are stored for the current project root. */
		static std::filesystem::path GetCSVFileDir();

	private:

		/**
		 * Process a single row from a CSV file and convert it to a JSON object.
		 * This will throw if the row is malformed.
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
		 */
		static void FixEscapedCommasInRow(csv::CSVRow& Row, std::vector<std::string> HeaderRow, const int32_t RowNum, json& OutNextRow, int32_t& OutCurrentField);

		/**
		 * Count the number of quote characters in the supplied string.
		 */
		static int32_t CountQuoteOccurrences(const std::string& PotentialQuoteString);

		/**
		 * Convert the supplied field data to UTF-8 if it is not already.
		 * This will modify the supplied string in place.
		 */
		static void ConvertFieldToUTF8(std::string& FieldDataToConvert);
	};
}
