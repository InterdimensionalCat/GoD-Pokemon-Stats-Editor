/*****************************************************************//**
 * \file   EvolutionCondition.h
 * \brief  UiElementSwitcher that switches between different evolution condition input elements.
 * 
 * \author bthomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiElementSwitcher.h"

class CSVIntHexBox;
class CSVIntHexComboBox;
class EvolutionElement;

/** The different types of evolution conditions that can be selected. */
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

/**
 * \brief  UiElementSwitcher that switches between different evolution condition input elements.
 * 
 * Each evolution condition type uses the same parameter field
 * in the CSV file, but the meaning of that parameter and the
 * valid range of values for that parameter depends on the
 * evolution method selected. This class switches between
 * different input elements depending on the evolution method
 * to allow the user to easily input an appropriate value.
 */
class EvolutionCondition : public UiElementSwitcher
{

public:

	/** Construct an EvolutionCondition with the specified parent EvolutionElement and evolution number. */
	EvolutionCondition(
		const std::string& InName, 
		UiSection* InParent,
		EvolutionElement* InParentElement,
		int32_t InEvolutionNumber
	);

	/** Switch the displayed element to match the currently selected EvolutionMethod */
	virtual void Refresh() override;

	/** Switch the displayed element to match the specified condition index. */
	void SwitchCondition(const int32_t ConditionIndex);

	/** Get the first valid value (which we use as a default) for the condition the condition index. */
	int32_t GetDefaultForCondition(const int32_t ConditionIndex);

	/** Get the CSV file name this element manages. */
	std::string GetCSVFileName() const;

	/** Get the column name this element manages. */
	std::string GetColumnName() const;

	/** Get the current row this element manages. */
	int32_t GetCurrentRow() const;

private:

	/** The parent EvolutionElement for this EvolutionCondition. */
	EvolutionElement* ParentElement;

	/**
	 * Display a disabled IntBox if the evolution method does not use
	 * the evolution condition parameter.
	 * This is used for:
	 * None
	 * Max Happiness
	 * Happiness (Day)
	 * Happiness (Night)
	 * Trade
	 */
	std::shared_ptr<CSVIntHexBox> NoParamBox;
	
	/**
	 * Display an IntBox for evolution methods that use a level parameter.
	 * This is used for:
	 * Level Up
	 * Atk > Def
	 * Atk = Def
	 * Atk < Def
	 * Silcoon
	 * Cascoon
	 * Ninjask
	 * Shedinja
	 */
	std::shared_ptr<CSVIntHexBox> LevelBox;

	/**
	 * Display an item combo box for evolution methods use
	 * an item parameter.
	 * This is used for:
	 * Trade With Item
	 * 
	 */
	std::shared_ptr<CSVIntHexComboBox> ItemBox;

	/**
	 * Display an item combo box limited to just
	 * evolution stones for evolution methods that
	 * use an evolution stone parameter.
	 * This is used for:
	 * Evolution Stone
	 */
	std::shared_ptr<CSVIntHexComboBox> StoneBox;

	/**
	 * Display an IntBox for evolution methods that use
	 * a beauty parameter.
	 * This is used for:
	 * Max Beauty
	 */
	std::shared_ptr<CSVIntHexBox> BeautyBox;

	/**
	 * Display an item combo box limited to just
	 * key items for evolution methods that
	 * use a key item parameter. The item IDs
	 * for key items are offset by 150 in the
	 * evolution condition parameter.
	 * This is used for:
	 * Level Up With Key Item
	 */
	std::shared_ptr<CSVIntHexComboBox> KeyItemBox;
	
};