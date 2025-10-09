/*****************************************************************//**
 * \file   ProgressBar.h
 * \brief  UiComponent that displays a progress bar.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiComponent/UiComponent.h"

/**
 * \brief  UiComponent that displays a progress bar.
 */
class ProgressBar : public UiComponent
{
public:

	/**
	 * Construct a ProgressBar with the supplied name and parent element.
	 * This ProgressBar will have no label by default.
	 * 
	 * \param InName Name of this ProgressBar.
	 * \param InParent Parent UiSingleElement of this ProgressBar.
	 */
	ProgressBar
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	/**
	 * Display this ProgressBar using ImGui::ProgressBar.
	 */
	virtual void DisplayComponent() override;

	/**
	 * Set the current progress of this ProgressBar.
	 * 
	 * \param NewProgress The new progress value, between 0.0f and 1.0f.
	 */
	void SetCurrentProgress(const float NewProgress);

	/**
	 * Set the color of the progress bar.
	 * 
	 * \param NewColor The new color of the progress bar, as an ImVec4.
	 */
	void SetProgressBarColor(const ImVec4& NewColor);

	/**
	 * Set this progress bar's minimum size in pixels.
	 * 
	 * \param InMinSize The minimum size in pixels.
	 */
	void SetBarMinSize(const float InMinSize);

	/**
	 * Calculate the internal space required by this ProgressBar,
	 * excluding label size.
	 * 
	 * \return The internal space required by this ProgressBar, excluding label size.
	 */
	virtual float CalculateInternalSpace() const override;

private:

	/** Current progress value, between 0.0f and 1.0f. */
	float CurrentProgress = 0.f;

	/** The current color of this progress bar. */
	ImVec4 ProgressBarColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
};
