#pragma once

#include "UI/BasicUiElements/BasicUiElement.h"

class CSVCheckbox : public BasicUiElement<bool>
{

public:

	CSVCheckbox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

	CSVCheckbox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName
	);

	virtual void Tick() override;

	virtual void Refresh() override;

private:

	bool bBoolBuffer = false;
};
