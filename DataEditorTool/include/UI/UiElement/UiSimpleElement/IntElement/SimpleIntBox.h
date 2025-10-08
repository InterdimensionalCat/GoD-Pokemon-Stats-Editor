/*****************************************************************//**
 * \file   SimpleIntBox.h
 * \brief  SingleUiElement that manages an IntBox component.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiElement/UiSingleElement.h"

class IntBox;

/**
 * \brief SingleUiElement that manages an IntBox component.
 * 
 * A SimpleIntBox is a UiSingleElement that manages an IntBox
 * component, allowing the user to input and manipulate integer
 * values. It provides functionality to set value bounds,
 * step sizes, and buffer values, as well as configuring
 * the display size based on the number of digits.
 */
class SimpleIntBox : public UiSingleElement
{
public:

	/**
	 * Construct a SimpleIntBox with the supplied name, parent section,
	 * step size, and fast step size.
	 * 
	 * \param InName Name of this SimpleIntBox.
	 * \param InParent Parent section of this SimpleIntBox.
	 * \param InStepSize The step size for incrementing/decrementing the value.
	 * \param InFastStepSize The fast step size for larger increments/decrements.
	 */
	SimpleIntBox
	(
		const std::string& InName,
		UiSection* InParent,
		const int InStepSize = 0,
		const int InFastStepSize = 0
	);

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * Does nothing for a SimpleIntBox.
	 */
	virtual void UiComponentUpdated() override;

	/**
	 * Set this element's min required size by passing in the
	 * number of digits this should be able to show.
	 * Will factor in step counter size if enabled.
	 * 
	 * \param MinNumDigits The minimum number of digits to display.
	 */
	void SetElementMinSize(const uint32_t MinNumDigits);

	/**
	 * Set this element's max required size by passing in the
	 * number of digits this should be able to show.
	 * Will factor in step counter size if enabled.
	 * 
	 * \param MaxNumDigits The maximum number of digits to display.
	 */
	void SetElementMaxSize(const uint32_t MaxNumDigits);

	/**
	 * Set the Min/Max value bounds.
	 * 
	 * \param NewMinValue New minimum value.
	 */
	void SetBounds(const int NewMinValue, const int NewMaxValue);

	/**
	 * Set the current int buffer value in the IntBox component.
	 * 
	 * \param NewBufferValue The new buffer value to set.
	 */
	void SetIntBuffer(const int NewBufferValue);

	/**
	 * Get the max value allowed by this IntBox.
	 * 
	 * \return The max value allowed by this IntBox.
	 */
	int GetMinValue() const;

	/**
	 * Get the max value allowed by this IntBox.
	 * 
	 * \return The max value allowed by this IntBox.
	 */
	int GetMaxValue() const;

private:

	/* The IntBox component managed by this SimpleIntBox. */
	std::shared_ptr<IntBox> IntBoxComponent;
};
