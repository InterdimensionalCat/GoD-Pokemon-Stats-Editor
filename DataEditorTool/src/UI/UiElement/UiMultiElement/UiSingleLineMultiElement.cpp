#include "include.h"
#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"
#include "UI/UiSection.h"
#include "UI/UiSize/UiSummedSize.h"
#include "UI/UiSize/UiConstrainedSizeWithLabel.h"

UiSingleLineMultiElement::UiSingleLineMultiElement(
	const std::string& InName,
	UiSection* InParent
) :
	UiMultiElement(InName, InParent),
	SizeConstraints(std::make_shared<UiSummedSize>())
{
	ConstrainedSize = std::make_shared<UiConstrainedSizeWithLabel>();
}

void UiSingleLineMultiElement::CalculateConstrainedSize(const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize, const std::shared_ptr<const UiSize>& ParentSizeConstraints)
{
	// First calculate the summed size of all child elements.
	// TODO: We could add elements as consideration targets
	// in AddElement.
	SizeConstraints->ClearSizesToConsider();

	for (const auto Element : UiElements)
	{
		SizeConstraints->AddSizeToConsider(Element->GetSizeConstraints());
	}

	// Then use this to calculate our own constrained size.
	// Note that this will account for element labels.
	ConstrainedSize->CalculateFromSizeConstraints(
		ParentConstrainedSize->GetConstrainedSize(),
		SizeConstraints
	);

	// Next, we need to account for fixed size elements. The sizing behavior we
	// want is for fixed size elements to always be their fixed size, and for
	// non-fixed size elements to share the remaining space equally.
	auto FixedSizeElements = GetFixedSizeElements();

	float TotalFixedSizeIncludingLabels = 0.f;
	const int32_t NumFixedElements = FixedSizeElements.size();

	for (auto Element : FixedSizeElements)
	{
		TotalFixedSizeIncludingLabels += Element->GetSizeConstraints()->GetMinWithLabel();
	}

	// Update the ConstrainedSize to account for the fixed size elements.
	ConstrainedSize->SetConstrainedSize(
		ConstrainedSize->GetConstrainedSize() - TotalFixedSizeIncludingLabels
	);

	const int32_t NumVariableSizeElements = UiElements.size() - NumFixedElements;

	if (NumVariableSizeElements != 0)
	{
		ConstrainedSize->SetConstrainedSize(
			ConstrainedSize->GetConstrainedSize() / static_cast<float>(NumVariableSizeElements)
		);
	}


	// Finally, calculate the constrained size of all child elements.
	for (auto Element : UiElements)
	{
		
		if (!Element->ShouldOverrideSyncedSize())
		{
			ICLogger::Warn("UiSingleLineMultiElement {} has a child element {} that does not override synced size. This may be a mistake.", GetName(), Element->GetName());
		}

		if (Element->GetSizeConstraints()->IsFixedSize())
		{
			// For fixed size elements, set their constrained size to their fixed size.
			auto ElementSizeConstraints = Element->GetSizeConstraints();
			auto FixedConstrainedSize = std::make_shared<UiConstrainedSizeWithLabel>(ElementSizeConstraints->GetMinWithoutLabel());
			Element->CalculateConstrainedSize(FixedConstrainedSize, ElementSizeConstraints);
		}
		else
		{
			// For variable size elements, calculate their constrained size with
			// an equal portion of the remaining space.
			if (NumVariableSizeElements == 0)
			{
				ICLogger::Warn("UiSingleLineMultiElement {} has no variable size elements, but is trying to calculate their constrained size. This may be a mistake.", GetName());
				continue;
			}

			auto ElementSizeConstraints = Element->GetSizeConstraints();

			// TODO: this probably won't work right unless each label is the same size,
			// but its behavior should be reasonable nonetheless.
			Element->CalculateConstrainedSize(ConstrainedSize, ElementSizeConstraints);
		}
	}
}

void UiSingleLineMultiElement::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	NewElement->SetShouldOverrideSyncedSize(true);

	if(UiElements.size() != 0)
	{
		NewElement->SetSameLine(true);
	}
	else
	{
		NewElement->SetSameLine(false);
	}

	UiElements.push_back(NewElement);
}

std::shared_ptr<const UiSize> UiSingleLineMultiElement::GetSizeConstraints() const
{
	return SizeConstraints;
}

std::vector<std::shared_ptr<UiElement>> UiSingleLineMultiElement::GetFixedSizeElements() const
{
	std::vector<std::shared_ptr<UiElement>> FixedSizeElements;

	for (auto Element : UiElements)
	{
		if (Element->GetSizeConstraints()->IsFixedSize())
		{
			FixedSizeElements.push_back(Element);
		}
	}

	return FixedSizeElements;
}