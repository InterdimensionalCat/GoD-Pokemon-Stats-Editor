/*****************************************************************//**
 * \file   UiUnboundSummedSize.h
 * \brief  UiSummedSize that has no upper bound on its maximum size.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSize/UiSummedSize.h"

/**
 * \brief	UiSummedSize that has no upper bound on its maximum size.
 * 
 * This is useful for multi UI elements that should expand to fill available space,
 * such as a UiElementGrid.
 */
class UiUnboundSummedSize : public UiSummedSize
{
public:

	/** Constructs a UiUnboundSummedSize with no size constraints. */
	UiUnboundSummedSize();

	/**
	 * Constructs a UiUnboundSummedSize that computes its bounds from
	 * the supplied UiSizes. A UiUnboundSummedSize's bounds are the sum
	 * of the bounds of its considered sizes, but its maximum bound is
	 * always unbounded (infinity).
	 * 
	 * \param InSizesToConsider The UiSizes to consider when calculating bounds.
	 */
	UiUnboundSummedSize(const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider);

	/**
	 * Get the calculated Maximum bound of this UiSize (including the label size).
	 * NOTE: This is always FLT_MAX for a UiUnboundSummedSize, even if bIsFixedSize is true.
	 * 
	 * \return The calculated Maximum bound of this UiSize (including the label size).
	 * \note This is always FLT_MAX for a UiUnboundSummedSize, even if bIsFixedSize is true.
	 */
	virtual float GetMaxWithLabel() const override;

	/**
	 * Get the calculated Maximum bound of this UiSize (excluding the label size).
	 * NOTE: This is always FLT_MAX for a UiUnboundSummedSize, even if bIsFixedSize is true.
	 * 
	 * \return The calculated Maximum bound of this UiSize (excluding the label size).
	 * \note This is always FLT_MAX for a UiUnboundSummedSize, even if bIsFixedSize is true.
	 */
	virtual float GetMaxWithoutLabel() const override;
};