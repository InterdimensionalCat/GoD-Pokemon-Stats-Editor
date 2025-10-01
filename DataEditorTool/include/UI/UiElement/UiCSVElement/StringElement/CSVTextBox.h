#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class TextBox;

class CSVTextBox : public UiBasicCSVElement<std::string>
{

public:

	CSVTextBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

	CSVTextBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName
	);

	virtual void Refresh() override;

	virtual void UiComponentUpdated() override;

private:

	std::shared_ptr<TextBox> TextBoxComponent;
};
