/*****************************************************************//**
 * \file   CSVHeader.h
 * \brief  Contans a vector of CSV Header fields
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

namespace GoDCSV
{
	class CSVHeader
	{
	public:

		CSVHeader(const std::vector<std::string>& InColumnNames);

		std::string GetColumnName(const int32_t ColumnIndex) const;

		int32_t GetIndexOfColumn(const std::string& ColumnName) const;

		const std::vector<std::string>& GetColumnNamesArray() const;

	private:

		const std::vector<std::string> ColumnNames;

	};
}

