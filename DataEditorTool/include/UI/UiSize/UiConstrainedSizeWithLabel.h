#pragma once

#include "UI/UiSize/UiConstrainedSize.h"

class UiSize;

class UiConstrainedSizeWithLabel : public UiConstrainedSize
{

public:

	UiConstrainedSizeWithLabel();

	UiConstrainedSizeWithLabel(const float InConstrainedSize);

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
	 * This particular implementation will include label sizes
	 * in the size constraint calculations, which is needed when
	 * setting size constraints for UiSingleLineMultiElements.
	 */
	virtual void CalculateFromSizeConstraints(
		const float SpaceAvailable,
		const std::shared_ptr<const UiSize> SizeConstraints
	) override;

};