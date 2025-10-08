/*****************************************************************//**
 * \file   EvolutionElement.h
 * \brief  Ui element for editing a single evolution of a Pokemon.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"

class CSVComboBox;
class EvolutionCondition;
class EvolutionMethod;

/**
 * \brief  Ui element for editing a single evolution of a Pokemon.
 * 
 * This element contains a combo box for selecting the evolution method,
 * a combo box for selecting the form to evolve into,
 * and an EvolutionCondition element for specifying the condition
 * required for the evolution to occur.
 */
class EvolutionElement : public UiSingleLineMultiElement
{

public:

	/** Construct an EvolutionElement with the specified Evolution Number */
	EvolutionElement(
		const std::string& InName, 
		UiSection* InParent,
		int32_t InEvolutionNumber
	);

	/** Get the current evolution method index. */
	int32_t GetCurrentMethod() const;

	/** Get the EvolutionCondition for this EvolutionElement. */
	std::shared_ptr<EvolutionCondition> GetEvolutionCondition() const;

private:

	/** The EvolutionMethod for this EvolutionElement */
	std::shared_ptr<EvolutionMethod> MethodComboBox;

	/** The form to evolve into for this EvolutionElement */
	std::shared_ptr<CSVComboBox> FormComboBox;

	/** The EvolutionCondition for this EvolutionElement */
	std::shared_ptr<EvolutionCondition> EvolutionConditionSwitcher;

};
