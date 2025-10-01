#pragma once

#include "UI/UiSize/UiCompoundSize.h"

class UiSyncedSize : public UiCompoundSize
{
public:
	/** Constructs a UiSyncedSize with no size constraints. */
	UiSyncedSize();

	/**
	 * Constructs a UiSyncedSize that computes its bounds from
	 * the supplied UiSizes. The bounds of a UiSyncedSize are the
	 * largest min and smallest max of its considered sizes,
	 * and the label size is largest label size of its considered sizes.
	 */
	UiSyncedSize(const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider);

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