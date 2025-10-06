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

std::deque<GLuint> PokemonStatsSpeciesInfo::PokefaceData;

bool PokemonStatsSpeciesInfo::bPokefaceDataLoaded = false;

PokemonStatsSpeciesInfo::PokemonStatsSpeciesInfo(PokemonStatsEditor* InParent) : UiSection("Species Info", InParent)
{
	const std::string CSVName = "Pokemon Stats";

	// Attempt to load Pokeface data. If loading fails we will just not display Pokeface images.
	InitPokefaceData();

	// Add the top level species info elements.

	// Species: This is just the entry name of the current row (IE: "BULBASAUR"  - 1)
	std::shared_ptr<CSVTextBox> Species = std::make_shared<CSVTextBox>("Species", this, CSVName, "Entry Name");

	// Pokeface Image: This is just the image of a Pokemon that is shown in the hp bar in battle
	PokefaceImage = std::make_shared<SimpleImageBox>("##PokefaceImage", this);
	if (bPokefaceDataLoaded)
	{
		PokefaceImage->SetTexture(PokefaceData.at(0));
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

	auto TypesOne = std::make_shared<CSVComboBox>("Type 1", this, CSVName, "Types 1", "Type", "Entry Name");
	auto TypesTwo = std::make_shared<CSVComboBox>("Type 2", this, CSVName, "Types 2", "Type", "Entry Name");


	AddElement(std::make_shared<SimpleSectionDivider>("Type Info", this));
	AddElement(TypesOne);
	AddElement(TypesTwo);

	// Add the ability info elements.

	auto AbilitiesOne = std::make_shared<CSVComboBox>("Abilities 1", this, CSVName, "Ability", "Entry Name");
	auto AbilitiesTwo = std::make_shared<CSVComboBox>("Abilities 2", this, CSVName, "Ability", "Entry Name");

	AddElement(std::make_shared<SimpleSectionDivider>("Ability Info", this));
	AddElement(AbilitiesOne);
	AddElement(AbilitiesTwo);

	// Add the wild item info elements.

	auto WildItemOne = std::make_shared<CSVComboBox>("Wild Item 1", this, CSVName, "Wild Items 1", "Item", "Entry Name");
	auto WildItemTwo = std::make_shared<CSVComboBox>("Wild Item 2", this, CSVName, "Wild Items 2", "Item", "Entry Name");

	AddElement(std::make_shared<SimpleSectionDivider>("Wild Item Info", this));
	AddElement(WildItemOne);
	AddElement(WildItemTwo);

	// Add the ev yield elements.

	// EV Yields HP,EV Yields Attack,EV Yields Defense,EV Yields Sp.Atk,EV Yields Sp.Def,EV Yields Speed

	auto HPEvYield      = std::make_shared<CSVIntSlider>("HP EV",      this, CSVName, "EV Yields HP",      0, 10);
	auto AttackEvYield  = std::make_shared<CSVIntSlider>("Attack EV",  this, CSVName, "EV Yields Attack",  0, 10);
	auto DefenseEvYield = std::make_shared<CSVIntSlider>("Defense EV", this, CSVName, "EV Yields Defense", 0, 10);
	auto SpAtkEvYield   = std::make_shared<CSVIntSlider>("Sp.Atk EV",  this, CSVName, "EV Yields Sp.Atk",  0, 10);
	auto SpDefEvYield   = std::make_shared<CSVIntSlider>("Sp.Def EV",  this, CSVName, "EV Yields Sp.Def",  0, 10);
	auto SpeedEvYield   = std::make_shared<CSVIntSlider>("Speed EV",   this, CSVName, "EV Yields Speed",   0, 10);

	AddElement(std::make_shared<SimpleSectionDivider>("EV Yields", this));
	AddElement(HPEvYield);
	AddElement(AttackEvYield);
	AddElement(DefenseEvYield);
	AddElement(SpAtkEvYield);
	AddElement(SpDefEvYield);
	AddElement(SpeedEvYield);

	// Add misc info elements.

	auto LevelUpRate = std::make_shared<CSVComboBox>("Level up Rate", this, CSVName, "LevelUpRate", "Rate");

	auto ExpYield = std::make_shared<CSVIntBox>("Exp Yield", this, CSVName, "Exp yield", 1, 5);
	ExpYield->SetBounds(0, ExpYield->GetMaxValue());

	auto GenderRatio = std::make_shared<CSVComboBox>("Gender Ratio", this, CSVName, "GenderRatio", "Ratio");

	auto CatchRate = std::make_shared<CSVIntBox>("Catch Rate", this, CSVName, 1, 5);
	CatchRate->SetBounds(0, CatchRate->GetMaxValue());

	auto Height = std::make_shared<CSVIntBox>("Height (Meters)", this, CSVName, "Height", 1, 5);
	Height->SetBounds(0, Height->GetMaxValue());

	auto Weight = std::make_shared<CSVIntBox>("Weight (Kg)", this, CSVName, "Weight", 1, 5);
	Weight->SetBounds(0, Height->GetMaxValue());

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
	if (bPokefaceDataLoaded)
	{
		PokefaceImage->SetTexture(PokefaceData.at(GetParent()->GetTabCSVState()->GetCurrentRow()));
	}
}

void PokemonStatsSpeciesInfo::InitPokefaceData()
{
	// TODO: Allow pokeface data to load if some pokeface files are missing,
	// which will be needed to support custom pokemon additions to the Pokemon Stats.csv file

	if(bPokefaceDataLoaded)
	{
		// Pokeface data is already loaded, no need to load it again.
		ICLogger::Info("Pokeface data already loaded, skipping load.");
		return;
	}

	try
	{
		ICLogger::Debug("Attempting to load Pokeface data.");
		PokefaceData.clear();
		// Attempt to find the Pokeface resource dir, which should be at
		// "{ToolPath}/Resources/PokeFace/"
		std::filesystem::path BasePath = std::filesystem::current_path();
		BasePath /= "Resources";
		BasePath /= "PokeFace";

		if (!std::filesystem::is_directory(BasePath))
		{
			// If the Pokeface directory is not found throw an error
			std::string ErrorMessage = std::format("{} is not a directory", BasePath.string());
			throw std::exception(ErrorMessage.c_str());
			return;
		}

		// Get the list of Pokemon, which we can convert into Pokeface data file names
		auto PokemonStatsCSV = GoDCSV::CSVDatabase::Get()->GetCSVFile("Pokemon Stats");
		auto PokemonList = PokemonStatsCSV->GetStringColumn("Entry Name");

		// Resize the PokefaceData list to be the same size as PokemonList, since
		// we will need to set texture ids to the index directly.
		PokefaceData = std::deque<GLuint>(PokemonList.size(), 0);

		// Attempt to load a pokeface data file for each Pokemon list entry.
		for (uint32_t Index = 0; Index < PokemonList.size(); Index++)
		{
			// Get the PokeFace file name, it will be of the format
			// "face_{3 digit int}.png"
			// Example: "face_002.png" is Ivysaur's Pokeface.
			const std::string FileName = std::format("face_{:03}.png", Index);

			std::filesystem::path PathToFace = BasePath / FileName;
			if (!std::filesystem::exists(PathToFace))
			{
				// If the Pokeface file doesn't exist, throw an error and stop loading
				std::string ErrorMessage = std::format("Pokeface file {} not found", FileName);
				throw std::exception(ErrorMessage.c_str());
				return;
			}

			int Width = 0;
			int Height = 0;

			// Attempt to load the pokeface image file, its Width/Height will be stored in the supplied
			// Width and height variables.
			bool Success = LoadTextureFromFile(PathToFace.string().c_str(), &PokefaceData.at(Index), &Width, &Height);
			if (Success)
			{
				ICLogger::Trace("Successfully loaded Pokeface image {}", FileName);
			}
			else
			{
				std::string ErrorMessage = std::format("Error loading Pokeface image {}, is this a valid image file?", FileName);
				throw std::exception(ErrorMessage.c_str());
				break;
			}
		}

		bPokefaceDataLoaded = true;
		ICLogger::Debug("Pokeface data loading successful!");
	}
	catch (const std::exception& e)
	{
		PokefaceData.clear();
		ICLogger::PushErrorNotification("Pokeface data will not be displayed", 10000, "Error Loading Pokeface data: {}", e.what());
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