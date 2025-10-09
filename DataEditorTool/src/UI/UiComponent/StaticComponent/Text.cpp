#include "include.h"
#include "UI/UIComponent/StaticComponent/Text.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"

Text::Text(
	const std::string& InName,
	UiSingleElement* InParent
) :
	UiComponent(InName, InParent, false),
	TextToDisplay(InName)
{
	ComponentSize->SetIsFixedSize(true);
	SetMinContentSizeFromString(TextToDisplay);
}

void Text::DisplayComponent()
{
	// Show the name of this element as text.
	ImGui::Text(TextToDisplay.c_str());
}

void Text::SetText(const std::string& NewText)
{
	TextToDisplay = NewText;
	SetMinContentSizeFromString(TextToDisplay);
}

float Text::CalculateInternalSpace() const
{
	// Text does not have any internal size,
	// the space between it and other elements
	// is just the ItemSpacing style var.
	return 0.f;
}