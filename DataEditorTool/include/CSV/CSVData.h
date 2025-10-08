/*****************************************************************//**
 * \file   CSVData.h
 * \brief  Class representing a CSV file of the format used by the GoD tool. 
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

namespace GoDCSV
{

	class CSVLoader;
	class CSVHeader;
	class CSVRow;

	/**
	 * \brief Class representing a CSV file of the format used by the GoD tool. 
	 * 
	 * This class allows reading and writing of CSV files
	 * with rows represented as JSON objects, and columns
	 * represented as strings in a header row.
	 * 
	 * Each row must have a unique "Entry Name" field which
	 * is used to identify rows by name.
	 * 
	 * Fields in rows may be bool, float, int32_t, or std::string values.
	 */
	class CSVData
	{
	public:

		/**
		 * Construct a CSV file with this file name.
		 * 
		 * This name should not include the ".csv" extension, and
		 * should correspond to a file in the CSV data directory
		 * for the current root, or be a static CSV file. 
		 * However, these conditions will not be checked for
		 * until the CSV File is initialized
		 * 
		 * \param CSVFileName The name of the CSV file, without the ".csv" extension.
		 */
		CSVData(const std::string& CSVFileName);

		/**
		 * Load the CSV file with this filename via the CSVLoader.
		 * 
		 * This will fail if CSVLoader::TryLoadCSV fails for this filename.
		 */
		void Init();

		/**
		 * Init CSV file from already loaded data the format.
		 *  
		 * {header list vector}, {rows json vector}
		 * 
		 * \param InLoadedData The loaded data to initialize this CSV file from.
		 */
		void InitFromLoadedData(std::pair<std::vector<std::string>, std::vector<json>> InLoadedData);

		/**
		 * Save this CSV file to disk. Return a failure reason if saving fails.
		 * 
		 * \return An empty string if saving succeeded, or a failure reason if saving failed.
		 */
		std::string Save();

		/**
		 * Get a read only pointer to a row. Useful if we want to get
		 * Multiple fields from the same row.
		 * 
		 * \param RowIndex The index of the row to get.
		 * \return A read-only shared pointer to the row at the specified index.
		 */
		std::shared_ptr<const CSVRow> GetRowAtIndex(const uint32_t RowIndex);

		/**
		 * Get a read only pointer to a row. Useful if we want to get
		 * Multiple fields from the same row.
		 * 
		 * \param RowName The name of the row to get, this is the value in the "Entry Name" column.
		 * \return A read-only shared pointer to the row with the specified name.
		 */
		std::shared_ptr<const CSVRow> GetRowByName(const std::string& RowName);

		/**
		 * Get a read only pointer to the header row. Useful if we want to
		 * search a CSV file for particular column names.
		 * 
		 * \return A read-only shared pointer to the header row.
		 */
		std::shared_ptr<const CSVHeader> GetHeaderRow() const;

		/**
		 * Get all fields in a column as bools.
		 * 
		 * \param ColumnName The name of the column to get.
		 * \return A vector of bools representing the values in the specified column.
		 */
		std::vector<bool> GetBoolColumn(const std::string& ColumnName);

		/**
		 * Get all fields in a column as floats.
		 * 
		 * \param ColumnName The name of the column to get.
		 * \return A vector of floats representing the values in the specified column.
		 */
		std::vector<float> GetFloatColumn(const std::string& ColumnName);

		/**
		 * Get all fields in a column as ints.
		 * 
		 * \param ColumnName The name of the column to get.
		 * \return A vector of int32_t representing the values in the specified column.
		 */
		std::vector<int32_t> GetIntColumn(const std::string& ColumnName);

		/**
		 * Get all fields in a column as strings.
		 * 
		 * \param ColumnName The name of the column to get.
		 * \return A vector of strings representing the values in the specified column.
		 */
		std::vector<std::string> GetStringColumn(const std::string& ColumnName);

		/**
		 * Returns the file name of this CSV file
		 * set at construction time.
		 * Name does not include ".csv" so
		 * "Pokemon Stats.csv" should be set to
		 * "Pokemon Stats"
		 * 
		 * \return The file name of this CSV file.
		 */
		std::string GetName() const;

		/**
		 * Modify the field at the supplied Column/Row to match the supplied Value.
		 * This will mark this CSV file as modified. Fields may only be set to
		 * bool, float, int32_t, or std::string values.
		 * 
		 * \param ColumnName The name of the column to modify.
		 * \param RowIndex The index of the row to modify.
		 * \param NewValue The new value to set the field to. May be bool, float, int32_t, or std::string.
		 */
		void SetField(const std::string& ColumnName, const int32_t RowIndex, const std::variant<bool, float, int32_t, std::string> NewValue);

		/**
		 * Has this CSV file been modified since it was last loaded or saved?
		 * 
		 * \return True if this CSV file has been modified, false otherwise.
		 */
		bool HasCSVFileBeenModified() const;

		/**
		 * Does the CSV file for this CSVData exist on disk?
		 * 
		 * \return True if the CSV file exists, false otherwise.
		 */
		bool DoesCSVFileExist() const;

		/**
		 * Is this CSV file currently loaded?
		 * 
		 * \return True if this CSV file is loaded, false otherwise.
		 */
		bool IsCSVFileLoaded() const;

	private:

		/** The file name for this CSV file */
		std::string FileName;

		/** The Header Row for this CSV file */
		std::shared_ptr<CSVHeader> HeaderRow;

		/** The data rows for this CSV file */
		std::vector<std::shared_ptr<CSVRow>> DataRows;

		/** Has this CSV file been modified since it was last loaded or saved? */
		bool bModified = false;

		/** Is this CSV file currently loaded? */
		bool bLoaded = false;
	};
}