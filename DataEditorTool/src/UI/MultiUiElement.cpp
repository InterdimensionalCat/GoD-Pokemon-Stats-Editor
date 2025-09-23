#include "include.h"
#include "UI/MultiUiElement.h"
#include "UI/UiSection.h"
#include "UI/UiTab.h"
#include "UI/TabCSVState.h"
#include "UI/UiCSVElement.h"

MultiUiElement::MultiUiElement(const std::string& InName, UiSection* InParent) : UiElement(InName, InParent)
{

}

void MultiUiElement::Tick()
{
	// We probably need to recalc every tick
	// because the MultiElement's size will not
	// respond properly to font size changes
	// otherwise
	CalculateSizeConstraints();

	for (uint32_t i = 0; i < UiElements.size(); i++)
	{
		std::shared_ptr<UiElement> UiElement = UiElements.at(i);
		if (UiElement->IsSameLine())
		{
			ImGui::SameLine();
		}

		// Draw the next UiElement with the correct constrained size.
		PushConstrainedSizeForElement(i);

		// Disable this element in ImGui before ticking if marked as disabled
		if (UiElement->IsDisabled())
		{
			ImGui::BeginDisabled();
			UiElement->Tick();

			// IsDisabled might change during Tick, so we must ensure this
			// gets called regardless of the value of IsDisabled after tick.
			ImGui::EndDisabled();
		}
		else
		{
			UiElement->Tick();
		}
		PopConstrainedSizeForElement(i);
	}
}

void MultiUiElement::Refresh()
{
	for (auto UiElement : UiElements)
	{
		UiElement->Refresh();
	}
}

void MultiUiElement::PushConstrainedElementSize()
{
	// Calculate the horizontal space available.
	const ImGuiStyle& Style = ImGui::GetStyle();
	const float SpaceAvailable = ImGui::GetContentRegionAvail().x - (Style.FramePadding.x * 2);

	float MaxLabelSize = GetLabelSize();

	switch (GetSizeSource())
	{
	case UiSizeSource_Parent:
		// Only sync with parent if its enabled, otherwise do the same calcs as self.
		if (ParentSection->ShouldSyncWidthAcrossElements())
		{
			MaxLabelSize = ParentSection->GetElementsMaxLabelSize();
			const UiSize& ParentSizeConstraints = ParentSection->GetSyncedSize();
			ConstrainedSizeForThisFrame = ParentSizeConstraints.CalculateSizeFromSpaceAvailable(SpaceAvailable, MaxLabelSize, ParentSection->GetNumItemsThisLine());
			return;
		}
		[[fallthrough]];
	case UiSizeSource_Self:
		[[fallthrough]]; // Falls through to default behavior
	default:
		ConstrainedSizeForThisFrame = GetSize().CalculateSizeFromSpaceAvailable(SpaceAvailable, MaxLabelSize, ParentSection->GetNumItemsThisLine());
		break;
	}
}

void MultiUiElement::PopConstrainedElementSize()
{
	// Implementation intentionally blank,
	// we do not need to pop size for
	// a multi line element, as push size only
	// sets the constrained size for the frame,
	// it doesn't actually push element size for anything.
}

// TODO: ability to designate an index as the "move to second line if not enough space" point
void MultiUiElement::PushConstrainedSizeForElement(const uint32_t ElementIndex)
{
	auto CurrentElement = UiElements.at(ElementIndex);
	CurrentElement->PushConstrainedElementSize();
}

void MultiUiElement::PopConstrainedSizeForElement(const uint32_t ElementIndex)
{
	auto CurrentElement = UiElements.at(ElementIndex);
	CurrentElement->PopConstrainedElementSize();
}

void MultiUiElement::AddCSVElement(const std::shared_ptr<UiCSVElement> NewElement)
{
	AddElement(NewElement);
	ParentSection->GetParent()->GetTabCSVState()->AddElementToUpdate(NewElement);
}

void MultiUiElement::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	UiElements.push_back(NewElement);

	std::shared_ptr<UiElement> AddedUiElement = UiElements.at(UiElements.size() - 1);

	// Recalculate the size constraints of this element.
	CalculateSizeConstraints();
}

void MultiUiElement::CalculateSizeConstraints()
{
	float MaxSize = 0.f;
	float MinSize = 0.f;

	for (const auto UiElement : UiElements)
	{
		const auto ElementSize = UiElement->GetSize();
		const auto ElementMaxSize = ElementSize.GetMax();
		const auto ElementMinSize = ElementSize.GetMin();

		const auto UpperBound = std::numeric_limits<float>::max() - ElementMaxSize;
		const auto LowerBound = std::numeric_limits<float>::max() - ElementMinSize;

		// Ensure we don't go over FLT_MAX to prevent float overflow
		if (MaxSize <= UpperBound)
		{
			MaxSize += ElementSize.GetMax();
		}

		if (MinSize <= LowerBound)
		{
			MinSize += ElementSize.GetMin();
		}
	}

	GetSize().SetMax(MaxSize);
	GetSize().SetMin(MinSize);
}

float MultiUiElement::GetLabelSize()
{
	float TotalLabelSize = 0.f;

	for (const auto UiElement : UiElements)
	{
		TotalLabelSize += UiElement->GetLabelSize();
	}

	return TotalLabelSize;
}