#include "include.h"
#include "UI/UiElement/UiCSVElement/BoolElement/CSVCheckbox.h"
#include "UI/UiComponent/BoolComponent/CheckBox.h"

CSVCheckbox::CSVCheckbox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName
) :
	UiBasicCSVElement<bool>(InName, InParent, InCSVFileName, InColumnName),
	CheckBoxComponent(std::make_shared<CheckBox>(InName, this))
{
	SetShouldOverrideSyncedSize(true);
	SetUiComponent(CheckBoxComponent);
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

void CSVCheckbox::Refresh()
{
	UiBasicCSVElement::Refresh();
	CheckBoxComponent->SetBoolBuffer(GetManagedValue());
}

void CSVCheckbox::UiComponentUpdated()
{
	SetManagedValue(CheckBoxComponent->GetBoolBuffer());
}
