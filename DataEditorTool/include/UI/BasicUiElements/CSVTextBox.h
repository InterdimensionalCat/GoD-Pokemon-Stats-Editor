#pragma once
#include "UI/BasicUiElements/BasicUiElement.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

class CSVTextBox : public BasicUiElement<std::string>
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

	virtual void Tick() override;

private:

	std::string TextBoxBuffer = "---";
};
