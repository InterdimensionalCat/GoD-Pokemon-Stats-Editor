#pragma once

class ParenthValueString;

class ColumnDatabase
{

public:

	/** Create a ColumnDatabase from an "Entry Name" column in a CSV file in the CSVDatabase */
	ColumnDatabase(const std::string& InDatabaseName, const std::string& CSVFileName);

	/** Create a ColumnDatabase from a preconstructed list of ParenthValueStrings */
	ColumnDatabase(const std::string& InDatabaseName, const std::vector<ParenthValueString>& InEntriesInColumn);

	std::vector<ParenthValueString> GetEntries();

	std::vector<std::string> GetEntriesAsStrings();

	std::string GetName() const;

	static void LoadEntryNameDatabase(const std::string& InDatabaseName, const std::string& CSVFileName);

	static void LoadStaticDatabase(const std::string& InDatabaseName, const std::vector<ParenthValueString>& InEntriesInColumn);

	static std::shared_ptr<ColumnDatabase> GetColumnDatabase(const std::string& DatabaseName);

	static void LoadStaticDatabases();

private:

	static std::map<std::string, std::shared_ptr<ColumnDatabase>> ColumnDatabaseMap;

	std::vector<ParenthValueString> EntriesInColumn;

	std::string DatabaseName;
};
