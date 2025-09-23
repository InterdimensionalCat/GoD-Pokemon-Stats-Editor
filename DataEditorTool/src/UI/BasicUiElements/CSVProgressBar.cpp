#include "include.h"
#include "UI/BasicUiElements/CSVProgressBar.h"
#include "UI/UiSection.h"

CSVProgressBar::CSVProgressBar
(
	const std::string& InName,
	UiSection* InParent
) :
	UiElement(InName, InParent)
{

}

void CSVProgressBar::Tick()
{
	// Set the progress bar color style var.
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ProgressBarColor);

	ItemWidth = ImGui::CalcItemWidth();

	// Show a Progress Bar
	ImGui::ProgressBar(CurrentProgress, ImVec2(ItemWidth, 0), "");

	ImGui::PopStyleColor();
}

void CSVProgressBar::SetCurrentProgress(const float NewProgress)
{
	CurrentProgress = NewProgress;
}

void CSVProgressBar::SetProgressBarColor(const ImVec4& NewColor)
{
	ProgressBarColor = NewColor;
}

void CSVProgressBar::PushConstrainedElementSize()
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
			ItemWidth = ParentSizeConstraints.CalculateSizeFromSpaceAvailable(SpaceAvailable, MaxLabelSize, ParentSection->GetNumItemsThisLine());
			return;
		}
		[[fallthrough]];
	case UiSizeSource_Self:
		[[fallthrough]]; // Falls through to default behavior
	default:
		ItemWidth = GetSize().CalculateSizeFromSpaceAvailable(SpaceAvailable, MaxLabelSize, ParentSection->GetNumItemsThisLine());
		break;
	}
}