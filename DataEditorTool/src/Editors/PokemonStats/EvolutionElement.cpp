#include "include.h"
#include "Editors/PokemonStats/EvolutionElement.h"
#include "Editors/PokemonStats/EvolutionCondition.h"
#include "UI/BasicUiElements/CSVComboBox.h"
#include "UI/BasicUiElements/SimpleText.h"

EvolutionElement::EvolutionElement(
	const std::string& InName,
	UiSection* InParent,
	int32_t InEvolutionNumber
) :
	MultiLineUiElement(InName, InParent)
{
	const std::string CSVName = "Pokemon Stats";

	const std::string MethodComboBoxName = std::format("##MethodCombo {}", InEvolutionNumber);
	const std::string MethodComboBoxColumn = std::format("Evolutions {} Evolution Method", InEvolutionNumber);

	MethodComboBox = std::make_shared<CSVComboBox>(MethodComboBoxName, InParent, CSVName, MethodComboBoxColumn, "EvolutionMethod", "Method");

	const std::string FormComboBoxName = std::format("##FormCombo {}", InEvolutionNumber);
	const std::string FormComboBoxColumn = std::format("Evolutions {} Evolved Form", InEvolutionNumber);

	FormComboBox = std::make_shared<CSVComboBox>(FormComboBoxName, InParent, CSVName, FormComboBoxColumn, "Pokemon Stats", "Entry Name");

	const std::string ConditionSwitcherName = std::format("Condition {}", InEvolutionNumber);
	EvolutionConditionSwitcher = std::make_shared<EvolutionCondition>(ConditionSwitcherName, InParent, this, InEvolutionNumber);

	AddCSVElement(MethodComboBox);
	AddElement(std::make_shared<SimpleText>(std::format("Method {}  ", InEvolutionNumber), InParent));
	AddCSVElement(FormComboBox);
	AddElement(std::make_shared<SimpleText>(std::format("Form {}  ", InEvolutionNumber), InParent));
	AddElement(EvolutionConditionSwitcher);
	AddElement(std::make_shared<SimpleText>(std::format("Condition {}  ", InEvolutionNumber), InParent));
}

int32_t EvolutionElement::GetCurrentMethod() const
{
	return static_cast<int32_t>(MethodComboBox->GetSelectedEntry());
}
