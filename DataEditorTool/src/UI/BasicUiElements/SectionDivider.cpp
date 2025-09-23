#include "include.h"
#include "UI/BasicUiElements/SectionDivider.h"

SectionDivider::SectionDivider(const std::string& InName, UiSection* InParent) : UiElement(InName, InParent)
{
	SetNumSpaceLengths(2);
	
	// This element controls its own size
	SetSizeSource(UiSizeSource::UiSizeSource_Self);

	// This element is always the same size
	GetSize().SetSizeRule(UiSizeRule::UiSizeRule_FixedSize);
}

void SectionDivider::Tick()
{
	// Show NumSpaceLengths number of spaces before text with the section name
	auto& Style = ImGui::GetStyle();
	if (NumSpaceLengths > 0)
	{
		ImGui::Dummy(ImVec2(0.0f, Style.ItemSpacing.y * NumSpaceLengths));
	}

	//ImGui::Text(GetName().c_str());
	//ImGui::Separator();
	ImGui::SeparatorText(GetName().c_str());
	//ImGui::Dummy(ImVec2(0.0f, Style.ItemSpacing.y));
}

void SectionDivider::SetNumSpaceLengths(const uint32_t NewNumSpaceLengths)
{
	NumSpaceLengths = NewNumSpaceLengths;
}

float SectionDivider::GetLabelSize()
{
	return 0.f;
}