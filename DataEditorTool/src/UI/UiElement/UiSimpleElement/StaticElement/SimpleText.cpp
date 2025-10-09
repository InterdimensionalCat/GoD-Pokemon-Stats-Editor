#include "include.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleText.h"
#include "UI/UiComponent/StaticComponent/Text.h"

SimpleText::SimpleText(
	const std::string& InName, 
	UiSection* InParent
) :
	UiSingleElement(InName, InParent),
	TextComponent(std::make_shared<Text>(InName, this))
{
	SetShouldOverrideSyncedSize(true);
	SetUiComponent(TextComponent);
}

void SimpleText::UiComponentUpdated()
{
	// Implementation intentionally left blank.
}

void SimpleText::SetText(const std::string& NewText)
{
	TextComponent->SetText(NewText);
}