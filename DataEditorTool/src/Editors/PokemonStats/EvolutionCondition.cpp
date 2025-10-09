#include "include.h"
#include "Editors/PokemonStats/EvolutionCondition.h"
#include "Editors/PokemonStats/EvolutionElement.h"
#include "Editors/PokemonStats/PokemonStatsEvolutionInfo.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntHexBox.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVIntHexComboBox.h"

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

	NoParamBox = std::make_shared<CSVIntHexBox>(NoParamBoxName, InParent, CSVName, ConditionColumnName, 1, 5);
	NoParamBox->SetDisabled(true);
	NoParamBox->SetElementMinSize(4);

	std::string LevelBoxName = std::format("##Evo-Level{}", InEvolutionNumber);
	LevelBox = std::make_shared<CSVIntHexBox>(LevelBoxName, InParent, CSVName, ConditionColumnName, 1, 5);
	LevelBox->SetElementMinSize(4);

	std::string ItemBoxName = std::format("##Evo-Item{}", InEvolutionNumber);
	ItemBox = std::make_shared<CSVIntHexComboBox>(ItemBoxName, InParent, CSVName, ConditionColumnName, "Item", "Entry Name");

	std::string StoneBoxName = std::format("##Evo-Stone{}", InEvolutionNumber);
	StoneBox = std::make_shared<CSVIntHexComboBox>(StoneBoxName, InParent, CSVName, ConditionColumnName, "EvolutionStone", "Item ID");

	std::string BeautyBoxName = std::format("##Evo-Beauty{}", InEvolutionNumber);
	BeautyBox = std::make_shared<CSVIntHexBox>(BeautyBoxName, InParent, CSVName, ConditionColumnName, 1, 5);
	BeautyBox->SetElementMinSize(4);

	std::string KeyItemBoxName = std::format("##Evo-KeyItem{}", InEvolutionNumber);
	KeyItemBox = std::make_shared<CSVIntHexComboBox>(KeyItemBoxName, InParent, CSVName, ConditionColumnName, "KeyItem", "Key Item ID");

	AddElement(NoParamBox);
	AddElement(LevelBox);
	AddElement(ItemBox);
	AddElement(StoneBox);
	AddElement(BeautyBox);
	AddElement(KeyItemBox);

	SwitchCurrentlyActiveElement(NoParamBox);
}

void EvolutionCondition::Refresh()
{
	SwitchCondition(ParentElement->GetCurrentMethod());
	CurrentlyActiveElement->Refresh();
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
		// whose ID is (Item ID + 150)
		SwitchCurrentlyActiveElement(KeyItemBox);
		break;
	}
}

int32_t EvolutionCondition::GetDefaultForCondition(const int32_t ConditionIndex)
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
		return 0;
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
		return 0;
	case EvoConditionType::TradeWithItem:
		// Trade with item uses any item as a condition
		return 0;
	case EvoConditionType::EvolutionStone:
		// Evolution Stone uses only evolution stone items as a condition
		return 93; // 93 is the item ID for the Sun Stone, which is the first stone ID.
	case EvoConditionType::MaxBeauty:
		// Max Beauty uses a beauty value int condition
		return 0;
	case EvoConditionType::LevelUpKeyItem:
		// Level Up with Key Item uses a unique Key item identifier item, 
		// whose ID is (Item ID + 150)
		return 500; // 500 is the key item ID for the Safe Key, which is the first key item ID.
	default:
		return 0;
	}
}

std::string EvolutionCondition::GetCSVFileName() const
{
	return LevelBox->GetCSVFileName();
}

std::string EvolutionCondition::GetColumnName() const
{
	return LevelBox->GetColumnName();
}

int32_t EvolutionCondition::GetCurrentRow() const
{
	return LevelBox->GetCurrentRow();
}