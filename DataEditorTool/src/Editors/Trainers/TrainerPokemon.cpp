#include "include.h"
#include "Editors/Trainers/TrainerPokemon.h"
#include "Editors/Trainers/TrainersEditorTrainerPokemon.h"
#include "Editors/Trainers/TrainersEditor.h"
#include "UI/UiElement/UiMultiElement/UiChildWindow.h"
#include "UI/UiElement/UiMultiElement/UiGroup.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleImageBox.h"
#include "Pokeface/PokefaceData.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVComboBox.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntBox.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntSlider.h"
#include "UI/UiElement/UiCSVElement/BoolElement/CSVCheckbox.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleText.h"

TrainerPokemon::TrainerPokemon(
	const std::string& InName,
	TrainersEditorTrainerPokemon* InParent,
	int32_t InPartyIndex
) :
	UiSingleLineMultiElement(InName, InParent),
	ParentTrainerPokemon(InParent),
	PartyIndex(InPartyIndex)
{
	InitPokefaceGroup();
	InitPokemonInfoGroup();
	InitIVsGroup();
	InitEVsGroup();
	InitMovesGroup();
	InitMiscGroup();

	AddElement(PokefaceGroup);
	AddElement(PokemonInfoGroup);
	AddElement(IVsGroup);
	AddElement(EVsGroup);
	AddElement(MovesGroup);
	AddElement(MiscGroup);
	SetCurrentRow(1);
}

void TrainerPokemon::Refresh()
{
	// Set the correct PokeFace image based
	// on the current row.
	const auto& PokefaceDataIds = PokefaceData::GetPokefaceData();

	if (!PokefaceDataIds.empty())
	{
		PokefaceImage->SetTexture(PokefaceDataIds.at(GetCurrentRow()));
	}

	UiMultiElement::Refresh();
}

void TrainerPokemon::SetCurrentRow(const int32_t InRow)
{
	CurrentRow = InRow;
}

int32_t TrainerPokemon::GetCurrentRow() const
{
	return CurrentRow;
}

void TrainerPokemon::InitPokefaceGroup()
{
	// Contains the Pokeface image.
	// TODO: should contain the current Pokemon combo box as well.
	PokefaceGroup = std::make_shared<UiGroup>("Pokeface Group", ParentTrainerPokemon);
	PokefaceGroup->SetIsFixedSize(true);

	PokefaceImage = std::make_shared<SimpleImageBox>("##PokefaceImage", ParentTrainerPokemon);
	PokefaceImage->SetShouldOverrideSyncedSize(false);

	const auto& PokefaceDataIds = PokefaceData::GetPokefaceData();
	if (!PokefaceDataIds.empty())
	{
		PokefaceImage->SetTexture(PokefaceDataIds.at(0));
	}

	PokefaceImage->SetImageSize(ImGui::GetFrameHeightWithSpacing() * 6);
	PokefaceGroup->AddElement(PokefaceImage);
}

