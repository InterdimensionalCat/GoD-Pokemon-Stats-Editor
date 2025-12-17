#include "include.h"
#include "Editors/Trainers/TrainerPokemon.h"
#include "Editors/Trainers/TrainersEditorTrainerPokemon.h"
#include "Editors/Trainers/TrainersEditor.h"
#include "Pokeface/PokefaceData.h"
#include "CSV/StringTypes/IntHexParenthValue.h"
#include "CSV/StringTypes/ParenthValueString.h"
#include "CSV/StringTypes/EntryNameString.h"
#include "UI/TabCSVState.h"
#include "UI/UiSize/UiConstrainedSize.h"
#include "UI/UiElement/UiMultiElement/UiChildWindow.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleImageBox.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVComboBox.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntBox.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntSlider.h"
#include "UI/UiElement/UiCSVElement/BoolElement/CSVCheckbox.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVIntHexComboBox.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleText.h"
#include "UI/UiElement/UiMultiElement/UiElementSwitcher.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleSectionDivider.h"
#include "Editors/Trainers/CurrentShadowPokemonBox.h"
#include "UI/UiElement/UiMultiElement/UiGroup.h"
#include "UI/UiElement/UiMultiElement/UiElementGrid.h"
#include "UI/UiElement/UiSimpleElement/IntElement/SimpleIntBox.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntHexBox.h"


TrainerPokemon::TrainerPokemon(
	const std::string& InName,
	TrainersEditorTrainerPokemon* InParent,
	int32_t InPartyIndex
) :
	UiChildWindow(InName, InParent),
	ParentTrainerPokemon(InParent),
	PartyIndex(InPartyIndex)
{
	InitPokefaceGroup();
	InitShadowPokemonInfo();
	InitPokemonInfoGroup();
	InitIvEvGrid();
	InitMovesGroup();
	InitMiscGroup();

	for (auto& CSVElement : RowElements)
	{
		CSVElement->SetShouldSyncRowToCSVState(false);
	}

	for (auto& CSVElement : ShadowPokemonElements)
	{
		CSVElement->SetShouldSyncRowToCSVState(false);
	}
}

void TrainerPokemon::Refresh()
{
	auto TrainersCSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(
		ParentTrainerPokemon->GetParentEditor()->GetTrainerCSVFileName()
	);

	auto CurrentTrainerRow = TrainersCSVData->GetRowAtIndex(ParentTrainerPokemon->GetParentEditor()->GetTabCSVState()->GetCurrentRow());

	const bool bPrevIsShadowPokemon = IsShadowPokemon;

	IsShadowPokemon = CurrentTrainerRow->GetBoolAtColumn(
		std::format("Pokemon {} is shadow id", PartyIndex)
	);

	if (IsShadowPokemon)
	{
		CurrentPokemonSwitcher->SwitchCurrentlyActiveElement(CurrentShadowPokemonComboBox);
		CurrentShadowPokemonComboBox->Refresh();
		auto ShadowPokemonCSVFile = GoDCSV::CSVDatabase::Get()->GetCSVFile("Shadow Pokemon");
		auto ShadowPokemonRow = ShadowPokemonCSVFile->GetRowAtIndex(CurrentShadowPokemonComboBox->GetSelectedEntry());
		ParenthValueString TrainerPokemonID = ShadowPokemonRow->GetStringAtColumn("Pokemon Index In Story Deck");
		SetCurrentRow(stoi(TrainerPokemonID.GetValue()));

		ShadowPokemonSwitcher->SwitchCurrentlyActiveElement(ShadowPokemonGroup);
	}
	else
	{
		CurrentPokemonSwitcher->SwitchCurrentlyActiveElement(CurrentPokemonComboBox);
		CurrentPokemonComboBox->Refresh();
		SetCurrentRow(CurrentPokemonComboBox->GetSelectedEntry());

		ShadowPokemonSwitcher->SwitchCurrentlyActiveElement(NonShadowPokemonGroup);
	}

	// Set the correct PokeFace image based
	// on the current row.
	const auto& PokefaceDataIds = PokefaceData::GetPokefaceData();

	if (!PokefaceDataIds.empty())
	{
		auto TrainerPokemonCSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(
			ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName()
		);

		auto CurrentPokemonRow = TrainerPokemonCSVData->GetRowAtIndex(GetCurrentRow());
		ParenthValueString SpeciesID = CurrentPokemonRow->GetStringAtColumn("Species");
		PokefaceImage->SetTexture(PokefaceDataIds.at(stoi(SpeciesID.GetValue())));
	}

	UiChildWindow::Refresh();
}

