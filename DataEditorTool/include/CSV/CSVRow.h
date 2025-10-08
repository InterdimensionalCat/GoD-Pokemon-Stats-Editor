/*****************************************************************//**
 * \file   CSVRow.h
 * \brief  Data rows for a CSVData file. Contains a json object with key/value pairs
 * corresponding to column names and field values.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

namespace GoDCSV
{
	/**
	 * \brief  Data rows for a CSVData file. Contains a json object with 
	 * key/value pairs corresponding to column names and field values.
	 */
	class CSVRow
	{

	public:

		/**
		 * Construct a CSVRow from the supplied json object.
		 * This json object should contain key/value pairs
		 * corresponding to column names and field values.
		 */
		CSVRow(const json& InRowFields);

		/**
		 * Get the value of the "Entry Name" column for this row.
		 * This is used to identify rows by name.
		 * 
		 * This will throw if the "Entry Name" column does not exist
		 * or is not a string.
		 */
		std::string GetName() const;

		/** Get the value at the specified column as a bool. */
		bool GetBoolAtColumn(const std::string& ColumnName) const;

		/** Get the value at the specified column as a float. */
		float GetFloatAtColumn(const std::string& ColumnName) const;

		/** Get the value at the specified column as an int. */
		int32_t GetIntAtColumn(const std::string& ColumnName) const;

		/** Get the value at the specified column as a string. */
		std::string GetStringAtColumn(const std::string& ColumnName) const;

		/** Set the value at the specified column to the new bool value. */
		void SetBoolAtColumn(const std::string& ColumnName, const bool NewValue);

		/** Set the value at the specified column to the new float value. */
		void SetFloatAtColumn(const std::string& ColumnName, const float NewValue);

		/** Set the value at the specified column to the new int value. */
		void SetIntAtColumn(const std::string& ColumnName, const int32_t NewValue);

		/** Set the value at the specified column to the new string value. */
		void SetStringAtColumn(const std::string& ColumnName, const std::string& NewValue);

		/** Get the raw json object representing this row's fields. */
		const json& GetRowJson() const;

	private:

		/** The json object representing this row's fields. */
		json RowFields;

	};
}