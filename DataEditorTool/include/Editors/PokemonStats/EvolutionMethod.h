#pragma once

#include "UI/UiElement/UiCSVElement/StringElement/CSVComboBox.h"

class EvolutionElement;

class EvolutionMethod : public CSVComboBox
{

public:

	EvolutionMethod
	(
		const std::string& InName,
		UiSection* InParent,
		EvolutionElement* InParentElement,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	EvolutionMethod
	(
		const std::string& InName,
		UiSection* InParent,
		EvolutionElement* InParentElement,
		const std::string& InCSVFileName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	virtual void UiComponentUpdated() override;

private:

	EvolutionElement* ParentElement;

};
