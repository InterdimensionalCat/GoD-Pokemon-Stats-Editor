#include "include.h"
#include "Editors/PokemonStats/PokemonStatsSpeciesInfo.h"

#include "Editors/PokemonStats/PokemonStatsEditor.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleSectionDivider.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleImageBox.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVTextBox.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntHexBox.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntBox.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVComboBox.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntSlider.h"
#include "Util/TextureLoader.h"
#include "Pokeface/PokefaceData.h"

PokemonStatsSpeciesInfo::PokemonStatsSpeciesInfo(PokemonStatsEditor* InParent) : UiSection("Species Info", InParent)
{
	const std::string CSVName = "Pokemon Stats";

	// Add the top level species info elements.

	// Species: This is just the entry name of the current row (IE: "BULBASAUR"  - 1)
	std::shared_ptr<CSVTextBox> Species = std::make_shared<CSVTextBox>("Species", this, CSVName, "Entry Name");

	// Pokeface Image: This is just the image of a Pokemon that is shown in the hp bar in battle
	PokefaceImage = std::make_shared<SimpleImageBox>("##PokefaceImage", this);

	const auto& PokefaceDataIds = PokefaceData::GetPokefaceData();

	if (!PokefaceDataIds.empty())
	{
		PokefaceImage->SetTexture(PokefaceDataIds.at(0));
	}

	AddElement(Species);
	AddElement(PokefaceImage);

	// Add the identification info elements.

	// Name ID: This is the text ID of the Pokemon's name (IE: "BULBASAUR" (0x3E9))
	NameID = std::make_shared<CSVTextBox>("Name ID", this, CSVName);

	// Species Name ID: This is the text ID of the Pokemon's species (IE: "SEED" (0x662))
	std::shared_ptr<CSVTextBox> SpeciesNameID = std::make_shared<CSVTextBox>("Species Name ID", this, CSVName);

	// Index: This is the internal ID number of this Pokemon (IE: 31 (0x1F))
	std::shared_ptr<CSVIntHexBox> Index = std::make_shared<CSVIntHexBox>("Index", this, CSVName, "Unknown 1", 0, 0);
	Index->SetDisabled(true);

	// National Dex ID: This is the National Dex number of this Pokemon (IE: 255)
	std::shared_ptr<CSVIntBox> NationalDexID = std::make_shared<CSVIntBox>("National Dex ID", this, CSVName, "National Dex Index", 1, 5);
	NationalDexID->SetDisabled(true);

	// National Dex ID: This is the Hoenn Dex number of this Pokemon (IE: 4)
	// Not sure what the number corresponds to for Pokemon outside of Hoenn's regional dex.
	std::shared_ptr<CSVIntBox> HoennDexID = std::make_shared<CSVIntBox>("Hoenn Dex ID", this, CSVName, "Hoenn dex regional id", 1, 5);
	HoennDexID->SetDisabled(true);

	AddElement(std::make_shared<SimpleSectionDivider>("Identification Info", this));
	AddElement(NameID);
	AddElement(SpeciesNameID);
	AddElement(Index);
	AddElement(NationalDexID);
	AddElement(HoennDexID);

	// Add the type info elements.

	// Type 1: This is the primary type of this Pokemon (IE: "GRASS (12)")
	auto TypesOne = std::make_shared<CSVComboBox>("Type 1", this, CSVName, "Types 1", "Type", "Entry Name");

	// Type 2: This is the secondary type of this Pokemon (IE: "POISON (4)")
	auto TypesTwo = std::make_shared<CSVComboBox>("Type 2", this, CSVName, "Types 2", "Type", "Entry Name");


	AddElement(std::make_shared<SimpleSectionDivider>("Type Info", this));
	AddElement(TypesOne);
	AddElement(TypesTwo);

	// Add the ability info elements.

	// Ability 1: This is the primary ability of this Pokemon (IE: "OVERGROW (65)")
	auto AbilitiesOne = std::make_shared<CSVComboBox>("Abilities 1", this, CSVName, "Ability", "Entry Name");

	// Ability 2: This is the secondary ability of this Pokemon (IE: "CHLOROPHYLL (34)")
	auto AbilitiesTwo = std::make_shared<CSVComboBox>("Abilities 2", this, CSVName, "Ability", "Entry Name");

	AddElement(std::make_shared<SimpleSectionDivider>("Ability Info", this));
	AddElement(AbilitiesOne);
	AddElement(AbilitiesTwo);

	// Add the wild item info elements.

	// Wild Item 1: This is the primary item this Pokemon may hold when encountered in the wild (IE: "MIRACLE SEED (205)")
	auto WildItemOne = std::make_shared<CSVComboBox>("Wild Item 1", this, CSVName, "Wild Items 1", "Item", "Entry Name");

	// Wild Item 2: This is the secondary item this Pokemon may hold when encountered in the wild (IE: "LEFTOVERS (200)")
	auto WildItemTwo = std::make_shared<CSVComboBox>("Wild Item 2", this, CSVName, "Wild Items 2", "Item", "Entry Name");

	AddElement(std::make_shared<SimpleSectionDivider>("Wild Item Info", this));
	AddElement(WildItemOne);
	AddElement(WildItemTwo);

	// Add the ev yield elements.

	// HP EV: This is the number of HP EVs this Pokemon yields when defeated (IE: 1)
	auto HPEvYield      = std::make_shared<CSVIntSlider>("HP EV",      this, CSVName, "EV Yields HP",      0, 10);

	// Attack EV: This is the number of Attack EVs this Pokemon yields when defeated (IE: 2)
	auto AttackEvYield  = std::make_shared<CSVIntSlider>("Attack EV",  this, CSVName, "EV Yields Attack",  0, 10);

	// Defense EV: This is the number of Defense EVs this Pokemon yields when defeated (IE: 3)
	auto DefenseEvYield = std::make_shared<CSVIntSlider>("Defense EV", this, CSVName, "EV Yields Defense", 0, 10);

	// Sp. Atk EV: This is the number of Special Attack EVs this Pokemon yields when defeated (IE: 2)
	auto SpAtkEvYield   = std::make_shared<CSVIntSlider>("Sp.Atk EV",  this, CSVName, "EV Yields Sp.Atk",  0, 10);

	// Sp. Def EV: This is the number of Special Defense EVs this Pokemon yields when defeated (IE: 3)
	auto SpDefEvYield   = std::make_shared<CSVIntSlider>("Sp.Def EV",  this, CSVName, "EV Yields Sp.Def",  0, 10);

	// Speed EV: This is the number of Speed EVs this Pokemon yields when defeated (IE: 1)
	auto SpeedEvYield   = std::make_shared<CSVIntSlider>("Speed EV",   this, CSVName, "EV Yields Speed",   0, 10);

	AddElement(std::make_shared<SimpleSectionDivider>("EV Yields", this));
	AddElement(HPEvYield);
	AddElement(AttackEvYield);
	AddElement(DefenseEvYield);
	AddElement(SpAtkEvYield);
	AddElement(SpDefEvYield);
	AddElement(SpeedEvYield);

	// Add misc info elements.

	// Level up Rate: This is the rate at which this Pokemon gains levels (IE: "Very Slow (5)")
	auto LevelUpRate = std::make_shared<CSVComboBox>("Level up Rate", this, CSVName, "LevelUpRate", "Rate");

	// Exp Yield: This is the modifier for the experience this Pokemon yields when defeated (IE: 64)
	auto ExpYield = std::make_shared<CSVIntBox>("Exp Yield", this, CSVName, "Exp yield", 1, 5);
	ExpYield->SetBounds(0, ExpYield->GetMaxValue());

	// Gender Ratio: This is the the ratio of Male/Female for this Pokemon out of 255, or 255 itself for genderless (IE: "75% Female (191)")
	auto GenderRatio = std::make_shared<CSVComboBox>("Gender Ratio", this, CSVName, "GenderRatio", "Ratio");

	// Catch Rate: This is the catch rate of this Pokemon, higher is easier to catch (IE: 45)
	auto CatchRate = std::make_shared<CSVIntBox>("Catch Rate", this, CSVName, 1, 5);
	CatchRate->SetBounds(0, CatchRate->GetMaxValue());

	// Height: This is the height of this Pokemon in meters (IE: 6)
	auto Height = std::make_shared<CSVIntBox>("Height (Meters)", this, CSVName, "Height", 1, 5);
	Height->SetBounds(0, Height->GetMaxValue());

	// Weight: This is the weight of this Pokemon in kilograms (IE: 69)
	auto Weight = std::make_shared<CSVIntBox>("Weight (Kg)", this, CSVName, "Weight", 1, 5);
	Weight->SetBounds(0, Height->GetMaxValue());

	// Base Happiness: This is the base happiness of this Pokemon, higher is happier (IE: 70)
	auto BaseHappiness = std::make_shared<CSVIntBox>("Base Happiness", this, CSVName, 1, 5);
	BaseHappiness->SetBounds(0, BaseHappiness->GetMaxValue());

	AddElement(std::make_shared<SimpleSectionDivider>("Misc Info", this));
	AddElement(LevelUpRate);
	AddElement(ExpYield);
	AddElement(GenderRatio);
	AddElement(CatchRate);
	AddElement(Height);
	AddElement(Weight);
	AddElement(BaseHappiness);

	CalculateElementMaxWidth();
}

