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

	// Evolution Method Documentation:

	// None (0): No evolution,                                             Param: Always 0
	// Max Happiness (1): Evolves when happiness is maxed,                 Param: Always 0
	// Happiness (Day) (2): Unimplemented, used for Espeon in RSE,         Param: Always 0
	// Happiness (Night) (3): Unimplemented, used for Umbreon in RSE,      Param: Always 0
	// Level Up (4): Evolves when the level is reached,                    Param: The level needed to evolve
	// Trade (5): Evolves when traded,                                     Param: Always 0
	// Trade With Item (6): Evoles when traded with an item,               Param: The ID of the item needed to evolve
	// Evolution Stone (7): Evolves when exposed to its evolution stone,   Param: The item ID of the needed stone
	// Atk > Def (8): Evolves at the specified level if Atk > Def,         Param: The level needed to evolve
	// Atk = Def (9): Evolves at the specified level if Atk = Def,         Param: The level needed to evolve
	// Atk < Def (10): Evolves at the specified level if Atk < Def,        Param: The level needed to evolve
	// Silcoon evolution method (11): Evolves based on PID at the level,   Param: The level needed to evolve
	// Cascoon evolution method (12): Evolves based on PID at the level,   Param: The level needed to evolve
	// Ninjask evolution method (13): Unimplemented, for Ninjask in RSE,   Param: The level needed to evolve
	// Shedinja evolution method (14): Shedinja appears at this level,     Param: The level needed to evolve
	// Max Beauty (15): Evolves when Beauty is raised to the param value,  Param: The beauty value needed to evolve
	// Level Up With Key Item (16): Used to evolve Espeon/Umbreon,         Param: Key Item ID (item 350 and after) + 150, (516 for Espeon, 517 for Umbreon).
	const std::string EvolutionMethodDatabaseName = "EvolutionMethod-EntriesList";

	std::vector<ParenthValueString> EvolutionMethodEntries;

	EvolutionMethodEntries.push_back(ParenthValueString("None (0)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Max Happiness (1)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Happiness (Day) (2)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Happiness (Night) (3)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Level Up (4)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Trade (5)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Trade With Item (6)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Evolution Stone (7)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Atk > Def (8)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Atk = Def (9)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Atk < Def (10)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Silcoon evolution method (11)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Cascoon evolution method (12)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Ninjask evolution method (13)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Shedinja evolution method (14)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Max Beauty (15)"));
	EvolutionMethodEntries.push_back(ParenthValueString("Level Up With Key Item (16)"));

	LoadStaticDatabase(EvolutionMethodDatabaseName, EvolutionMethodEntries);

	// Evolution stones:

	const std::string EvolutionStoneDatabaseName = "EvolutionStone-EntriesList";

	std::vector<ParenthValueString> EvolutionStoneEntries;

	EvolutionStoneEntries.push_back(ParenthValueString("SUN STONE (93)"));
	EvolutionStoneEntries.push_back(ParenthValueString("MOON STONE (94)"));
	EvolutionStoneEntries.push_back(ParenthValueString("FIRE STONE (95)"));
	EvolutionStoneEntries.push_back(ParenthValueString("THUNDERSTONE (96)"));
	EvolutionStoneEntries.push_back(ParenthValueString("WATER STONE (97)"));
	EvolutionStoneEntries.push_back(ParenthValueString("LEAF STONE (98)"));

	LoadStaticDatabase(EvolutionStoneDatabaseName, EvolutionStoneEntries);

	// Key Items:
	// Needed for the "Evolve with Key Item" evolution condition.
	// For some reason this condition does not use the standard
	// item ID for each key item, but rather a secondary ID that is
	// just the original ID + 150, so for example, the SAFE KEY is
	// normally item ID 350, but for the key item evo condition its 500

	const std::string KeyItemDatabaseName = "KeyItem-EntriesList";

	std::vector<ParenthValueString> KeyItemEntries;

	KeyItemEntries.push_back(ParenthValueString("SAFE KEY (500)"));
	KeyItemEntries.push_back(ParenthValueString("ELEVATOR KEY (501)"));
	KeyItemEntries.push_back(ParenthValueString("BONSLY CARD (502)"));
	KeyItemEntries.push_back(ParenthValueString("MACHINE PART (503)"));
	KeyItemEntries.push_back(ParenthValueString("GONZAP'S KEY (504)"));
	KeyItemEntries.push_back(ParenthValueString("DATA ROM (505)"));
	KeyItemEntries.push_back(ParenthValueString("ID CARD (506)"));
	KeyItemEntries.push_back(ParenthValueString("MUSIC DISC (507)"));
	KeyItemEntries.push_back(ParenthValueString("SYSTEM LEVER (508)"));
	KeyItemEntries.push_back(ParenthValueString("MAYOR'S NOTE (509)"));
	KeyItemEntries.push_back(ParenthValueString("MIROR RADAR (510)"));
	KeyItemEntries.push_back(ParenthValueString("POKé SNACK (511)"));
	KeyItemEntries.push_back(ParenthValueString("COLOGNE CASE (512)"));
	KeyItemEntries.push_back(ParenthValueString("JOY SCENT (513)"));
	KeyItemEntries.push_back(ParenthValueString("EXCITE SCENT (514)"));
	KeyItemEntries.push_back(ParenthValueString("VIVID SCENT (515)"));
	KeyItemEntries.push_back(ParenthValueString("SUN SHARD (516)"));
	KeyItemEntries.push_back(ParenthValueString("MOON SHARD (517)"));
	KeyItemEntries.push_back(ParenthValueString("BONSLY PHOTO (518)"));
	KeyItemEntries.push_back(ParenthValueString("CRY ANALYZER (519)"));

	LoadStaticDatabase(KeyItemDatabaseName, KeyItemEntries);
}
