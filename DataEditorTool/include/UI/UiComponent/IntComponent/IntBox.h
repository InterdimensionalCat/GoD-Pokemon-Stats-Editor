/*****************************************************************//**
 * \file   IntBox.h
 * \brief  UiComponent that displays and edits an integer value via an input int box with optional step buttons.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiComponent/UiComponent.h"

/**
 * \brief  UiComponent that displays and edits an integer value via an input int box with optional step buttons.
 */
class IntBox : public UiComponent
{
public:

	/**
	 * Construct an IntBox with the supplied name, parent element,
	 * step size, and fast step size.
	 * This IntBox will have a label by default.
	 * 
	 * \param InName Name of this IntBox.
	 * \param InParent Parent UiSingleElement of this IntBox.
	 * \param InStepSize The amount to increment/decrement the value by when the step buttons are pressed. Default is 0 (no step buttons).
	 * \param InFastStepSize The amount to increment/decrement the value by when the fast step buttons are pressed. Default is 0 (no fast step buttons).
	 */
	IntBox
	(
		const std::string& InName,
		UiSingleElement* InParent,
		const int InStepSize = 0,
		const int InFastStepSize = 0
	);

	/**
	 * Display this IntBox using ImGui::InputInt with optional step buttons.
	 */
	virtual void DisplayComponent() override;

	/**
	 * Set this element's min required size by passing in the
	 * number of digits this should be able to show.
	 * Will factor in step counter size if enabled.
	 * 
	 * \param MinNumDigits The minimum number of digits this element should be able to show.
	 */
	void SetElementMinSize(const uint32_t MinNumDigits);

	/**
	 * Set this element's max required size by passing in the
	 * number of digits this should be able to show.
	 * Will factor in step counter size if enabled.
	 * 
	 * \param MaxNumDigits The maximum number of digits this element should be able to show.
	 */
	void SetElementMaxSize(const uint32_t MaxNumDigits);

	/**
	 * Set the Min/Max value bounds.
	 * 
	 * \param NewMinValue The new minimum value.
	 * \param NewMaxValue The new maximum value.
	 */
	void SetBounds(const int NewMinValue, const int NewMaxValue);

	/**
	 * Set the value of the internal integer buffer used by this IntBox.
	 * 
	 * \param NewBufferValue The new value for the internal integer buffer.
	 */
	void SetIntBuffer(const int NewBufferValue);

	/**
	 * Get the value of the internal integer buffer used by this IntBox.
	 * 
	 * \return The value of the internal integer buffer.
	 */
	int GetIntBuffer() const;

	/**
	 * Get the minimum value bound.
	 * 
	 * \return The minimum value bound.
	 */
	int GetMinValue() const;

	/**
	 * Get the maximum value bound.
	 *
	 * \return The maximum value bound.
	 */
	int GetMaxValue() const;

	/**
	 * Calculate the internal space required by this IntBox,
	 * excluding label size.
	 * 
	 * \return The internal space required by this IntBox, excluding label size.
	 */
	virtual float CalculateInternalSpace() const override;

private:

	/* The amount to increment/decrement the value by when the step buttons are pressed. */
	const int StepSize;

	/* The amount to increment/decrement the value by when the step buttons are pressed with shift held down. */
	const int FastStepSize;

	/** The minimum value bound */
	int MinValue;

	/** The maximum value bound */
	int MaxValue;

	/* The internal integer buffer used by ImGui::InputInt. */
	int IntBuffer = -1;
};
