#pragma once
#include "UI/UiElement/UiSingleElement.h"

class ProgressBar;
class UiSection;

class SimpleProgressBar : public UiSingleElement
{
public:

	SimpleProgressBar
	(
		const std::string& InName,
		UiSection* InParent
	);

	virtual void ComponentUpdated() override;

	void SetCurrentProgress(const float NewProgress);

	void SetProgressBarColor(const ImVec4& NewColor);

private:

	std::shared_ptr<ProgressBar> ProgressBarComponent;
};
