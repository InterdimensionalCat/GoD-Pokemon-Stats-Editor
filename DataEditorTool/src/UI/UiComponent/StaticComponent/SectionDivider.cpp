#include "include.h"
#include"UI/UiComponent/StaticComponent/SectionDivider.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"

SectionDivider::SectionDivider(const std::string& InName, UiSingleElement* InParent)
	: UiComponent(InName, InParent, false)
{
	SetNumSpaceLengths(2);

	ComponentSize->SetIsFixedSize(true);
}

void SectionDivider::DisplayComponent()
{
	// Show NumSpaceLengths number of spaces before text with the section name
	auto& Style = ImGui::GetStyle();
	if (NumSpaceLengths > 0)
	{
		ImGui::Dummy(ImVec2(0.0f, Style.ItemSpacing.y * NumSpaceLengths));
	}

	ImGui::SeparatorText(GetName().c_str());
}

void SectionDivider::SetNumSpaceLengths(const uint32_t NewNumSpaceLengths)
{
	NumSpaceLengths = NewNumSpaceLengths;
}

float SectionDivider::CalculateInternalSpace() const
{
	// Section dividers never have internal space.
	return 0.f;
}