/*****************************************************************//**
 * \file   IntSlider.h
 * \brief  UiComponent that displays and edits an integer value via a slider.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiComponent/UiComponent.h"

class UiElement;

/**
 * \brief  UiComponent that displays and edits an integer value via a slider.
 */
class IntSlider : public UiComponent
{
public:

	/**
	 * Construct an IntSlider with the supplied name, parent element,
	 * minimum value, and maximum value.
	 * This IntSlider will have a label by default.
	 * 
	 * \param InName Name of this IntSlider.
	 * \param InParent Parent UiSingleElement of this IntSlider.
	 * \param InMinValue The minimum value of the slider. Default is 0.
	 * \param InMaxValue The maximum value of the slider. Default is 3.
	 */
	IntSlider
	(
		const std::string& InName,
		UiSingleElement* InParent,
		const int InMinValue = 0,
		const int InMaxValue = 3
	);

	/**
	 * Display this IntSlider using ImGui::SliderInt.
	 */
	virtual void DisplayComponent() override;

	/**
	 * Set the Min/Max value bounds.
	 *
	 * \param NewMinValue The new minimum value.
	 * \param NewMaxValue The new maximum value.
	 */
	void SetBounds(const int NewMinValue, const int NewMaxValue);

	/**
	 * Set this slider's minimum size in pixels.
	 * 
	 * \param InMinSize The minimum size in pixels.
	 */
	void SetSliderMinSize(const float InMinSize);

	/**
	 * Set the value of the internal integer buffer used by this IntSlider.
	 * 
	 * \param NewBufferValue The new value for the internal integer buffer.
	 */
	void SetIntBuffer(const int NewBufferValue);

	/**
	 * Get the value of the internal integer buffer used by this IntSlider.
	 * 
	 * \return The value of the internal integer buffer.
	 */
	int GetIntBuffer() const;

	/**
	 * Get the minimum value of the slider.
	 * 
	 * \return The minimum value of the slider.
	 */
	int GetMinValue() const;

	/**
	 * Get the maximum value of the slider.
	 * 
	 * \return The maximum value of the slider.
	 */
	int GetMaxValue() const;

	/**
	 * Calculate the internal space required by this IntSlider,
	 * excluding label size.
	 * 
	 * \return The internal space required by this IntSlider, excluding label size.
	 */
	virtual float CalculateInternalSpace() const override;

private:

	/** The minimum value of the slider. */
	int MinValue;

	/** The maximum value of the slider. */
	int MaxValue;

	/* The internal integer buffer used by ImGui::SliderInt. */
	int IntBuffer = 0;
};