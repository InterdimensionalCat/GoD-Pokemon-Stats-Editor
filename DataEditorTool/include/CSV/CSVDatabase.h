/*****************************************************************//**
 * \file   CSVDatabase.h
 * \brief  Database containing all CSV files in the current project root.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

namespace GoDCSV
{
	class CSVData;

	/**
	 * \brief  Database containing all CSV files in the current project root.
	 */
	class CSVDatabase
	{
		using LoadedCSVData = std::pair<std::vector<std::string>, std::vector<json>>;
		
	public:

		/**
		 * Construct a CSVDatabase.
		 * This does not load or find any CSV files
		 * until OnProjectRootPathSet is called.
		 */
		CSVDatabase() = default;

		/**
		 * Search for all CSV files in this project root and
		 * add them to the database, but don't load them.
		 * 
		 * Clears any previously loaded CSV data if another project root
		 * Was loaded beforehand.
		 */
		void OnProjectRootPathSet();

		/** Load the hard-coded databases needed for the editor to function. */
		void LoadStaticDatabases();

		/**
		* Get the CSV file with the specified name from the Database.
		*/
		std::shared_ptr<CSVData> GetCSVFile(const std::string& CSVFileName);

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

		/**
		 * Load the CSV file with the specified name from disk into the database.
		 * If the file is already loaded, this will do nothing.
		 * If the file is not in the database, this will add it to the database
		 * and then load it.
		 */
		void LoadCSVFile(const std::string& CSVFileName);
		
		/**
		 * Load a CSV file from already loaded data, bypassing the CSVLoader.
		 * If the file is already loaded, this will do nothing.
		 * If the file is not in the database, this will add it to the database
		 * and then load it.
		 */
		void LoadCSVFileFromData(
			const std::string& CSVFileName,
			LoadedCSVData LoadedData
		);

		/** DEBUG COMMANDS: USE FOR TESTING ONLY */
		
		/** Load every CSV file in the database. */
		//void LoadAllCSVFiles();

		/** Save every CSV file in the database. */
		//void SaveAllCSVFiles();

		//std::map<std::string, std::shared_ptr<CSVData>>& GetDatabaseMap();

		/** DEBUG COMMAND END */

		/** Get a pointer to the Database from the DataEditorInstance */
		static std::shared_ptr<CSVDatabase> Get();

	private:

		/** Database of all loaded CSV files. */
		std::map<std::string, std::shared_ptr<CSVData>> CSVDatabaseMap;
	};
}

