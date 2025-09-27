#pragma once

#include "UI/UiElementSwitcher.h"

class IntHexStringBox;
class CSVComboBoxInt;
class EvolutionElement;

enum class EvoConditionType : int32_t
{
	None = 0,
	MaxHappiness = 1,
	HappinessDay = 2,
	HappinessNight = 3,
	LevelUp = 4,
	Trade = 5,
	TradeWithItem = 6,
	EvolutionStone =  7,
	AtkOverDef = 8,
	AtkEqualsDef = 9,
	AtkUnderDef = 10,
	Silcoon = 11,
	Cascoon = 12,
	Ninjask = 13,
	Shedinja = 14,
	MaxBeauty = 15,
	LevelUpKeyItem = 16
};

class EvolutionCondition : public UiElementSwitcher
{

public:

	EvolutionCondition(
		const std::string& InName, 
		UiSection* InParent,
		EvolutionElement* InParentElement,
		int32_t InEvolutionNumber
	);

	virtual void Refresh() override;

	virtual void PushConstrainedSizeForElement(const uint32_t ElementIndex) override;

	virtual void PopConstrainedSizeForElement(const uint32_t ElementIndex) override;

	void SwitchCondition(const int32_t ConditionIndex);

private:

	EvolutionElement* ParentElement;

	std::shared_ptr<IntHexStringBox> NoParamBox;
	
	std::shared_ptr<IntHexStringBox> LevelBox;

	std::shared_ptr<CSVComboBoxInt> ItemBox;

	std::shared_ptr<CSVComboBoxInt> StoneBox;

	std::shared_ptr<IntHexStringBox> BeautyBox;

	std::shared_ptr<CSVComboBoxInt> KeyItemBox;
	
};