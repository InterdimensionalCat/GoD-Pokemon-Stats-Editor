#include "include.h"
#include "CSV/StaticCSVFiles.h"

#include "CSV/CSVDatabase.h"
#include "CSV/CSVData.h"
#include "CSV/StringTypes/ParenthValueString.h"
#include "CSV/StringTypes/EntryNameString.h"

using namespace GoDCSV;

using LoadedCSVData = std::pair<std::vector<std::string>, std::vector<json>>;

LoadedCSVData StaticCSVFiles::LoadLevelUpRateDatabase()
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

	ICLogger::Info("Loading static LevelUpRate database");

	std::vector<ParenthValueString> LevelUpRateEntries;

	LevelUpRateEntries.push_back(ParenthValueString("Standard (0)"));
	LevelUpRateEntries.push_back(ParenthValueString("Very Fast (1)"));
	LevelUpRateEntries.push_back(ParenthValueString("Slowest (2)"));
	LevelUpRateEntries.push_back(ParenthValueString("Slow (3)"));
	LevelUpRateEntries.push_back(ParenthValueString("Fast (4)"));
	LevelUpRateEntries.push_back(ParenthValueString("Very Slow (5)"));

	return CreateLoadedDataFromParenthValueList(LevelUpRateEntries, "Rate");
}

LoadedCSVData StaticCSVFiles::LoadGenderRatioDatabase()
{
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

	// However, interestingly, 87.5% Female Pokemon are so
	// uncommonly made, that in Gen 3 no Pokemon use this
	// gender ratio yet.

	ICLogger::Debug("Loading static GenderRatio database");

	std::vector<ParenthValueString> GenderRatioEntries;

	GenderRatioEntries.push_back(ParenthValueString("Male Only (0)"));
	GenderRatioEntries.push_back(ParenthValueString("87.5% Male (31)"));
	GenderRatioEntries.push_back(ParenthValueString("75% Male (63)"));
	GenderRatioEntries.push_back(ParenthValueString("50% Male (127)"));
	GenderRatioEntries.push_back(ParenthValueString("75% Female (191)"));
	GenderRatioEntries.push_back(ParenthValueString("87.5% Female (223)"));
	GenderRatioEntries.push_back(ParenthValueString("Female Only (254)"));
	GenderRatioEntries.push_back(ParenthValueString("Genderless (255)"));

	return CreateLoadedDataFromParenthValueList(GenderRatioEntries, "Ratio");
}

LoadedCSVData StaticCSVFiles::LoadGenderDatabase()
{
	// Gender Documentation:
	// Male (0)
	// Female (1)
	// Genderless (2)
	// Random (255)

	ICLogger::Debug("Loading static Gender database");

	std::vector<ParenthValueString> GenderEntries;

	GenderEntries.push_back(ParenthValueString("Male (0)"));
	GenderEntries.push_back(ParenthValueString("Female (1)"));
	GenderEntries.push_back(ParenthValueString("Genderless (2)"));
	GenderEntries.push_back(ParenthValueString("Random (255)"));

	return CreateLoadedDataFromParenthValueList(GenderEntries, "Gender");
}

LoadedCSVData StaticCSVFiles::LoadEvolutionMethodDatabase()
{
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

	ICLogger::Debug("Loading static EvolutionMethod database");

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

	return CreateLoadedDataFromParenthValueList(EvolutionMethodEntries, "Method");
}

LoadedCSVData StaticCSVFiles::LoadEvolutionStoneDatabase()
{
	// Evolution stones:

	ICLogger::Debug("Loading static EvolutionStone database");

	std::vector<ParenthValueString> EvolutionStoneEntries;

	EvolutionStoneEntries.push_back(ParenthValueString("SUN STONE (93)"));
	EvolutionStoneEntries.push_back(ParenthValueString("MOON STONE (94)"));
	EvolutionStoneEntries.push_back(ParenthValueString("FIRE STONE (95)"));
	EvolutionStoneEntries.push_back(ParenthValueString("THUNDERSTONE (96)"));
	EvolutionStoneEntries.push_back(ParenthValueString("WATER STONE (97)"));
	EvolutionStoneEntries.push_back(ParenthValueString("LEAF STONE (98)"));

	return CreateLoadedDataFromParenthValueList(EvolutionStoneEntries, "Item ID");
}

LoadedCSVData StaticCSVFiles::LoadKeyItemDatabase()
{
	// Key Items:
	// Needed for the "Evolve with Key Item" evolution condition.
	// For some reason this condition does not use the standard
	// item ID for each key item, but rather a secondary ID that is
	// just the original ID + 150, so for example, the SAFE KEY is
	// normally item ID 350, but for the key item evo condition its 500

	ICLogger::Debug("Loading static KeyItem database");

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

	return CreateLoadedDataFromParenthValueList(KeyItemEntries, "Key Item ID");
}

LoadedCSVData StaticCSVFiles::CreateLoadedDataFromParenthValueList(const std::vector<ParenthValueString>& InEntries, const std::string& ValueColumnName)
{
	LoadedCSVData LoadedData;
	LoadedData.first = { "Entry Name", ValueColumnName};
	for (int32_t Index = 0; Index < InEntries.size(); Index++)
	{
		json NewRow;
		EntryNameString EntryName = EntryNameString(
			InEntries.at(Index).GetString(),
			std::format("{}", Index)
		);
		NewRow["Entry Name"] = EntryName.GetEntryNameString();
		NewRow[ValueColumnName] = InEntries.at(Index).GetParenthValueString();
		LoadedData.second.push_back(NewRow);
	}

	return LoadedData;
}
