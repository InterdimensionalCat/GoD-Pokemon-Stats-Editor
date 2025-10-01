#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class CheckBox;

class CSVCheckbox : public UiBasicCSVElement<bool>
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

	virtual void Refresh() override;

	virtual void UiComponentUpdated() override;

private:

	std::shared_ptr<CheckBox> CheckBoxComponent;
};
