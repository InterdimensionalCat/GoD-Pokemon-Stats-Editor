#include "include.h"
#include "UI/UiComponent/UiComponent.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"

UiComponent::UiComponent(
	const std::string& InName,
	UiSingleElement* InParent,
	const bool InHasLabel
) :
	UiObject(InName, InParent),
	ParentElement(InParent),
	ComponentSize(std::make_shared<UiSize>()),
	bHasLabel(InHasLabel),
	bIsSameLine(false),
	bIsDisabled(false)
{
	if (HasLabel())
	{
		ComponentSize->SetLabel(GetName());
	}
	else
	{
		ComponentSize->SetLabel("");
	}
}

UiComponent::UiComponent(
	const std::string& InName,
	UiSingleElement* InParent
) :
	UiComponent(InName, InParent, true)
{

}

void UiComponent::Tick()
{

	if (IsSameLine())
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

	// Disable this element in ImGui before ticking if marked as disabled
	if (IsDisabled())
	{
		ImGui::BeginDisabled();
		DisplayComponent();

		// IsDisabled might change during Tick, so we must ensure this
		// gets called regardless of the value of IsDisabled after tick.
		ImGui::EndDisabled();
	}
	else
	{
		DisplayComponent();
	}
}

void UiComponent::ComponentUpdated()
{
	ParentElement->UiComponentUpdated();
}

void UiComponent::SetSameLine(const bool IsSameLine)
{
	bIsSameLine = IsSameLine;
	SameLineOffsetFromStart = 0.f;
}

void UiComponent::SetSameLine(const float OffsetFromStart)
{
	bIsSameLine = true;
	SameLineOffsetFromStart = OffsetFromStart;
}

void UiComponent::SetDisabled(const bool InIsDisabled)
{
	bIsDisabled = InIsDisabled;
}

void UiComponent::SetMinContentSizeFromString(const std::string& NewMinString)
{
	ComponentSize->SetMin(UiSizeBound(NewMinString, CalculateInternalSpace(), 0.f));
}

void UiComponent::SetMaxContentSizeFromString(const std::string& NewMaxString)
{
	ComponentSize->SetMax(UiSizeBound(NewMaxString, CalculateInternalSpace(), 0.f));
}

void UiComponent::SetMinContentSizeFromStringLength(const uint32_t NewMinStringLength)
{
	std::string MinString(NewMinStringLength, '-');
	SetMinContentSizeFromString(MinString);
}

void UiComponent::SetMaxContentSizeFromStringLength(const uint32_t NewMaxStringLength)
{
	std::string MaxString(NewMaxStringLength, '-');
	SetMaxContentSizeFromString(MaxString);
}

std::shared_ptr<UiSize> UiComponent::GetSizeConstraints()
{
	return ComponentSize;
}

std::shared_ptr<const UiSize> UiComponent::GetSizeConstraints() const
{
	return ComponentSize;
}

bool UiComponent::IsSameLine() const
{
	return bIsSameLine;
}

bool UiComponent::IsDisabled() const
{
	return bIsDisabled;
}

bool UiComponent::HasLabel() const
{
	return bHasLabel;
}

float UiComponent::CalculateInternalSpace() const
{
	// Implementation intentionally blank, override in subclasses.
	return 0.f;
}
