#pragma once

#include "UI/UiSize/UiSize.h"

class UiCompoundSize : public UiSize
{

public:

	/** Constructs a UiCompoundSize with no size constraints. */
	UiCompoundSize();

	/**
	 * Constructs a UiCompoundSize that computes its bounds from
	 * the supplied UiSizes. The logic for computing bounds from
	 * these considered sizes varies based on subclass.
	 */
	UiCompoundSize(const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider);

	/**
	 * Add a UiSize to consider when calculating the bounds
	 * of this UiCompoundSize.
	 */
	void AddSizeToConsider(const std::shared_ptr<const UiSize>& SizeToConsider);

	/**
	 * Remove a UiSize to consider when calculating the bounds
	 * of this UiCompoundSize.
	 */
	void RemoveSizeToConsider(const std::shared_ptr<const UiSize>& SizeToConsider);

	/**
	 * Remove all UiSizes to consider when calculating the 
	 * bounds of this UiCompoundSize.
	 */
	void ClearSizesToConsider();

	/** Subclasses must re-implement the following functions to behave correctly: */

	/** 
	 * Get the calculated label size, including the ItemInnerSpacing
	 * between the element and its label.
	 */
	virtual float GetLabelSizeWithSpacing() const override = 0;

	/**
	 * Get the calculated label size, excluding the ItemInnerSpacing
	 * between the element and its label.
	 */
	virtual float GetLabelSizeWithoutSpacing() const override = 0;

	/** Get the calculated Minimum bound of this UiSize (including the label size) */
	virtual float GetMinWithLabel() const override = 0;

	/** Get the calculated Minimum bound of this UiSize (excluding the label size) */
	virtual float GetMinWithoutLabel() const override = 0;

	/**
	 * Get the calculated Maximum bound of this UiSize (including the label size).
	 * NOTE: this will return the Minimum bound if bIsFixedSize is true.
	 */
	virtual float GetMaxWithLabel() const override = 0;

	/**
	 * Get the calculated Maximum bound of this UiSize (excluding the label size).
	 * NOTE: this will return the Minimum bound if bIsFixedSize is true.
	 */
	virtual float GetMaxWithoutLabel() const override = 0;

protected:

	std::vector<std::shared_ptr<const UiSize>> SizesToConsider;
};