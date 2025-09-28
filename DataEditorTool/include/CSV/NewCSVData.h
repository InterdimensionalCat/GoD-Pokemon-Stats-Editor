#pragma once

namespace GoDCSV
{

	class CSVLoader;
	class CSVHeader;
	class CSVRow;

	class NewCSVData
	{
	public:

		NewCSVData(const std::string& CSVFileName);

		/** Load the CSV file with this filename via the CSVLoader */
		void Init();

		void InitFromLoadedData(std::pair<std::vector<std::string>, std::vector<json>> InLoadedData);

		/** Save this CSV file to disk. Return a failure reason if saving fails. */
		std::string Save();

		/**
		 * Get a read only pointer to a row. Useful if we want to get
		 * Multiple fields from the same row.
		 */
		std::shared_ptr<const CSVRow> GetRowAtIndex(const uint32_t RowIndex);

		/**
		 * Get a read only pointer to a row. Useful if we want to get
		 * Multiple fields from the same row.
		 */
		std::shared_ptr<const CSVRow> GetRowByName(const std::string& RowName);

		/**
		 * Get a read only pointer to the header row. Useful if we want to
		 * search a CSV file for particular column names.
		 */
		std::shared_ptr<const CSVHeader> GetHeaderRow() const;

		/** Get all fields in a column. */
		std::vector<bool> GetBoolColumn(const std::string& ColumnName);
		std::vector<float> GetFloatColumn(const std::string& ColumnName);
		std::vector<int32_t> GetIntColumn(const std::string& ColumnName);
		std::vector<std::string> GetStringColumn(const std::string& ColumnName);

		/**
		 * Name does not include ".csv" so
		 * "Pokemon Stats.csv" should be set to
		 * "Pokemon Stats"
		 */
		std::string GetName() const;

		/**
		 * Modify the field at the supplied Column/Row to match the supplied Value.
		 * This will mark this CSV file as modified. Fields may only be set to
		 * bool, float, int32_t, or std::string values.
		 */
		void SetField(const std::string& ColumnName, const int32_t RowIndex, const std::variant<bool, float, int32_t, std::string> NewValue);

		bool HasCSVFileBeenModified() const;

		bool DoesCSVFileExist() const;

		bool IsCSVFileLoaded() const;

	private:

		std::string FileName;

		std::shared_ptr<CSVHeader> HeaderRow;

		std::vector<std::shared_ptr<CSVRow>> DataRows;

		bool bModified = false;

		bool bLoaded = false;
	};
}