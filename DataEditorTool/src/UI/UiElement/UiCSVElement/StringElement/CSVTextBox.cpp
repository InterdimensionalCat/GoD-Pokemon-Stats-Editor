#include "include.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVTextBox.h"
#include "UI/UiComponent/StringComponent/TextBox.h"

CSVTextBox::CSVTextBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName
) :
	UiBasicCSVElement<std::string>(InName, InParent, InCSVFileName, InColumnName),
	TextBoxComponent(std::make_shared<TextBox>(InName, this))
{
	// We don't need to set the text box buffer to
	// The managed value here because the whole tab
	// will refresh on the next tick after elements
	// are added.
}

CSVTextBox::CSVTextBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName
) :
	CSVTextBox(InName, InParent, InCSVFileName, InName)
{
	SetUiComponent(TextBoxComponent);
}

void CSVTextBox::Refresh()
{
	UiBasicCSVElement::Refresh();
	TextBoxComponent->SetTextBoxBuffer(GetManagedValue());
}

void CSVTextBox::UiComponentUpdated()
{
	SetManagedValue(TextBoxComponent->GetTextBoxBuffer());
}