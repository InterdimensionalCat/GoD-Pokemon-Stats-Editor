#include "include.h"
#include "Editors/PokemonStats/EvolutionMethod.h"

#include "Editors/PokemonStats/EvolutionElement.h"
#include "Editors/PokemonStats/EvolutionCondition.h"
#include "UI/UiComponent/StringComponent/ComboBox.h"
#include "Command/MultiCommand.h"
#include "CSV/StringTypes/IntHexParenthValue.h"

EvolutionMethod::EvolutionMethod
(
	const std::string& InName,
	UiSection* InParent,
	EvolutionElement* InParentElement,
	const std::string& InCSVFileName,
	const std::string& InColumnName,
	const std::string& InEntriesListCSVFileName,
	const std::string& InEntriesListColumnName
) :
	CSVComboBox(
		InName,
		InParent,
		InCSVFileName,
		InColumnName,
		InEntriesListCSVFileName,
		InEntriesListColumnName
	),
	ParentElement(InParentElement)
{
}

EvolutionMethod::EvolutionMethod
(
	const std::string& InName,
	UiSection* InParent,
	EvolutionElement* InParentElement,
	const std::string& InCSVFileName,
	const std::string& InEntriesListCSVFileName,
	const std::string& InEntriesListColumnName
) :
	EvolutionMethod
	(
		InName,
		InParent,
		InParentElement,
		InCSVFileName,
		InName,
		InEntriesListCSVFileName,
		InEntriesListColumnName
	)
{

}

void EvolutionMethod::UiComponentUpdated()
{
	// Only update if a different value was selected.
	auto SelectedValue = ComboBoxComponent->GetEntriesList().at(GetSelectedEntry());

	if(GetManagedValue() != SelectedValue)
	{
		std::shared_ptr<MultiCommand> EvolutionChangeCommand = std::make_shared<MultiCommand>("Change evolution method");

		EvolutionChangeCommand->AddCommandAndExecute(std::make_shared<ModifySingleCSVValue>(
			GetCSVFileName(),
			GetColumnName(),
			GetCurrentRow(),
			SelectedValue
		));

		auto Condition = ParentElement->GetEvolutionCondition();
		int32_t ConditionDefault = Condition->GetDefaultForCondition(GetSelectedEntry());

		IntHexParenthValue ConditionAsString = IntHexParenthValue(ConditionDefault);

		EvolutionChangeCommand->AddCommandAndExecute(std::make_shared<ModifySingleCSVValue>(
			Condition->GetCSVFileName(),
			Condition->GetColumnName(),
			Condition->GetCurrentRow(),
			ConditionAsString.GetParenthValueString()
		));

		GetTabState()->PushCommand(EvolutionChangeCommand);
	}
}