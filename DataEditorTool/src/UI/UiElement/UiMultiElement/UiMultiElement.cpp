#include "include.h"
#include "UI/UiElement/UiMultiElement/UiMultiElement.h"
#include "UI/UiSize/UiConstrainedSize.h"
#include "UI/UiSize/UiSize.h"
#include "UI/UiSection.h"

UiMultiElement::UiMultiElement(
	const std::string& InName,
	UiSection* InParent
) :
	UiElement(InName, InParent)
{

}

void UiMultiElement::Tick()
{
	for (auto UiElement : UiElements)
	{
		UiElement->Tick();
	}
}

void UiMultiElement::Refresh()
{
	for (auto UiElement : UiElements)
	{
		UiElement->Refresh();
	}
}

void UiMultiElement::CalculateConstrainedSize(
	const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
	const std::shared_ptr<const UiSize>& ParentSizeConstraints
)
{
	// This implementation assumes that all child elements are on their own line,
	// multi elements that have multiple elements on one line will need to
	// override this behavior.

	auto SizeConstraints = GetSizeConstraints();

	// First calculate this MultiElement's constrained size.
	ConstrainedSize->CalculateFromSizeConstraints(
		ParentConstrainedSize->GetConstrainedSize(),
		SizeConstraints
	);

	// Then use that calculated size as the space available for all our
	// child elements.
	for (auto UiElement : UiElements)
	{
		UiElement->CalculateConstrainedSize(ConstrainedSize, SizeConstraints);
	}
}

void UiMultiElement::SetSameLine(const bool bInSameLine)
{
	for (auto UiElement : UiElements)
	{
		UiElement->SetSameLine(bInSameLine);
	}
}

void UiMultiElement::SetDisabled(const bool bInDisabled)
{
	for (auto UiElement : UiElements)
	{
		UiElement->SetDisabled(bInDisabled);
	}
}

void UiMultiElement::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	UiElements.push_back(NewElement);
}