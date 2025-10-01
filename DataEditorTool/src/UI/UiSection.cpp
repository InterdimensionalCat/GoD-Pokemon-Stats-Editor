#include "include.h"
#include "UI/UiTab.h"
#include "UI/UiSection.h"
#include "UI/UiElement/UiElement.h"
#include "UI/TabCSVState.h"
#include "UI/UiSize/UiSyncedSize.h"

UiSection::UiSection(const std::string& InName, UiTab* InParent) :
	UiObject(InName, InParent),
	SyncedSize(std::make_shared<UiSyncedSize>()),
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

	// Calculate the constrained sizes of all elements in this section.
	// This will set their UiConstrainedSize components to the correct size,
	// which we will then use to push the correct item width at draw time.
	CalculateElementConstrainedSizes();

	for(std::shared_ptr<UiElement> UiElement : UiElements)
	{
		UiElement->Tick();
	}

	ImGui::End();
}

void UiSection::CalculateElementConstrainedSizes()
{
	CalculateSyncedSize();

	const float SpaceAvailable = ImGui::GetContentRegionAvail().x;

	for (std::shared_ptr<UiElement> UiElement : UiElements)
	{
		// Calculate the constrained size for each element in this section.
		UiElement->CalculateConstrainedSize(
			std::make_shared<UiConstrainedSize>(SpaceAvailable),
			SyncedSize
		);
	}
}

void UiSection::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	UiElements.push_back(NewElement);
}

void UiSection::CalculateSyncedSize() const
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

