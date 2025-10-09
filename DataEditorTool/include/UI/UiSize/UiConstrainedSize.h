/*****************************************************************//**
 * \file   UiConstrainedSize.h
 * \brief  Class that handles the constrained size of a UiElement
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

class UiSize;

/**
 * \brief  Class that contains the calculated constrained size of a UiElement.
 * 
 * A UiConstrainedSize contains the calculated size of a UiElement
 * after taking into account its size constraints and the space
 * available to it. It can calculate the correct size based on
 * supplied size constraints and available space.
 * 
 * \note The base implementation will subtract the label size from the space
 * available and return the constrained size excluding the label size. This is because
 * ImGui's PushItemWidth function, which is used to set the width of the underlying UI
 * element, does not include the label size in the width it sets.
 */
class UiConstrainedSize
{

public:

	/** Constructs a UiConstrainedSize with a constrained size of 0. */
	UiConstrainedSize();

	/**
	 * Constructs a UiConstrainedSize with the given constrained size.
	 * 
	 * \param InConstrainedSize The initial constrained size.
	 */
	UiConstrainedSize(const float InConstrainedSize);

	/**
	 * Recalculate this constrained size from the given
	 * size constraints and the available space.
	 * 
	 * This will set the constrained size to be as large
	 * as possible without exceeding the max size constraint
	 * or space available. If the amount of space available
	 * is less then the min size constraint, then we will not
	 * go lower than the min to accommodate for 
	 * the space available.
	 * 
	 * \param SpaceAvailable The space available to this UiElement.
	 * \param SizeConstraints The size constraints to use when calculating the constrained size.
	 */
	virtual void CalculateFromSizeConstraints(
		const float SpaceAvailable,
		const std::shared_ptr<const UiSize> SizeConstraints
	);

	/**
	 * Directly set the constrained size to the supplied value.
	 * 
	 * \param InConstrainedSize The new constrained size.
	 * \note This will not factor in any size constraints.
	 */
	void SetConstrainedSize(const float InConstrainedSize);

	/**
	 * Returns the calculated constrained size.
	 * 
	 * NOTE: this does not include the element's label
	 * or the space between the label and the element.
	 * 
	 * \return The calculated constrained size.
	 * \note This does not include the element's label or spacing.
	 */
	float GetConstrainedSize() const;

protected:

	/** The calculated constrained size of this UiElement. */
	float ConstrainedSize = 0.f;
};