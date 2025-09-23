#pragma once
#include "UI/UiElement.h"

class CSVProgressBar : public UiElement
{
public:

	CSVProgressBar
	(
		const std::string& InName,
		UiSection* InParent
	);

	virtual void Tick() override;

	void SetCurrentProgress(const float NewProgress);

	void SetProgressBarColor(const ImVec4& NewColor);

	virtual void PushConstrainedElementSize() override;

private:

	float CurrentProgress = 0.f;

	float ItemWidth = 128.f;
	
	ImVec4 ProgressBarColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
};
