#include "include.h"
#include "UI/BasicUiElements/SimpleText.h"

SimpleText::SimpleText(
	const std::string& InName, 
	UiSection* InParent
) :
	UiElement(InName, InParent),
	TextToDisplay(InName)
{
	GetSize().SetMinFromString(TextToDisplay);
	GetSize().SetSizeRule(UiSizeRule_FixedSize);
}

void SimpleText::Tick()
{
	// Show the name of this element as text.
	ImGui::Text(TextToDisplay.c_str());
}

void SimpleText::SetText(const std::string& NewText)
{
	TextToDisplay = NewText;
	GetSize().SetMinFromString(TextToDisplay);
}

float SimpleText::GetLabelSize()
{
	// Text does not have a label.
	return 0.f;
}