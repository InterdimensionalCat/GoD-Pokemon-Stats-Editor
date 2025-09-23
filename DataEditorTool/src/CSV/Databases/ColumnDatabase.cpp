#include "include.h"
#include "CSV/Databases/ColumnDatabase.h"

#include "CSV/CSVDatabase.h"
#include "CSV/NewCSVData.h"
#include "CSV/StringTypes/ParenthValueString.h"
#include "CSV/StringTypes/EntryNameString.h"

std::map<std::string, std::shared_ptr<ColumnDatabase>> ColumnDatabase::ColumnDatabaseMap = std::map<std::string, std::shared_ptr<ColumnDatabase>>();

// TODO: ColumnDatabases is honestly not a good solution to the problem of not wanting to
// redefine lists of columns in CSV files and also static lists. Consider a better solution
// and refactoring it.
ColumnDatabase::ColumnDatabase
(
	const std::string& InDatabaseName,
	const std::string& CSVFileName
) :
	DatabaseName(InDatabaseName)
{
	auto EntryNameStrings = GoDCSV::CSVDatabase::Get()->GetCSVFile<GoDCSV::NewCSVData>(CSVFileName)->GetStringColumn("Entry Name");

	EntriesInColumn.reserve(EntryNameStrings.size());
	for (const auto& String : EntryNameStrings)
	{
		const EntryNameString EntryName = EntryNameString(String);
		EntriesInColumn.push_back(EntryName.ToParenthValueString());
	}
}

ColumnDatabase::ColumnDatabase(
	const std::string& InDatabaseName,
	const std::vector<ParenthValueString>& InEntriesInColumn
) :
	DatabaseName(InDatabaseName),
	EntriesInColumn(InEntriesInColumn)
{

}

std::vector<ParenthValueString> ColumnDatabase::GetEntries()
{
	return EntriesInColumn;
}

std::vector<std::string> ColumnDatabase::GetEntriesAsStrings()
{
	std::vector<std::string> ReturnedStrings;
	ReturnedStrings.reserve(EntriesInColumn.size());

	for (const auto& ParenthValue : EntriesInColumn)
	{
		ReturnedStrings.push_back(ParenthValue.GetParenthValueString());
	}

	return ReturnedStrings;
}

std::string ColumnDatabase::GetName() const
{
	return DatabaseName;
}

void ColumnDatabase::LoadEntryNameDatabase(
	const std::string& InDatabaseName, 
	const std::string& CSVFileName
)
{
	ColumnDatabaseMap.insert_or_assign(
		InDatabaseName, 
		std::make_shared<ColumnDatabase>(InDatabaseName, CSVFileName)
	);
}

void ColumnDatabase::LoadStaticDatabase
(
	const std::string& InDatabaseName, 
	const std::vector<ParenthValueString>& InEntriesInColumn
)
{
	ColumnDatabaseMap.insert_or_assign(
		InDatabaseName,
		std::make_shared<ColumnDatabase>(InDatabaseName, InEntriesInColumn)
	);
}

std::shared_ptr<ColumnDatabase> ColumnDatabase::GetColumnDatabase(const std::string& DatabaseName)
{
	return ColumnDatabaseMap.at(DatabaseName);
}

void ColumnDatabase::LoadStaticDatabases()
{
	// TODO: Show the standard level up rate strings rather than
	// the internal ones (IE: "Medium Fast" instead of "Standard")

	// Xp Rate Documentation:
    // Standard (0):   Medium Fast
    // Very Fast (1):  Erratic
    // Slowest (2)     Fluctuating
    // Slow (3):       Medium Slow
    // Fast (4):       Fast
    // Very Slow (5):  Slow

	const std::string LevelUpRateDatabaseName = "LevelUpRate-EntriesList";

	std::vector<ParenthValueString> LevelUpRateEntries;

	LevelUpRateEntries.push_back(ParenthValueString("Standard (0)"));
	LevelUpRateEntries.push_back(ParenthValueString("Very Fast (1)"));
	LevelUpRateEntries.push_back(ParenthValueString("Slowest (2)"));
	LevelUpRateEntries.push_back(ParenthValueString("Slow (3)"));
	LevelUpRateEntries.push_back(ParenthValueString("Fast (4)"));
	LevelUpRateEntries.push_back(ParenthValueString("Very Slow (5)"));

	LoadStaticDatabase(LevelUpRateDatabaseName, LevelUpRateEntries);


	// Gender Ratio Documentation:
	// Any value between 0 and 255 can be input,
	// the gender ratio is ~= Input/254 (its not exact)
	// and 255 is special cased to be Genderless.
	// In this and future pokemon games the following
	// ratios are the only ones ever used:

	// Male Only (0)
	// 87.5% Male (31)
	// 75% Male (63)
	// 50% Male (127)
	// 75% Female (191)
	// 87.5% Female (223)
	// Female Only (254)
	// Genderless (255)

	// However, interestingly, 87.5% Female pokemon are so
	// uncommonly made, that in Gen 3 no pokemon use this
	// gender ratio yet.
	const std::string GenderRatioDatabaseName = "GenderRatio-EntriesList";

	std::vector<ParenthValueString> GenderRatioEntries;

	GenderRatioEntries.push_back(ParenthValueString("Male Only (0)"));
	GenderRatioEntries.push_back(ParenthValueString("87.5% Male (31)"));
	GenderRatioEntries.push_back(ParenthValueString("75% Male (63)"));
	GenderRatioEntries.push_back(ParenthValueString("50% Male (127)"));
	GenderRatioEntries.push_back(ParenthValueString("75% Female (191)"));
	GenderRatioEntries.push_back(ParenthValueString("87.5% Female (223)"));
	GenderRatioEntries.push_back(ParenthValueString("Female Only (254)"));
	GenderRatioEntries.push_back(ParenthValueString("Genderless (255)"));

	LoadStaticDatabase(GenderRatioDatabaseName, GenderRatioEntries);
}