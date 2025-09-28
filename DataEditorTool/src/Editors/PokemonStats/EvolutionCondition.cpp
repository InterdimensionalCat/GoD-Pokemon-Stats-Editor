#include "include.h"
#include "Editors/PokemonStats/EvolutionCondition.h"
#include "Editors/PokemonStats/EvolutionElement.h"
#include "Editors/PokemonStats/PokemonStatsEvolutionInfo.h"
#include "UI/BasicUiElements/IntHexStringBox.h"
#include "UI/BasicUiElements/CSVComboBoxInt.h"

EvolutionCondition::EvolutionCondition
(
	const std::string& InName,
	UiSection* InParent,
	EvolutionElement* InParentElement,
	int32_t InEvolutionNumber
) : 
	UiElementSwitcher(InName, InParent),
	ParentElement(InParentElement)
{

	const std::string CSVName = "Pokemon Stats";

	std::string ConditionColumnName = std::format("Evolutions {} Evolution Condition", InEvolutionNumber);
	std::string NoParamBoxName = std::format("##Evo-No Condition{}", InEvolutionNumber);

	NoParamBox = std::make_shared<IntHexStringBox>(NoParamBoxName, InParent, CSVName, ConditionColumnName, 1, 5);
	NoParamBox->SetDisabled(true);
	NoParamBox->SetElementMinSize(4);

	std::string LevelBoxName = std::format("##Evo-Level{}", InEvolutionNumber);
	LevelBox = std::make_shared<IntHexStringBox>(LevelBoxName, InParent, CSVName, ConditionColumnName, 1, 5);
	LevelBox->SetElementMinSize(4);

	std::string ItemBoxName = std::format("##Evo-Item{}", InEvolutionNumber);
	ItemBox = std::make_shared<CSVComboBoxInt>(ItemBoxName, InParent, CSVName, ConditionColumnName, "Item", "Entry Name");

	std::string StoneBoxName = std::format("##Evo-Stone{}", InEvolutionNumber);
	StoneBox = std::make_shared<CSVComboBoxInt>(StoneBoxName, InParent, CSVName, ConditionColumnName, "EvolutionStone", "Item ID");

	std::string BeautyBoxName = std::format("##Evo-Beauty{}", InEvolutionNumber);
	BeautyBox = std::make_shared<IntHexStringBox>(BeautyBoxName, InParent, CSVName, ConditionColumnName, 1, 5);
	BeautyBox->SetElementMinSize(4);

	std::string KeyItemBoxName = std::format("##Evo-KeyItem{}", InEvolutionNumber);
	KeyItemBox = std::make_shared<CSVComboBoxInt>(KeyItemBoxName, InParent, CSVName, ConditionColumnName, "KeyItem", "Key Item ID");

	AddCSVElement(NoParamBox);
	AddCSVElement(LevelBox);
	AddCSVElement(ItemBox);
	AddCSVElement(StoneBox);
	AddCSVElement(BeautyBox);
	AddCSVElement(KeyItemBox);

	SwitchCurrentlyActiveElement(NoParamBox);
}

void EvolutionCondition::Refresh()
{
	SwitchCondition(ParentElement->GetCurrentMethod());
	CurrentlyActiveElement->Refresh();
}

void EvolutionCondition::PushConstrainedSizeForElement(const uint32_t ElementIndex)
{
	// The currently active element can use whatever size was pushed for
	// this multi ui element.

	// TODO: This should probably be in UiElementSwitcher
}

void EvolutionCondition::PopConstrainedSizeForElement(const uint32_t ElementIndex)
{
	// implementation left intentionally blank for the above reason.
}

void EvolutionCondition::SwitchCondition(const int32_t ConditionIndex)
{
	EvoConditionType NewConditionType = static_cast<EvoConditionType>(ConditionIndex);
	switch (NewConditionType)
	{
	case EvoConditionType::None:
		[[fallsthrough]]
	case EvoConditionType::MaxHappiness:
		[[fallsthrough]]
	case EvoConditionType::HappinessDay:
		[[fallsthrough]]
	case EvoConditionType::HappinessNight:
		[[fallsthrough]]
	case EvoConditionType::Trade:
		// All of the above methods use no condition
		SwitchCurrentlyActiveElement(NoParamBox);
		break;
	case EvoConditionType::LevelUp:
		[[fallsthrough]]
	case EvoConditionType::AtkOverDef:
		[[fallsthrough]]
	case EvoConditionType::AtkEqualsDef:
		[[fallsthrough]]
	case EvoConditionType::AtkUnderDef:
		[[fallsthrough]]
	case EvoConditionType::Silcoon:
		[[fallsthrough]]
	case EvoConditionType::Cascoon:
		[[fallsthrough]]
	case EvoConditionType::Ninjask:
		[[fallsthrough]]
	case EvoConditionType::Shedinja:
		// All of the above methods use a level condition.
		SwitchCurrentlyActiveElement(LevelBox);
		break;
	case EvoConditionType::TradeWithItem:
		// Trade with item uses any item as a condition
		SwitchCurrentlyActiveElement(ItemBox);
		break;
	case EvoConditionType::EvolutionStone:
		// Evolution Stone uses only evolution stone items as a condition
		SwitchCurrentlyActiveElement(StoneBox);
		break;
	case EvoConditionType::MaxBeauty:
		// Max Beauty uses a beauty value int condition
		SwitchCurrentlyActiveElement(BeautyBox);
		break;
	case EvoConditionType::LevelUpKeyItem:
		// Level Up with Key Item uses a unique Key item identifier item, 
		// whos ID is (Item ID + 150)
		SwitchCurrentlyActiveElement(KeyItemBox);
		break;
	}
}
