#pragma once

namespace GoDCSV
{
	class NewCSVData;

	/** CSVType type must either be a NewCSVData or derive from NewCSVData */
	template <typename CSVType>
	concept NewCSVDataOrSubclass =
		std::same_as<CSVType, NewCSVData> ||
		std::derived_from<CSVType, NewCSVData>;

	class CSVDatabase
	{

	public:

		CSVDatabase() = default;

		/**
		 * Search for all CSV files in this project root and
		 * add them to the database, but don't load them.
		 * 
		 * Clears any previously loaded CSV data if another project root
		 * Was loaded beforehand.
		 */
		void OnProjectRootPathSet();

		/**
		 * Get the CSV file with the specified name from the Database
		 * and cast it to the specified CSV data type.
		 */
		template <NewCSVDataOrSubclass CSVType>
		std::shared_ptr<CSVType> GetCSVFile(const std::string& CSVFileName)
		{
			return std::dynamic_pointer_cast<CSVType>(CSVDatabaseMap.at(CSVFileName));
		}

		/**
		* Get the CSV file with the specified name from the Database.
		* No need to cast if we are just trying to get a NewCSVData
		* typed CSV file.
		*/
		template <>
		std::shared_ptr<NewCSVData> GetCSVFile<NewCSVData>(const std::string& CSVFileName)
		{
			return CSVDatabaseMap.at(CSVFileName);
		}

		/** Return whether or not the current root contains all the given CSV files. */
		bool RootContainsAllCSVFiles(const std::vector<std::string>& CSVFileNames) const;

		/** Get a list of all CSV files that were marked as modified since the last save. */
		std::vector<std::string> GetAllModifiedCSVFileNames();

		/** Returns true if any open CSV files are marked as modified */
		bool AreAnyCSVFilesModified();

		/**
		 * Returns true if a CSV file with the specified name is in the database,
		 * weather loaded or not.
		 */
		bool IsCSVFileInDatabase(const std::string& CSVFileName) const;

		/**
		 * Save all CSV files in the supplied vector. Return any CSV file names that fail to save, along with the failure reason
		 */
		std::vector<std::pair<std::string, std::string>> SaveSelectedCSVFiles(const std::vector<std::string>& SelectedCSVFiles);

		/**
		 * Save all CSV files marked as modified. Return any CSV file names that fail to save, along with the failure reason
		 */
		std::vector<std::pair<std::string, std::string>> SaveAllModifiedCSVFiles();

		/**
		 * Clear the database of all CSV files, both loaded and unloaded.
		 */
		void ClearDatabase();

		void LoadCSVFile(const std::string& CSVFileName);

		/** DEBUG COMMANDS: USE FOR TESTING ONLY */
		
		/** Load every CSV file in the database. */
		void LoadAllCSVFiles();

		/** Save every CSV file in the database. */
		void SaveAllCSVFiles();

		std::map<std::string, std::shared_ptr<NewCSVData>>& GetDatabaseMap();

		/** DEBUG COMMAND END */

		/** Get a pointer to the Database from the DataEditorInstance */
		static std::shared_ptr<CSVDatabase> Get();

	private:

		/** Database of all loaded CSV files. */
		std::map<std::string, std::shared_ptr<NewCSVData>> CSVDatabaseMap;
	};
}

