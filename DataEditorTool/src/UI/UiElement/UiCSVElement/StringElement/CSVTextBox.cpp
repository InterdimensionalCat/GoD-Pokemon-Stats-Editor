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
	SetUiComponent(TextBoxComponent);
}

CSVTextBox::CSVTextBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName
) :
	CSVTextBox(InName, InParent, InCSVFileName, InName)
{

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

void CSVTextBox::SetMinFromLongestString(const std::vector<std::string>& PossibleStrings)
{
	const auto LongestString = std::max_element(
		PossibleStrings.begin(),
		PossibleStrings.end(),
		[](const std::string& A, const std::string& B)
		{
			return A.length() < B.length();
		}
	);

	TextBoxComponent->SetMinContentSizeFromString(*LongestString);
}