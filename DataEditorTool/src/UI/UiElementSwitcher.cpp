#include "include.h"
#include "UI/UiElementSwitcher.h"
#include "UI/UiSection.h"
#include "UI/UiTab.h"
#include "UI/TabCSVState.h"
#include "UI/UiCSVElement.h"

UiElementSwitcher::UiElementSwitcher(const std::string& InName, UiSection* InParent) : MultiUiElement(InName, InParent)
{

}

void UiElementSwitcher::Tick()
{
	// We probably need to recalc every tick
	// because the MultiElement's size will not
	// respond properly to font size changes
	// otherwise
	CalculateSizeConstraints();

	if (CurrentlyActiveElementIndex >= 0)
	{
		if (CurrentlyActiveElement->IsSameLine())
		{
			ImGui::SameLine();
		}

		PushConstrainedSizeForElement(CurrentlyActiveElementIndex);

		// Disable this element in ImGui before ticking if marked as disabled
		if (CurrentlyActiveElement->IsDisabled())
		{
			ImGui::BeginDisabled();
			CurrentlyActiveElement->Tick();

			// IsDisabled might change during Tick, so we must ensure this
			// gets called regardless of the value of IsDisabled after tick.
			ImGui::EndDisabled();
		}
		else
		{
			CurrentlyActiveElement->Tick();
		}
		PopConstrainedSizeForElement(CurrentlyActiveElementIndex);
	}
}

void UiElementSwitcher::SwitchCurrentlyActiveElement(std::shared_ptr<UiElement> NewActiveElement)
{
	// Don't bother switching if the current element is passed in.
	if (NewActiveElement == CurrentlyActiveElement)
	{
		return;
	}


	auto FoundEltIt = std::find(UiElements.begin(), UiElements.end(), NewActiveElement);

	if (FoundEltIt != UiElements.end())
	{
		CurrentlyActiveElement = *FoundEltIt;
		CurrentlyActiveElementIndex = std::distance(UiElements.begin(), FoundEltIt);
	}
	else
	{
		ICLogger::Warn("UiElementSwitcher attempted to switch to an element not in the switcher.");
	}
}

void UiElementSwitcher::CalculateSizeConstraints()
{
	float MaxSize = FLT_MAX;
	float MinSize = 0.f;

	for (const auto UiElement : UiElements)
	{
		const auto ElementSize = UiElement->GetSize();
		const auto ElementMaxSize = ElementSize.GetMax();
		const auto ElementMinSize = ElementSize.GetMin();

		MaxSize = std::min(MaxSize, ElementMaxSize);
		MinSize = std::max(MinSize, ElementMinSize);
	}

	GetSize().SetMax(MaxSize);
	GetSize().SetMin(MinSize);
}

float UiElementSwitcher::GetLabelSize()
{
	float LabelSize = 0.f;

	for (const auto UiElement : UiElements)
	{
		LabelSize = std::max(LabelSize, UiElement->GetLabelSize());
	}

	return LabelSize;
}