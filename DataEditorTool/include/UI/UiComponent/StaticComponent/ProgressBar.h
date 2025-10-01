#pragma once
#include "UI/UiComponent/UiComponent.h"

class ProgressBar : public UiComponent
{
public:

	ProgressBar
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	virtual void DisplayComponent() override;

	void SetCurrentProgress(const float NewProgress);

	void SetProgressBarColor(const ImVec4& NewColor);

	void SetBarMinSize(const float InMinSize);

	bool HasLabel() const override;

	virtual float CalculateInternalSpace() const override;

private:

	float CurrentProgress = 0.f;

	ImVec4 ProgressBarColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
};
