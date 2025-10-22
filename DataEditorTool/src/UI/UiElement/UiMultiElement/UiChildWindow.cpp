#include "include.h"
#include "UI/UiElement/UiMultiElement/UiChildWindow.h"
#include "UI/UiSize/UiSyncedSize.h"
#include "UI/UiSize/UiConstrainedSizeWithLabel.h"

UiChildWindow::UiChildWindow
(
	const std::string& InName,
	UiSection* InParent
) :
	UiMultiElement(InName, InParent),
	SyncedSize(std::make_shared<UiSyncedSize>())
{
	ConstrainedSize = std::make_shared<UiConstrainedSizeWithLabel>();
}

void UiChildWindow::Tick()
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

	// Begin the child window
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.f, 0.f, 0.f, 1.f));
	//ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = ImGui::GetStyle().Colors[ImGuiCol_WindowBg] + ImVec4(0.f, 0.2f, 0.4f, 1.f);
	auto WindowHeight = ImGui::GetFrameHeightWithSpacing() * GetNumLines();// + ImGui::GetStyle().ScrollbarSize;
	if (ImGui::BeginChild(GetInvisibleName().c_str(), ImVec2(ConstrainedSize->GetConstrainedSize(), WindowHeight), 0, 0))
	{
		// Tick all child elements within the child window
		UiMultiElement::Tick();
		// End the child window
	}
	ImGui::EndChild();
	//ImGui::PopStyleColor();
}


void UiChildWindow::CalculateConstrainedSize(const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize, const std::shared_ptr<const UiSize>& ParentSizeConstraints)
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

void UiChildWindow::SetSameLine(const bool bInSameLine)
{
	bIsSameLine = bInSameLine;
	SameLineOffsetFromStart = 0.f;
}

void UiChildWindow::SetSameLine(const float OffsetFromStart)
{
	bIsSameLine = true;
	SameLineOffsetFromStart = OffsetFromStart;
}

void UiChildWindow::CalculateSyncedSize()
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

void UiChildWindow::SetNumLines(const int32_t InNumLines)
{
	NumLines = InNumLines;
}

void UiChildWindow::SetIsFixedSize(const bool bInIsFixedSize)
{
	SyncedSize->SetIsFixedSize(bInIsFixedSize);
}

void UiChildWindow::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	UiMultiElement::AddElement(NewElement);
}

std::shared_ptr<const UiSize> UiChildWindow::GetSizeConstraints() const
{
	return SyncedSize;
}

int32_t UiChildWindow::GetNumLines() const
{
	return NumLines;
}