#include "include.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleProgressBar.h"

#include "UI/UiComponent/StaticComponent/ProgressBar.h"
#include "UI/UiSection.h"

SimpleProgressBar::SimpleProgressBar
(
	const std::string& InName,
	UiSection* InParent
) :
	UiSingleElement(InName, InParent),
	ProgressBarComponent(std::make_shared<ProgressBar>(InName, this))
{
	SetUiComponent(ProgressBarComponent);
}

void SimpleProgressBar::ComponentUpdated()
{
	// Implementation intentionally left blank.
}

void SimpleProgressBar::SetCurrentProgress(const float NewProgress)
{
	ProgressBarComponent->SetCurrentProgress(NewProgress);
}

void SimpleProgressBar::SetProgressBarColor(const ImVec4& NewColor)
{
	ProgressBarComponent->SetProgressBarColor(NewColor);
}