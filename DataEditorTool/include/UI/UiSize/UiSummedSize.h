#pragma once

#include "UI/UiSize/UiCompoundSize.h"

class UiSummedSize : public UiCompoundSize
{
public:

	/** Constructs a UiSummedSize with no size constraints. */
	UiSummedSize();

	/**
	 * Constructs a UiSummedSize that computes its bounds from
	 * the supplied UiSizes. A UiSummedSize's bounds are the sum
	 * of the bounds of its considered sizes.
	 */
	UiSummedSize(const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider);

	/**
	* Get the calculated label size, including the ItemInnerSpacing
	* between the element and its label.
	*/
	virtual float GetLabelSizeWithSpacing() const override;

	/**
	 * Get the calculated label size, excluding the ItemInnerSpacing
	 * between the element and its label.
	 */
	virtual float GetLabelSizeWithoutSpacing() const override;

	/** Get the calculated Minimum bound of this UiSize (including the label size) */
	virtual float GetMinWithLabel() const override;

	/** Get the calculated Minimum bound of this UiSize (excluding the label size) */
	virtual float GetMinWithoutLabel() const override;

	/**
	 * Get the calculated Maximum bound of this UiSize (including the label size).
	 * NOTE: this will return the Minimum bound if bIsFixedSize is true.
	 */
	virtual float GetMaxWithLabel() const override;

	/**
	 * Get the calculated Maximum bound of this UiSize (excluding the label size).
	 * NOTE: this will return the Minimum bound if bIsFixedSize is true.
	 */
	virtual float GetMaxWithoutLabel() const override;
};