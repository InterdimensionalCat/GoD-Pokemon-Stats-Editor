#include "include.h"
#include "UI/UiElement/UiCSVElement/BoolElement/CSVRadioButton.h"
#include "UI/UiComponent/BoolComponent/RadioButton.h"

CSVRadioButton::CSVRadioButton
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName
) :
	UiBasicCSVElement<bool>(InName, InParent, InCSVFileName, InColumnName),
	RadioButtonComponent(std::make_shared<RadioButton>(InName, this))
{
	SetShouldOverrideSyncedSize(true);
	SetUiComponent(RadioButtonComponent);
}

CSVRadioButton::CSVRadioButton
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName
) :
	CSVRadioButton(InName, InParent, InCSVFileName, InName)
{

}

void CSVRadioButton::Refresh()
{
	UiBasicCSVElement::Refresh();
	RadioButtonComponent->SetBoolBuffer(GetManagedValue());
}

void CSVRadioButton::UiComponentUpdated()
{
	SetManagedValue(RadioButtonComponent->GetBoolBuffer());
}
