#include "include.h"
#include "UI/UiElement/UiSimpleElement/StringElement/SimpleTextBox.h"

#include  "UI/UiComponent/StringComponent/TextBox.h"

SimpleTextBox::SimpleTextBox(
	const std::string& InName,
	UiSection* InParent
) :
	UiSingleElement(InName, InParent),
	TextBoxComponent(std::make_shared<TextBox>(InName, this))
{
	SetUiComponent(TextBoxComponent);
}

void SimpleTextBox::UiComponentUpdated()
{
	// Implementation intentionally left empty.
}

void SimpleTextBox::SetMinFromLongestString(const std::vector<std::string>& PossibleStrings)
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

void SimpleTextBox::SetTextBoxBuffer(const std::string& NewBufferValue)
{
	TextBoxComponent->SetTextBoxBuffer(NewBufferValue);
}

std::string SimpleTextBox::GetTextBoxBuffer() const
{
	return TextBoxComponent->GetTextBoxBuffer();
}
