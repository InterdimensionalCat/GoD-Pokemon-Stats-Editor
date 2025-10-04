#include "include.h"
#include "UI/UiComponent/StaticComponent/ProgressBar.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"

ProgressBar::ProgressBar
(
	const std::string& InName,
	UiSingleElement* InParent
) :
	UiComponent(InName, InParent, false)
{
	SetBarMinSize(128.f);
}

void ProgressBar::DisplayComponent()
{
	// Set the progress bar color style var.
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ProgressBarColor);

	// const float BarSize = ImGui::CalcItemWidth();

	// Show a Progress Bar
	ImGui::ProgressBar(CurrentProgress, ImVec2(ImGui::CalcItemWidth(), 0), "");

	ImGui::PopStyleColor();
}

void ProgressBar::SetCurrentProgress(const float NewProgress)
{
	CurrentProgress = NewProgress;
}

void ProgressBar::SetProgressBarColor(const ImVec4& NewColor)
{
	ProgressBarColor = NewColor;
}

void ProgressBar::SetBarMinSize(const float InMinSize)
{
	// Progress bars don't have a content string they need to be 
	// big enough to display, so we set a min size in pixels using 
	// the ExtraSpace parameter.
	ComponentSize->SetMin(UiSizeBound("", CalculateInternalSpace(), InMinSize));
}

float ProgressBar::CalculateInternalSpace() const
{
	// Progress bars never have an internal size.
	return 0.f;
}