/*****************************************************************//**
 * \file   SimpleProgressBar.h
 * \brief  UiSingleElement that manages a ProgressBar component.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
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

	virtual void UiComponentUpdated() override;

	void SetCurrentProgress(const float NewProgress);

	void SetProgressBarColor(const ImVec4& NewColor);

	void SetBarMinSize(const float InMinSize);

private:

	std::shared_ptr<ProgressBar> ProgressBarComponent;
};
