#include "include.h"
#include "UI/UiElement/UiMultiElement/UiElementSwitcher.h"
#include "UI/UiSection.h"
#include "UI/UiSize/UiSyncedSize.h"
#include "UI/UiSize/UiConstrainedSize.h"


UiElementSwitcher::UiElementSwitcher(
	const std::string& InName,
	UiSection* InParent
) :
	UiMultiElement(InName, InParent),
	SizeConstraints(std::make_shared<UiSyncedSize>())
{

}

void UiElementSwitcher::Tick()
{
	if (CurrentlyActiveElement.get() != nullptr)
	{
		CurrentlyActiveElement->Tick();
	}
	else
	{
		ICLogger::Warn("UiElementSwitcher {} has no active element to display.", GetName());
	}
}

void UiElementSwitcher::CalculateConstrainedSize(const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize, const std::shared_ptr<const UiSize>& ParentSizeConstraints)
{
	// Recalculate the synced size between all possible
	// child elements
	//SizeConstraints->ClearSizesToConsider();

	//for (auto Element : UiElements)
	//{
	//	SizeConstraints->AddSizeToConsider(Element->GetSizeConstraints());
	//}

	// The default UiMultiElement calculations will work here so long as our
	// synced size is properly updated. It assumes each element is on its own
	// line and has the entire line's available space to work with, which is
	// essentially true for an element switcher.
	UiMultiElement::CalculateConstrainedSize(ParentConstrainedSize, ParentSizeConstraints);
}

void UiElementSwitcher::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	UiMultiElement::AddElement(NewElement);
	SizeConstraints->AddSizeToConsider(NewElement->GetSizeConstraints());
	// If this is the first element added, make it the active element.
	if (CurrentlyActiveElement == nullptr)
	{
		SwitchCurrentlyActiveElement(NewElement);
	}
}

std::shared_ptr<const UiSize> UiElementSwitcher::GetSizeConstraints() const
{
	return SizeConstraints;
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
		ICLogger::Warn("UiElementSwitcher attempted to switch to an element not in the switcher: {}", NewActiveElement->GetName());
	}
}