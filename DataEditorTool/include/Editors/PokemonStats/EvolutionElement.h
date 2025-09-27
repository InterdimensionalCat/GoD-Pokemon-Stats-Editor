#pragma once

#include "UI/MultiLineUiElement.h"

class CSVComboBox;
class EvolutionCondition;

class EvolutionElement : public MultiLineUiElement
{

public:

	EvolutionElement(
		const std::string& InName, 
		UiSection* InParent,
		int32_t InEvolutionNumber
	);

	int32_t GetCurrentMethod() const;

private:

	std::shared_ptr<CSVComboBox> MethodComboBox;

	std::shared_ptr<CSVComboBox> FormComboBox;

	std::shared_ptr<EvolutionCondition> EvolutionConditionSwitcher;

};
