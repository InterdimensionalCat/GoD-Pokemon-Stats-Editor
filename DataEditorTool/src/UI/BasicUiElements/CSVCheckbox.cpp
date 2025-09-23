#include "include.h"
#include "UI/BasicUiElements/CSVCheckbox.h"

CSVCheckbox::CSVCheckbox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName
) :
	BasicUiElement<bool>(InName, InParent, InCSVFileName, InColumnName)
{
	// Images will always be a fixed size.
	SetSizeSource(UiSizeSource_Self);
	GetSize().SetSizeRule(UiSizeRule_FixedSize);
	GetSize().SetMinFromStringLength(1);
}

CSVCheckbox::CSVCheckbox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName
) :
	CSVCheckbox(InName, InParent, InCSVFileName, InName)
{

}

void CSVCheckbox::Tick()
{
	// Show an checkbox.
	if(ImGui::Checkbox(GetName().c_str(), &bBoolBuffer))
	{
		SetManagedValue(bBoolBuffer);
	}
}

void CSVCheckbox::Refresh()
{
	BasicUiElement::Refresh();
	bBoolBuffer = GetManagedValue();
}
