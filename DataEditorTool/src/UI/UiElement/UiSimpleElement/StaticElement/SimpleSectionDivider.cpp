#include "include.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleSectionDivider.h"
#include "UI/UiComponent/StaticComponent/SectionDivider.h"

SimpleSectionDivider::SimpleSectionDivider(
	const std::string& InName,
	UiSection* InParent
) :
	UiSingleElement(InName, InParent),
	SectionDividerComponent(std::make_shared<SectionDivider>(InName, this))
{
	SetShouldOverrideSyncedSize(true);
	SetUiComponent(SectionDividerComponent);
}

void SimpleSectionDivider::UiComponentUpdated()
{
	// Implementation intentionally left blank.
}

void SimpleSectionDivider::SetNumSpaceLengths(const uint32_t NewNumSpaceLengths)
{
	SectionDividerComponent->SetNumSpaceLengths(NewNumSpaceLengths);
}