void TrainerPokemon::Tick()
{
	// Update total IVs and EVs each tick
	int32_t TotalIVs = 0;
	int32_t TotalEVs = 0;
	for (auto& IvElement : IvElements)
	{
		TotalIVs += IvElement->GetManagedValue();
	}
	TotalIvBox->SetIntBuffer(TotalIVs);

	for (auto& EvElement : EvElements)
	{
		TotalEVs += EvElement->GetManagedValue();
	}
	TotalEvBox->SetIntBuffer(TotalEVs);

	UiChildWindow::Tick();
}

void TrainerPokemon::CalculateConstrainedSize(
	const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
	const std::shared_ptr<const UiSize>& ParentSizeConstraints
)
{
	UpdatePokefaceImageSize();
	UiChildWindow::CalculateConstrainedSize(ParentConstrainedSize, ParentSizeConstraints);
}

void TrainerPokemon::SetCurrentRow(const int32_t InRow)
{
	if (CurrentRow != InRow)
	{
		CurrentRow = InRow;

		for (auto& CSVElement : RowElements)
		{
			CSVElement->SetCurrentRow(CurrentRow);
		}

		for (auto& CSVElement : ShadowPokemonElements)
		{
			int32_t Row = 0;

			if (IsShadowPokemon)
			{
				auto ShadowPokemonCSVFile = GoDCSV::CSVDatabase::Get()->GetCSVFile("Shadow Pokemon");
				auto ShadowPokemonRow = ShadowPokemonCSVFile->GetRowAtIndex(CurrentShadowPokemonComboBox->GetSelectedEntry());
				EntryNameString TrainerPokemonID = ShadowPokemonRow->GetStringAtColumn("Entry Name");
				Row = stoi(TrainerPokemonID.GetEntryNum());
				CSVElement->SetDisabled(false);
			}
			else
			{
				CSVElement->SetDisabled(true);
			}

			CSVElement->SetCurrentRow(Row);
		}
	}
}

int32_t TrainerPokemon::GetCurrentRow() const
{
	return CurrentRow;
}

void TrainerPokemon::UpdatePokefaceImageSize()
{
	if (PokefaceImage)
	{
		PokefaceImage->SetImageSize(ImGui::GetFrameHeightWithSpacing() * 4 + ImGui::CalcTextSize("Pokemon Info").y + ImGui::GetStyle().ItemSpacing.y - 1);
	}
}

