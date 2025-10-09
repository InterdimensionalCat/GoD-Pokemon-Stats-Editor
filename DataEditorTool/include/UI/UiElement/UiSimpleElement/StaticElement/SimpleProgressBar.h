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

/**
 * \brief UiSingleElement that manages a ProgressBar component.
 * 
 * A SimpleProgressBar displays a progress bar with a specified
 * progress value between 0.0 and 1.0. The color and minimum size
 * of the progress bar can also be customized.
 */
class SimpleProgressBar : public UiSingleElement
{
public:

	/**
	 * Construct a SimpleProgressBar with the supplied name and parent section.
	 * 
	 * \param InName Name of this SimpleProgressBar.
	 * \param InParent Parent section of this SimpleProgressBar.
	 */
	SimpleProgressBar
	(
		const std::string& InName,
		UiSection* InParent
	);

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * Does nothing for a SimpleProgressBar.
	 */
	virtual void UiComponentUpdated() override;

	/**
	 * Set the current progress of the progress bar.
	 * 
	 * \param NewProgress The new progress value, between 0.0 and 1.0.
	 */
	void SetCurrentProgress(const float NewProgress);

	/**
	 * Set the color of the progress bar.
	 * 
	 * \param NewColor The new color of the progress bar.
	 */
	void SetProgressBarColor(const ImVec4& NewColor);

	/**
	 * Set the minimum size of the progress bar.
	 * 
	 * \param InMinSize The new minimum size of the progress bar.
	 */
	void SetBarMinSize(const float InMinSize);

private:

	/* The ProgressBar component managed by this SimpleProgressBar. */
	std::shared_ptr<ProgressBar> ProgressBarComponent;
};
