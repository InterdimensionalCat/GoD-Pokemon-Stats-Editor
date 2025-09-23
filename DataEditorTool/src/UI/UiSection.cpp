#include "include.h"
#include "UI/UiTab.h"
#include "UI/UiSection.h"
#include "UI/UiElement.h"
#include "UI/UiCSVElement.h"
#include "UI/TabCSVState.h"

UiSection::UiSection(const std::string& InName, UiTab* InParent) :
	UiObject(InName, InParent),
	bShouldSyncWidthAcrossElements(true),
	SyncedSize(UiSize()),
	ParentTab(InParent)
{
	SectionDockspace = InParent->GetSectionDockspace();
}

void UiSection::Refresh()
{
	for (std::shared_ptr<UiElement> UiElement : UiElements)
	{
		UiElement->Refresh();
	}
}

void UiSection::Tick()
{
	ImGui::SetNextWindowClass(SectionDockspace.get());

	ImGuiWindowFlags WindowFlags = 0;
	WindowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
	// WindowFlags |= ImGuiWindowFlags_NoNavInputs;

	// Begin a new Window for this UiSection.
	if (!ImGui::Begin(GetName().c_str(), nullptr, WindowFlags))
	{
		ImGui::End();
		return;
	}

	// If SouldSyncWidthAcrossElements is set,
	// calculate a new Synced size based on
	// the max/min width constraints of all elements
	if (ShouldSyncWidthAcrossElements())
	{
		// The max element size can be less than the min element size.
		// If this happens we just set the element size to be the MinElementSize.
		const float MaxElementSize = GetMaxAllowedWidth();
		const float MinElementSize = GetMinNeededWidth();

		SyncedSize = UiSize(MinElementSize, MaxElementSize);
	}

	NumItemsThisLine = 1;
	for (uint32_t i = 0; i < UiElements.size(); i++)
	{
		std::shared_ptr<UiElement> UiElement = UiElements.at(i);
		if (UiElement->IsSameLine())
		{
			ImGui::SameLine();
		}
		else {
			CalcNumItemsOnNextLine(i);
		}

		// Draw the next UiElement with the correct constrained size.
		UiElement->PushConstrainedElementSize();

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
		UiElement->PopConstrainedElementSize();
	}

	ImGui::End();
}

void UiSection::AddCSVElement(const std::shared_ptr<UiCSVElement> NewElement)
{
	AddElement(NewElement);
	GetParent()->GetTabCSVState()->AddElementToUpdate(NewElement);
}

void UiSection::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	UiElements.push_back(NewElement);
}

void UiSection::SetShouldSyncWidthAcrossElements(const bool ShouldSync)
{
	bShouldSyncWidthAcrossElements = ShouldSync;
}

void UiSection::CalcNumItemsOnNextLine(const uint32_t ItemIndex)
{
	NumItemsThisLine = 1;
	for (uint32_t i = ItemIndex + 1; i < UiElements.size(); i++)
	{
		std::shared_ptr<UiElement> UiElement = UiElements.at(i);
		if (UiElement->IsSameLine())
		{
			NumItemsThisLine++;
		}
		else
		{
			return;
		}
	}
}

bool UiSection::ShouldSyncWidthAcrossElements()
{
	return bShouldSyncWidthAcrossElements;
}

float UiSection::GetMinNeededWidth()
{
	// Min needed with is the largest min needed of the
	// elements in this section.
	float MinNeededWidth = 0.f;

	for (std::shared_ptr<UiElement> UiElement : UiElements)
	{
		MinNeededWidth = std::max(MinNeededWidth, UiElement->GetSize().GetMin());
	}

	return MinNeededWidth;
}

float UiSection::GetMaxAllowedWidth()
{
	// Max allowed with is the smallest max allowed of the
	// elements in this section.
	float MaxAllowedWidth = FLT_MAX;

	for (std::shared_ptr<UiElement> UiElement : UiElements)
	{
		MaxAllowedWidth = std::min(MaxAllowedWidth, UiElement->GetSize().GetMax());
	}

	return MaxAllowedWidth;
}

float UiSection::GetElementsMaxLabelSize()
{
	float MaxLabelSize = 0.f;

	for (std::shared_ptr<UiElement> UiElement : UiElements)
	{
		MaxLabelSize = std::max(MaxLabelSize, UiElement->GetLabelSize());
	}

	return MaxLabelSize;
}

const UiSize& UiSection::GetSyncedSize() const
{
	return SyncedSize;
}

uint32_t UiSection::GetNumItemsThisLine() const
{
	return NumItemsThisLine;
}

UiTab* UiSection::GetParent()
{
	return ParentTab;
}