/*****************************************************************//**
 * \file   UiConstrainedSizeWithLabel.h
 * \brief  UiConstrainedSize that includes label size in its final size.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSize/UiConstrainedSize.h"

class UiSize;

/**
 * \brief  UiConstrainedSize that includes label size in its final size.
 * 
 * Unlike the base UiConstrainedSize implementation, this implementation
 * will not subtract the label size from the space available when calculating
 * its constrained size, and will instead include the label size in its final
 * constrained size. This is useful for UiMultiElements, which use their
 * constrained size as the space available for their child UI elements, rather
 * than for ImGui's PushItemWidth function.
 */
class UiConstrainedSizeWithLabel : public UiConstrainedSize
{

public:

	/** Constructs a UiConstrainedSizeWithLabel with a constrained size of 0. */
	UiConstrainedSizeWithLabel();

	/**
	 * Constructs a UiConstrainedSizeWithLabel with the given constrained size.
	 * 
	 * \param InConstrainedSize The initial constrained size.
	 */
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
	 * 
	 * \param SpaceAvailable The space available to this UiElement.
	 * \param SizeConstraints The size constraints to use when calculating the constrained size.
	 */
	virtual void CalculateFromSizeConstraints(
		const float SpaceAvailable,
		const std::shared_ptr<const UiSize> SizeConstraints
	) override;

};