void TrainerPokemon::InitPokemonInfoGroup()
{
	PokemonInfoGroup = std::make_shared<UiGroup>("Pokemon Info", ParentTrainerPokemon);
	PokemonInfoGroup->SetSameLine(true);
	PokemonInfoGroup->SetIsFixedSize(true);

	auto PokemonInfoText = std::make_shared<SimpleText>("Pokemon Info", ParentTrainerPokemon);

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

	auto AiRoleComboBox = std::make_shared<CSVComboBox>(
		std::format("AI Role##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"AI Role",
		"Pokemon AI Roles",
		"Entry Name"
	);
	AiRoleComboBox->SetSizeConstraintsDisabled(true);
	RowElements.push_back(AiRoleComboBox);

	auto IsKeyStrategicPokemonIntBox = std::make_shared<CSVIntBox>(
		std::format("Is Key Poke##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Is Key Strategic Pokemon",
		1,
		5
	);
	RowElements.push_back(IsKeyStrategicPokemonIntBox);

	PokemonInfoGroup->AddElement(PokemonInfoText);
	PokemonInfoGroup->AddElement(PokemonComboBox);
	PokemonInfoGroup->AddElement(LevelIntBox);
	PokemonInfoGroup->AddElement(HappinessIntBox);
	PokemonInfoGroup->AddElement(ItemComboBox);
	PokemonInfoGroup->AddElement(AiRoleComboBox);
	PokemonInfoGroup->AddElement(IsKeyStrategicPokemonIntBox);
}

void TrainerPokemon::InitIVsGroup()
{
	IVsGroup = std::make_shared<UiGroup>("IVs Group", ParentTrainerPokemon);
	IVsGroup->SetSameLine(true);
	IVsGroup->SetIsFixedSize(true);

	auto IVSText = std::make_shared<SimpleText>("IVs", ParentTrainerPokemon);
	IVsGroup->AddElement(IVSText);

	const std::vector<std::string> IVsNames =
	{
		"HP",
		"Atk",
		"Def",
		"SpA",
		"SpD",
		"Spe"
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

	for(int32_t i = 0; i < IVsNames.size(); i++)
	{
		InitIVElement(IVsNames[i], IVsColumns[i]);
	}
}

void TrainerPokemon::InitIVElement(const std::string& ItemName, const std::string& ItemColumn)
{
	auto IvIntBox = std::make_shared<CSVIntBox>(
		std::format("{}##IV-{}", ItemName, PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		ItemColumn,
		1,
		5
	);
	IvIntBox->SetBounds(0, 31);
	IvIntBox->SetElementMinSize(3);
	IvIntBox->SetIsFixedSize(true);
	IvIntBox->SetShouldOverrideSyncedSize(false);
	RowElements.push_back(IvIntBox);
	IVsGroup->AddElement(IvIntBox);
}

void TrainerPokemon::InitEVsGroup()
{
	EVsGroup = std::make_shared<UiGroup>("EVs Group", ParentTrainerPokemon);
	EVsGroup->SetSameLine(true);
	EVsGroup->SetIsFixedSize(true);

	auto EVSText = std::make_shared<SimpleText>("EVs", ParentTrainerPokemon);
	EVsGroup->AddElement(EVSText);

	const std::vector<std::string> EVsNames =
	{
		"HP",
		"Atk",
		"Def",
		"SpA",
		"SpD",
		"Spe"
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

	for (int32_t i = 0; i < EVsNames.size(); i++)
	{
		InitEVElement(EVsNames[i], EVsColumns[i]);
	}
}

void TrainerPokemon::InitEVElement(const std::string& ItemName, const std::string& ItemColumn)
{
	auto EvIntBox = std::make_shared<CSVIntBox>(
		std::format("{}##EV-{}", ItemName, PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		ItemColumn,
		4,
		8
	);
	EvIntBox->SetBounds(0, 255);
	EvIntBox->SetElementMinSize(3);
	EvIntBox->SetIsFixedSize(true);
	EvIntBox->SetShouldOverrideSyncedSize(false);
	RowElements.push_back(EvIntBox);
	EVsGroup->AddElement(EvIntBox);
}

void TrainerPokemon::InitMovesGroup()
{
	MovesGroup = std::make_shared<UiGroup>("Moves Group", ParentTrainerPokemon);
	MovesGroup->SetSameLine(true);

	auto MovesText = std::make_shared<SimpleText>("Moves", ParentTrainerPokemon);
	MovesGroup->AddElement(MovesText);

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
	RowElements.push_back(NatureComboBox);

	MovesGroup->AddElement(GenderComboBox);
	MovesGroup->AddElement(NatureComboBox);

	for (int32_t MoveIndex = 1; MoveIndex <= 4; MoveIndex++)
	{
		InitMoveElement(MoveIndex);
	}
}

void TrainerPokemon::InitMoveElement(int32_t MoveIndex)
{
	auto MoveComboBox = std::make_shared<CSVComboBox>(
		std::format("Moves{}##Move-{}", MoveIndex, PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		std::format("Moves {}", MoveIndex),
		"Move",
		"Entry Name"
	);

	RowElements.push_back(MoveComboBox);
	MovesGroup->AddElement(MoveComboBox);
}

void TrainerPokemon::InitMiscGroup()
{
	MiscGroup = std::make_shared<UiGroup>("Misc Group", ParentTrainerPokemon);
	MiscGroup->SetSameLine(true);
	MiscGroup->SetIsFixedSize(true);

	auto MiscText = std::make_shared<SimpleText>("Misc", ParentTrainerPokemon);
	MiscGroup->AddElement(MiscText);

	auto UseSpeciesSecondAbilityCheckbox = std::make_shared<CSVCheckbox>(
		std::format("Use 2nd Ability##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Use species second ability"
	);
	UseSpeciesSecondAbilityCheckbox->SetShouldOverrideSyncedSize(false);
	RowElements.push_back(UseSpeciesSecondAbilityCheckbox);

	auto UseRandomNatureAndGenderCheckbox = std::make_shared<CSVCheckbox>(
		std::format("Rand Nature/Gender##{}", PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		"Use Random Nature and Gender"
	);
	UseRandomNatureAndGenderCheckbox->SetShouldOverrideSyncedSize(false);
	RowElements.push_back(UseRandomNatureAndGenderCheckbox);

	MiscGroup->AddElement(UseSpeciesSecondAbilityCheckbox);
	MiscGroup->AddElement(UseRandomNatureAndGenderCheckbox);

	InitComboRoleElement("A", 1);
	InitComboRoleElement("A", 2);
	InitComboRoleElement("B", 1);
	InitComboRoleElement("B", 2);
}

void TrainerPokemon::InitComboRoleElement(const std::string& ComboName, int32_t RoleNum)
{
	auto ComboRoleCheckbox = std::make_shared<CSVCheckbox>(
		std::format("Combo {} Role {}##{}", ComboName, RoleNum, PartyIndex),
		ParentTrainerPokemon,
		ParentTrainerPokemon->GetParentEditor()->GetTrainerPokemonCSVFileName(),
		std::format("Can Fill Combo {} Role {}", ComboName, RoleNum)
	);

	ComboRoleCheckbox->SetShouldOverrideSyncedSize(false);
	RowElements.push_back(ComboRoleCheckbox);
	MiscGroup->AddElement(ComboRoleCheckbox);
}