void TrainerPokemon::InitPokefaceGroup()
{
	auto SectionDividerOne = std::make_shared<SimpleSectionDivider>(std::format("Pokemon {}", PartyIndex), ParentTrainerPokemon);
	SectionDividerOne->SetNumSpaceLengths(1);

	PokefaceImage = std::make_shared<SimpleImageBox>("##PokefaceImage", ParentTrainerPokemon);
	PokefaceImage->SetShouldOverrideSyncedSize(true);

	const auto& PokefaceDataIds = PokefaceData::GetPokefaceData();
	if (!PokefaceDataIds.empty())
	{
		PokefaceImage->SetTexture(PokefaceDataIds.at(0));
	}

	UpdatePokefaceImageSize();

	auto ShadowPokemonCheckbox = std::make_shared<CSVCheckbox>(
		std::format("Shadow Pokemon?##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerCSVFileName(),
		std::format("Pokemon {} is shadow id", PartyIndex)
	);

	CurrentPokemonSwitcher = std::make_shared<UiElementSwitcher>(
		std::format("##CurrentPokemonSwitcher{}", PartyIndex),
		ParentTrainerPokemon
	);

	CurrentPokemonComboBox = std::make_shared<CSVIntHexComboBox>(
		std::format("Deck Data ID##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerCSVFileName(),
		std::format("Pokemon {}", PartyIndex),
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Entry Name"
	);

	CurrentShadowPokemonComboBox = std::make_shared<CurrentShadowPokemonBox>(
		std::format("Shadow Pokemon ID##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerCSVFileName(),
		std::format("Pokemon {}", PartyIndex)
	);

	CurrentPokemonSwitcher->AddElement(CurrentPokemonComboBox);
	CurrentPokemonSwitcher->AddElement(CurrentShadowPokemonComboBox);

	AddElement(SectionDividerOne);
	AddElement(PokefaceImage);
	AddElement(ShadowPokemonCheckbox);
	AddElement(CurrentPokemonSwitcher);
}

void TrainerPokemon::InitPokemonInfoGroup()
{
	//PokemonInfoGroup = std::make_shared<UiGroup>("Pokemon Info", ParentTrainerPokemon);
	//PokemonInfoGroup->SetSameLine(true);
	//PokemonInfoGroup->SetIsFixedSize(true);

	auto PokemonInfoText = std::make_shared<SimpleSectionDivider>("Pokemon Info", ParentTrainerPokemon);
	PokemonInfoText->SetNumSpaceLengths(1);

	auto PokemonComboBox = std::make_shared<CSVComboBox>(
		std::format("Species##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Species",
		"Pokemon Stats",
		"Entry Name"
	);
	RowElements.push_back(PokemonComboBox);

	auto LevelIntBox = std::make_shared<CSVIntBox>(
		std::format("Level##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Level",
		1,
		5
	);
	RowElements.push_back(LevelIntBox);

	auto HappinessIntBox = std::make_shared<CSVIntBox>(
		std::format("Happiness##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Happiness",
		1,
		5
	);
	RowElements.push_back(HappinessIntBox);

	auto ItemComboBox = std::make_shared<CSVComboBox>(
		std::format("Item##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Item",
		"Item",
		"Entry Name"
	);
	RowElements.push_back(ItemComboBox);

	auto GenderComboBox = std::make_shared<CSVComboBox>(
		std::format("Gender##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Gender",
		"Gender",
		"Gender"
	);
	RowElements.push_back(GenderComboBox);

	auto NatureComboBox = std::make_shared<CSVComboBox>(
		std::format("Nature##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Nature",
		"Nature",
		"Entry Name"
	);

	NatureComboBox->SetStartWithCapitalLetter(true);

	RowElements.push_back(NatureComboBox);

	AddElement(PokemonInfoText);
	AddElement(PokemonComboBox);
	AddElement(LevelIntBox);
	AddElement(ItemComboBox);
	AddElement(GenderComboBox);
	AddElement(NatureComboBox);
	AddElement(HappinessIntBox);
}

void TrainerPokemon::InitIvEvGrid()
{
	AddElement(std::make_shared<SimpleSectionDivider>("IVs and EVs", ParentTrainerPokemon));

	IvEvGrid = std::make_shared<UiElementGrid>("##IVEV Grid", ParentTrainerPokemon);
	IvEvGrid->SetMinColumns(3);
	IvEvGrid->SetMaxColumns(3);
	IvEvGrid->SetShouldAlignElements(true);
	IvEvGrid->SetShouldOverrideSyncedSize(true);

	IvEvGrid->AddElement(std::make_shared<SimpleText>("Stat:", ParentTrainerPokemon), true);
	IvEvGrid->AddElement(std::make_shared<SimpleText>("IVS", ParentTrainerPokemon), true);
	IvEvGrid->AddElement(std::make_shared<SimpleText>("EVS", ParentTrainerPokemon), true);

	const std::vector<std::string> StatNames =
	{
		"HP:",
		"Attack:",
		"Defense:",
		"Sp. Atk:",
		"Sp. Def:",
		"Speed:"
	};

	const std::vector<std::string> IVsColumns =
	{
		"IVs HP",
		"IVs Attack",
		"IVs Defense",
		"IVs Sp.Atk",
		"IVs Sp.Def",
		"IVs Speed"
	};

	const std::vector<std::string> EVsColumns =
	{
		"EVs HP",
		"EVs Attack",
		"EVs Defense",
		"EVs Sp.Atk",
		"EVs Sp.Def",
		"EVs Speed"
	};

	for (int32_t i = 0; i < StatNames.size(); i++)
	{
		IvEvGrid->AddElement(std::make_shared<SimpleText>(StatNames[i], ParentTrainerPokemon), true);
		InitIVElement(StatNames[i], IVsColumns[i]);
		InitEVElement(StatNames[i], EVsColumns[i]);
	}

	IvEvGrid->AddElement(std::make_shared<SimpleText>("Total:", ParentTrainerPokemon), true);

	TotalIvBox = std::make_shared<SimpleIntBox>("##Total IVs Box", ParentTrainerPokemon);
	TotalIvBox->SetDisabled(true);
	TotalIvBox->SetElementMinSize(3);
	TotalIvBox->SetElementMaxSize(30);
	TotalIvBox->SetShouldOverrideSyncedSize(false);

	TotalEvBox = std::make_shared<SimpleIntBox>("##Total EVs Box", ParentTrainerPokemon);
	TotalEvBox->SetDisabled(true);
	TotalEvBox->SetElementMinSize(3);
	TotalEvBox->SetElementMaxSize(30);
	TotalEvBox->SetShouldOverrideSyncedSize(false);

	IvEvGrid->AddElement(TotalIvBox, true);
	IvEvGrid->AddElement(TotalEvBox, true);

	AddElement(IvEvGrid);
}

void TrainerPokemon::InitIVElement(const std::string& ItemName, const std::string& ItemColumn)
{
	auto IvIntBox = std::make_shared<CSVIntBox>(
		std::format("##{}IV-{}", ItemName, PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		ItemColumn,
		1,
		5
	);

	IvElements.push_back(IvIntBox);

	IvIntBox->SetBounds(0, 31);
	IvIntBox->SetElementMinSize(3);
	IvIntBox->SetIsFixedSize(true);
	IvIntBox->SetShouldOverrideSyncedSize(false);
	RowElements.push_back(IvIntBox);
	IvEvGrid->AddElement(IvIntBox, true);
}

void TrainerPokemon::InitEVElement(const std::string& ItemName, const std::string& ItemColumn)
{
	auto EvIntBox = std::make_shared<CSVIntBox>(
		std::format("##{}EV-{}", ItemName, PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		ItemColumn,
		4,
		8
	);

	EvElements.push_back(EvIntBox);

	EvIntBox->SetBounds(0, 255);
	EvIntBox->SetElementMinSize(3);
	EvIntBox->SetIsFixedSize(true);
	EvIntBox->SetShouldOverrideSyncedSize(false);
	RowElements.push_back(EvIntBox);
	IvEvGrid->AddElement(EvIntBox, true);
}

void TrainerPokemon::InitMovesGroup()
{
	AddElement(std::make_shared<SimpleSectionDivider>("Moves", ParentTrainerPokemon));

	for (int32_t MoveIndex = 1; MoveIndex <= 4; MoveIndex++)
	{
		InitMoveElement(MoveIndex);
	}
}

void TrainerPokemon::InitMoveElement(int32_t MoveIndex)
{
	auto MoveComboBox = std::make_shared<CSVComboBox>(
		std::format("Moves {}##Move-{}", MoveIndex, PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		std::format("Moves {}", MoveIndex),
		"Move",
		"Entry Name"
	);

	RowElements.push_back(MoveComboBox);
	AddElement(MoveComboBox);
}

void TrainerPokemon::InitMiscGroup()
{
	AddElement(std::make_shared<SimpleSectionDivider>("Misc", ParentTrainerPokemon));

	auto UseSpeciesSecondAbilityCheckbox = std::make_shared<CSVCheckbox>(
		std::format("Use Species Second Ability##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Use species second ability"
	);
	UseSpeciesSecondAbilityCheckbox->SetShouldOverrideSyncedSize(false);
	RowElements.push_back(UseSpeciesSecondAbilityCheckbox);

	auto UseRandomNatureAndGenderCheckbox = std::make_shared<CSVCheckbox>(
		std::format("Use Random Nature and Gender##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Use Random Nature and Gender"
	);
	UseRandomNatureAndGenderCheckbox->SetShouldOverrideSyncedSize(false);
	RowElements.push_back(UseRandomNatureAndGenderCheckbox);

	AddElement(UseSpeciesSecondAbilityCheckbox);
	AddElement(UseRandomNatureAndGenderCheckbox);

	auto AiRoleComboBox = std::make_shared<CSVComboBox>(
		std::format("AI Role##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"AI Role",
		"Pokemon AI Roles",
		"Entry Name"
	);

	// Needed because for some reason AI role entries have two spaces between the
	// string and value.
	AiRoleComboBox->SetEntriesNumWhitespace(2);

	AiRoleComboBox->SetSizeConstraintsDisabled(true);
	RowElements.push_back(AiRoleComboBox);

	// Must be an int box because this field's values go above 1
	auto IsKeyStrategicPokemonIntBox = std::make_shared<CSVIntBox>(
		std::format("Is Key Strategic Pokemon?##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Is Key Strategic Pokemon",
		1,
		5
	);
	RowElements.push_back(IsKeyStrategicPokemonIntBox);

	AddElement(AiRoleComboBox);
	AddElement(IsKeyStrategicPokemonIntBox);

	InitComboRoleElement("A", 1);
	InitComboRoleElement("A", 2);
	InitComboRoleElement("B", 1);
	InitComboRoleElement("B", 2);
}

void TrainerPokemon::InitComboRoleElement(const std::string& ComboName, int32_t RoleNum)
{
	auto ComboRoleCheckbox = std::make_shared<CSVCheckbox>(
		std::format("Can Fill Combo {} Role {}##{}", ComboName, RoleNum, PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		std::format("Can Fill Combo {} Role {}", ComboName, RoleNum)
	);

	ComboRoleCheckbox->SetShouldOverrideSyncedSize(false);
	RowElements.push_back(ComboRoleCheckbox);
	AddElement(ComboRoleCheckbox);
}

void TrainerPokemon::InitShadowPokemonInfo()
{
	ShadowPokemonSwitcher = std::make_shared<UiElementSwitcher>(
		std::format("##ShadowPokemonSwitcher{}", PartyIndex),
		ParentTrainerPokemon
	);

	ShadowPokemonGroup = std::make_shared<UiGroup>(std::format("##ShadowPokemonGroup{}", PartyIndex), ParentTrainerPokemon);
	NonShadowPokemonGroup = std::make_shared<UiGroup>(std::format("##NonShadowPokemonGroup{}", PartyIndex), ParentTrainerPokemon);

	auto ShadowPokemonText = std::make_shared<SimpleSectionDivider>("Shadow Pokemon Info", ParentTrainerPokemon);

	auto ShadowPokemonIndex = std::make_shared<CSVComboBox>(
		std::format("Story Deck ID##{}", PartyIndex),
		ParentTrainerPokemon,
		"Shadow Pokemon",
		"Pokemon Index In Story Deck",
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Entry Name"
	);
	ShadowPokemonIndex->SetEntriesNumWhitespace(2);
	ShadowPokemonElements.push_back(ShadowPokemonIndex);

	auto ShadowPokemonLevel = std::make_shared<CSVIntBox>(
		std::format("Level (When Caught)##{}", PartyIndex),
		ParentTrainerPokemon,
		"Shadow Pokemon",
		"Level",
		1,
		5
	);
	ShadowPokemonElements.push_back(ShadowPokemonLevel);

	auto HeartGuageIntBox = std::make_shared<CSVIntBox>(
		std::format("Heart Guage##{}", PartyIndex),
		ParentTrainerPokemon,
		"Shadow Pokemon",
		"Heart Guage",
		1,
		5
	);
	ShadowPokemonElements.push_back(HeartGuageIntBox);

	ShadowPokemonGroup->AddElement(ShadowPokemonText);
	ShadowPokemonGroup->AddElement(ShadowPokemonIndex);
	ShadowPokemonGroup->AddElement(ShadowPokemonLevel);
	ShadowPokemonGroup->AddElement(HeartGuageIntBox);

	for (int32_t i = 1; i <= 4; i++)
	{
		auto MoveElement = std::make_shared<CSVComboBox>(
			std::format("Shadow Move {}##{}-{}", i, PartyIndex, i),
			ParentTrainerPokemon,
			"Shadow Pokemon",
			std::format("Shadow Moves {}", i),
			"Move",
			"Entry Name"
		);
		ShadowPokemonElements.push_back(MoveElement);
		ShadowPokemonGroup->AddElement(MoveElement);
	}

	auto ShadowPokemonCatchRateIntBox = std::make_shared<CSVIntBox>(
		std::format("Catch Rate##{}", PartyIndex),
		ParentTrainerPokemon,
		"Shadow Pokemon",
		"Catch Rate",
		1,
		5
	);
	ShadowPokemonElements.push_back(ShadowPokemonCatchRateIntBox);

	auto MirorBWeightingIntBox = std::make_shared<CSVIntHexBox>(
		std::format("Miror B Weighting##{}", PartyIndex),
		ParentTrainerPokemon,
		"Shadow Pokemon",
		"Miror B weighting",
		1,
		5
	);
	ShadowPokemonElements.push_back(MirorBWeightingIntBox);

	auto ShadowIDIsBeingUsedCheckbox = std::make_shared<CSVCheckbox>(
		std::format("Shadow ID is Being used?##{}", PartyIndex),
		ParentTrainerPokemon,
		"Shadow Pokemon",
		"Shadow ID Is Being Used"
	);
	ShadowPokemonElements.push_back(ShadowIDIsBeingUsedCheckbox);

	auto ShadowPokemonAggressionIntBox = std::make_shared<CSVIntHexBox>(
		std::format("Aggression##{}", PartyIndex),
		ParentTrainerPokemon,
		"Shadow Pokemon",
		"Aggression",
		1,
		5
	);
	ShadowPokemonElements.push_back(ShadowPokemonAggressionIntBox);

	auto FleesWhenPlayerLosesCheckbox = std::make_shared<CSVCheckbox>(
		std::format("Flees When Player Loses?##{}", PartyIndex),
		ParentTrainerPokemon,
		"Shadow Pokemon",
		"Flees When Player Loses"
	);
	ShadowPokemonElements.push_back(FleesWhenPlayerLosesCheckbox);
	
	ShadowPokemonGroup->AddElement(ShadowIDIsBeingUsedCheckbox);
	ShadowPokemonGroup->AddElement(ShadowPokemonCatchRateIntBox);
	ShadowPokemonGroup->AddElement(MirorBWeightingIntBox);
	ShadowPokemonGroup->AddElement(ShadowPokemonAggressionIntBox);
	ShadowPokemonGroup->AddElement(FleesWhenPlayerLosesCheckbox);
	
	ShadowPokemonSwitcher->AddElement(ShadowPokemonGroup);
	ShadowPokemonSwitcher->AddElement(NonShadowPokemonGroup);

	AddElement(ShadowPokemonSwitcher);
}