void PokemonStatsSpeciesInfo::Refresh()
{
	CalculateElementMaxWidth();

	UiSection::Refresh();

	// Set the correct PokeFace image based
	// on the current row.

	const auto& PokefaceDataIds = PokefaceData::GetPokefaceData();

	if(!PokefaceDataIds.empty())
	{
		PokefaceImage->SetTexture(PokefaceDataIds.at(GetParent()->GetTabCSVState()->GetCurrentRow()));
	}
}

void PokemonStatsSpeciesInfo::CalculateElementMaxWidth()
{
	const std::string CSVName = "Pokemon Stats";

	// Determine the largest element size of anything in this section and set that as the min needed size.
	auto PokemonStatsCSV = GoDCSV::CSVDatabase::Get()->GetCSVFile(CSVName);
	std::vector<std::string> StringLengths = PokemonStatsCSV->GetStringColumn("Entry Name");

	auto NameIDStrings = PokemonStatsCSV->GetStringColumn("Name ID");
	StringLengths.insert(StringLengths.end(), NameIDStrings.begin(), NameIDStrings.end());

	auto SpeciesNameIDStrings = PokemonStatsCSV->GetStringColumn("Species Name ID");
	StringLengths.insert(StringLengths.end(), SpeciesNameIDStrings.begin(), SpeciesNameIDStrings.end());

	// Setting the min size for this element will effectively set the min size for every element in this
	// Section as the section has size syncing enabled
	NameID->SetMinFromLongestString(StringLengths);
}