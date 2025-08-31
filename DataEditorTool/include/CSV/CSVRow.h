/*****************************************************************//**
 * \file   CSVRow.h
 * \brief  Contains a vector of CSV fields for this row
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/

#pragma once

namespace GoDCSV
{
	class CSVRow
	{
	public:

		CSVRow(const json& InRowFields);

		std::string GetName() const;

		bool GetBoolAtColumn(const std::string& ColumnName) const;
		float GetFloatAtColumn(const std::string& ColumnName) const;
		int32_t GetIntAtColumn(const std::string& ColumnName) const;
		std::string GetStringAtColumn(const std::string& ColumnName) const;

		void SetBoolAtColumn(const std::string& ColumnName, const bool NewValue);
		void SetFloatAtColumn(const std::string& ColumnName, const float NewValue);
		void SetIntAtColumn(const std::string& ColumnName, const int32_t NewValue);
		void SetStringAtColumn(const std::string& ColumnName, const std::string& NewValue);

		const json& GetRowJson() const;

	private:

		json RowFields;

	};
}