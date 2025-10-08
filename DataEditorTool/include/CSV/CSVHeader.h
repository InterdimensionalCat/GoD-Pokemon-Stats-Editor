/*****************************************************************//**
 * \file   CSVHeader.h
 * \brief  Header row for a CSVData file. Contains a vector of CSV Header fields
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

namespace GoDCSV
{
	/** \brief  Header row for a CSVData file. Contains a vector of CSV Header fields */
	class CSVHeader
	{
	public:

		/**
		 * Construct a CSVHeader from the supplied column names.
		 */
		CSVHeader(const std::vector<std::string>& InColumnNames);

		/**
		 * Get the column name at the supplied index.
		 * This will throw if the index is out of range.
		 */
		std::string GetColumnName(const int32_t ColumnIndex) const;

		/**
		 * Get the index of the supplied column name.
		 * Returns -1 if the column name could not be found.
		 */
		int32_t GetIndexOfColumn(const std::string& ColumnName) const;

		/**
		 * Get the column names as a vector of strings.
		 */
		const std::vector<std::string>& GetColumnNamesArray() const;

	private:

		/** The column names in this header row. */
		const std::vector<std::string> ColumnNames;

	};
}

