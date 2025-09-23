#include "include.h"
#include "UI/UiSection.h"
#include "UI/UiElement.h"
#include "UI/UiSize.h"

UiElement::UiElement(const std::string& InName, UiSection* InParent) :
	UiObject(InName, InParent),
	ParentSection(InParent),
	SizeSource(UiSizeSource_Parent),
	ElementSize(UiSize()),
	bIsSameLine(false)
{

}

void UiElement::Tick()
{

}

void UiElement::PushConstrainedElementSize()
{
	// Calculate the horizontal space available.
	const ImGuiStyle& Style = ImGui::GetStyle();
	const float SpaceAvailable = ImGui::GetContentRegionAvail().x - (Style.FramePadding.x * 2);

	float MaxLabelSize = GetLabelSize();

	switch (SizeSource)
	{
	case UiSizeSource_Parent:
		// Only sync with parent if its enabled, otherwise do the same calcs as self.
		if (ParentSection->ShouldSyncWidthAcrossElements())
		{
			MaxLabelSize = ParentSection->GetElementsMaxLabelSize();
			const UiSize& ParentSizeConstraints = ParentSection->GetSyncedSize();
			ImGui::PushItemWidth(ParentSizeConstraints.CalculateSizeFromSpaceAvailable(SpaceAvailable, MaxLabelSize, ParentSection->GetNumItemsThisLine()));
			return;
		}
		[[fallthrough]];
	case UiSizeSource_Self:
		[[fallthrough]]; // Falls through to default behavior
	default:
		ImGui::PushItemWidth(GetSize().CalculateSizeFromSpaceAvailable(SpaceAvailable, MaxLabelSize, ParentSection->GetNumItemsThisLine()));
		break;
	}
}

void UiElement::PopConstrainedElementSize()
{
	ImGui::PopItemWidth();
}

void UiElement::SetSameLine(const bool IsSameLine)
{
	bIsSameLine = IsSameLine;
}

void UiElement::SetDisabled(const bool InIsDisabled)
{
	bIsDisabled = InIsDisabled;
}

void UiElement::SetSizeSource(const UiSizeSource InSizeSource)
{
	SizeSource = InSizeSource;
}

bool UiElement::IsSameLine() const
{
	return bIsSameLine;
}

bool UiElement::IsDisabled() const
{
	return bIsDisabled;
}

float UiElement::GetLabelSize()
{
	return ImGui::CalcTextSize(GetName().c_str(), 0, true).x;
}

UiSize& UiElement::GetSize()
{
	return ElementSize;
}

const UiSize& UiElement::GetSize() const
{
	return ElementSize;
}

UiSizeSource UiElement::GetSizeSource() const
{
	return SizeSource;
}