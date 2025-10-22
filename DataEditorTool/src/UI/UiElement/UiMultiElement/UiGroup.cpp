#include "include.h"
#include "UI/UiElement/UiMultiElement/UiGroup.h"
#include "UI/UiSize/UiSyncedSize.h"
#include "UI/UiSize/UiConstrainedSizeWithLabel.h"

UiGroup::UiGroup
(
	const std::string& InName,
	UiSection* InParent
) :
	UiMultiElement(InName, InParent),
	SyncedSize(std::make_shared<UiSyncedSize>())
{
	ConstrainedSize = std::make_shared<UiConstrainedSizeWithLabel>();
}

void UiGroup::Tick()
{
	if (bIsSameLine)
	{
		// Set same line with an offset from start X
		// if same line with an offset was set, otherwise
		// just set same line with no offset.
		if (SameLineOffsetFromStart != 0.f)
		{
			ImGui::SameLine(SameLineOffsetFromStart);
		}
		else
		{
			ImGui::SameLine();
		}
	}

	// Begin the group
	ImGui::BeginGroup();

	// Tick all child elements within the group
	UiMultiElement::Tick();

	// End the group
	ImGui::EndGroup();
}


void UiGroup::CalculateConstrainedSize(const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize, const std::shared_ptr<const UiSize>& ParentSizeConstraints)
{
	CalculateSyncedSize();

	// First calculate this MultiElement's constrained size.
	ConstrainedSize->CalculateFromSizeConstraints(
		ParentConstrainedSize->GetConstrainedSize(),
		ParentSizeConstraints
	);

	// Calculate the size constraints of each element with its own UiSize, 
	// rather than this child's UiSize.
	for (auto UiElement : UiElements)
	{
		UiElement->CalculateConstrainedSize(ConstrainedSize, SyncedSize);
	}
}

void UiGroup::SetSameLine(const bool bInSameLine)
{
	bIsSameLine = bInSameLine;
	SameLineOffsetFromStart = 0.f;
}

void UiGroup::SetSameLine(const float OffsetFromStart)
{
	bIsSameLine = true;
	SameLineOffsetFromStart = OffsetFromStart;
}

void UiGroup::CalculateSyncedSize()
{
	SyncedSize->ClearSizesToConsider();

	for (const std::shared_ptr<UiElement>& Element : UiElements)
	{
		if (Element->ShouldOverrideSyncedSize())
		{
			continue;
		}

		SyncedSize->AddSizeToConsider(Element->GetSizeConstraints());
	}
}

void UiGroup::SetIsFixedSize(const bool bInIsFixedSize)
{
	SyncedSize->SetIsFixedSize(bInIsFixedSize);
}

void UiGroup::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	UiMultiElement::AddElement(NewElement);
}

std::shared_ptr<const UiSize> UiGroup::GetSizeConstraints() const
{
	return SyncedSize;
}