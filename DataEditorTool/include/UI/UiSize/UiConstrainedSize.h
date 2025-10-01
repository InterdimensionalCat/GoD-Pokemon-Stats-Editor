#pragma once

class UiSize;

class UiConstrainedSize
{

public:

	UiConstrainedSize();

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
	 */
	virtual void CalculateFromSizeConstraints(
		const float SpaceAvailable,
		const std::shared_ptr<const UiSize> SizeConstraints
	);

	/** Directly set the constrained size to the supplied value */
	void SetConstrainedSize(const float InConstrainedSize);

	/**
	 * Returns the calculated constrained size.
	 * 
	 * NOTE: this does not include the element's label
	 * or the space between the label and the element.
	 */
	float GetConstrainedSize() const;

protected:

	float ConstrainedSize = 0.f;
};