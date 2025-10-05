#pragma once

#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"

class CSVComboBox;
class EvolutionCondition;
class EvolutionMethod;

class EvolutionElement : public UiSingleLineMultiElement
{

public:

	EvolutionElement(
		const std::string& InName, 
		UiSection* InParent,
		int32_t InEvolutionNumber
	);

	int32_t GetCurrentMethod() const;

	std::shared_ptr<EvolutionCondition> GetEvolutionCondition() const;

private:

	std::shared_ptr<EvolutionMethod> MethodComboBox;

	std::shared_ptr<CSVComboBox> FormComboBox;

	std::shared_ptr<EvolutionCondition> EvolutionConditionSwitcher;

};
