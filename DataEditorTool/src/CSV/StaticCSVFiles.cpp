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

LoadedCSVData StaticCSVFiles::LoadBattleStyleDatabase()
{
	// Battle Style Documentation:

	// None (0): None,
	// Single (1): Single Battle,
	// Double (2): Double Battle,
	// Other (3): Everything else (is "Multi" in Colo only)
	ICLogger::Debug("Loading static BattleStyle database");
	std::vector<ParenthValueString> BattleStyleEntries;

	BattleStyleEntries.push_back(ParenthValueString("None (0)"));
	BattleStyleEntries.push_back(ParenthValueString("Single (1)"));
	BattleStyleEntries.push_back(ParenthValueString("Double (2)"));
	BattleStyleEntries.push_back(ParenthValueString("Other (3)"));

	return CreateLoadedDataFromParenthValueList(BattleStyleEntries, "BattleStyle");
}

LoadedCSVData StaticCSVFiles::LoadBGMMusicDatabase()
{
	// BGM Music Documentation:
	// BGM Musics are stored as just hex ID's, however documentation
	// of what what song each ID corresponds to has been compiled.
	// this matches each ID to its known song name.
	ICLogger::Debug("Loading static BGM Music database");
	std::vector<ParenthValueString> BGMMusicEntries;

	BGMMusicEntries.push_back(ParenthValueString("None (0)"));

	BGMMusicEntries.push_back(ParenthValueString("Cipher Lab (1067)"));
	BGMMusicEntries.push_back(ParenthValueString("Mt. Battle (1068)"));
	BGMMusicEntries.push_back(ParenthValueString("Phenac City [A] (1070)"));
	BGMMusicEntries.push_back(ParenthValueString("Outskirt Stand (1071)"));
	BGMMusicEntries.push_back(ParenthValueString("Relic Forest (1072)"));
	BGMMusicEntries.push_back(ParenthValueString("Pyrite Town (1074)"));
	BGMMusicEntries.push_back(ParenthValueString("Pokemon Center (1075)"));
	BGMMusicEntries.push_back(ParenthValueString("Miror B. Theme (1088)"));

	BGMMusicEntries.push_back(ParenthValueString("Pokeon Lab (1124)"));
	BGMMusicEntries.push_back(ParenthValueString("Gateon Port (1125)"));
	BGMMusicEntries.push_back(ParenthValueString("Krabby Club (1126)"));
	BGMMusicEntries.push_back(ParenthValueString("Normal Battle XD (1127)"));
	BGMMusicEntries.push_back(ParenthValueString("Cipher Battle Normal (1128)"));
	BGMMusicEntries.push_back(ParenthValueString("Purification Chamber (1129)"));
	BGMMusicEntries.push_back(ParenthValueString("Theme of Suspense (1130)"));
	BGMMusicEntries.push_back(ParenthValueString("Mecha-Groudon (1132)"));
	BGMMusicEntries.push_back(ParenthValueString("World Map (1133)"));

	BGMMusicEntries.push_back(ParenthValueString("Mt. Battle Break Room (1193)"));
	BGMMusicEntries.push_back(ParenthValueString("Reception Center (1194)"));

	BGMMusicEntries.push_back(ParenthValueString("Colosseum 1 [B] (1241)"));
	BGMMusicEntries.push_back(ParenthValueString("Colosseum 3 [B] (1242)"));
	BGMMusicEntries.push_back(ParenthValueString("Colosseum 3 [C] (1243)"));
	BGMMusicEntries.push_back(ParenthValueString("Greevil Battle (1251)"));
	BGMMusicEntries.push_back(ParenthValueString("Shadow Lugia Battle (1252)"));
	BGMMusicEntries.push_back(ParenthValueString("Battle Bingo (1264)"));
	BGMMusicEntries.push_back(ParenthValueString("Battle CD Simulator [A] (1265)"));
	BGMMusicEntries.push_back(ParenthValueString("Link Battle [Gym Leader] (1266)"));
	BGMMusicEntries.push_back(ParenthValueString("Link Battle [Trainer] (1267)"));
	BGMMusicEntries.push_back(ParenthValueString("Dr. Kaminko's Yard (1291)"));
	BGMMusicEntries.push_back(ParenthValueString("S.S. Libra (1292)"));
	BGMMusicEntries.push_back(ParenthValueString("Wild Battle (1293)"));
	BGMMusicEntries.push_back(ParenthValueString("Puri 4 (1294)"));
	BGMMusicEntries.push_back(ParenthValueString("Puri 3 (1295)"));
	BGMMusicEntries.push_back(ParenthValueString("Puri 2 (1296)"));
	BGMMusicEntries.push_back(ParenthValueString("Mecha-Groudon Cutscene (1297)"));

	BGMMusicEntries.push_back(ParenthValueString("Snagem Hideout (1317)"));
	BGMMusicEntries.push_back(ParenthValueString("Colosseum 1 [A] (1318)"));
	BGMMusicEntries.push_back(ParenthValueString("Colosseum 2 (1319)"));
	BGMMusicEntries.push_back(ParenthValueString("Colosseum 3 (A) (1320)"));
	BGMMusicEntries.push_back(ParenthValueString("Colosseum 4 (1321)"));

	BGMMusicEntries.push_back(ParenthValueString("Jovi is Sad (1361)"));
	BGMMusicEntries.push_back(ParenthValueString("Shadow Lugia Battle [B] (1362)"));
	BGMMusicEntries.push_back(ParenthValueString("Jovi's Theme (1363)"));
	BGMMusicEntries.push_back(ParenthValueString("Phenac City [B] (1370)"));

	BGMMusicEntries.push_back(ParenthValueString("Kandee (1382)"));
	BGMMusicEntries.push_back(ParenthValueString("Link Battle [Mode Select] [B] (1383)"));
	BGMMusicEntries.push_back(ParenthValueString("Link Battle [Mode Select] (1384)"));

	BGMMusicEntries.push_back(ParenthValueString("Miror B Battle (1390)"));
	BGMMusicEntries.push_back(ParenthValueString("Jingle Dissonant - Need Info (1391)"));

	BGMMusicEntries.push_back(ParenthValueString("Cipher Admin Battle (1407)"));
	BGMMusicEntries.push_back(ParenthValueString("Hexagon Brothers (1408)"));
	BGMMusicEntries.push_back(ParenthValueString("Cipher Key Lair (1409)"));
	BGMMusicEntries.push_back(ParenthValueString("Willie Battle (1410)"));
	BGMMusicEntries.push_back(ParenthValueString("Greevil (1412)"));
	BGMMusicEntries.push_back(ParenthValueString("Battle CD Simulator [B] (1413)"));

	BGMMusicEntries.push_back(ParenthValueString("Relieve Ceremony - Need Info (1448)"));
	BGMMusicEntries.push_back(ParenthValueString("Heroic [A] (1449)"));
	BGMMusicEntries.push_back(ParenthValueString("Heroic [B] (1450)"));

	BGMMusicEntries.push_back(ParenthValueString("Puri 1 (1467)"));
	BGMMusicEntries.push_back(ParenthValueString("Orre Colosseum (1468)"));
	BGMMusicEntries.push_back(ParenthValueString("Ending Cutscene [A] (1469)"));
	BGMMusicEntries.push_back(ParenthValueString("Ending Cutscene [B] (1470)"));
	BGMMusicEntries.push_back(ParenthValueString("Cipher Admin Gonzap (1471)"));

	BGMMusicEntries.push_back(ParenthValueString("Link Battle [Champion] (1485)"));
	BGMMusicEntries.push_back(ParenthValueString("Mr. Verich (1486)"));

	BGMMusicEntries.push_back(ParenthValueString("Link Battle [Select Screen] (1499)"));

	return CreateLoadedDataFromParenthValueList(BGMMusicEntries, "BGMID");
}