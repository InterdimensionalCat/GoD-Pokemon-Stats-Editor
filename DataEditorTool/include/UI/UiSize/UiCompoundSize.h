/*****************************************************************//**
 * \file   UiCompoundSize.h
 * \brief  UiSize that computes its bounds from multiple UiSizes.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSize/UiSize.h"

/**
 * \brief	UiSize that computes its bounds from multiple UiSizes.
 * 
 * This is an abstract base class for UiSizes that compute their
 * bounds from multiple other UiSizes. Subclasses must implement
 * the logic for how the bounds are computed from the considered
 * sizes.
 */
class UiCompoundSize : public UiSize
{

public:

	/** Constructs a UiCompoundSize with no size constraints. */
	UiCompoundSize();

	/**
	 * Constructs a UiCompoundSize that computes its bounds from
	 * the supplied UiSizes. The logic for computing bounds from
	 * these considered sizes varies based on subclass.
	 * 
	 * \param InSizesToConsider The UiSizes to consider when calculating bounds.
	 */
	UiCompoundSize(const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider);

	/**
	 * Add a UiSize to consider when calculating the bounds
	 * of this UiCompoundSize.
	 * 
	 * \param SizeToConsider The UiSize to add.
	 */
	void AddSizeToConsider(const std::shared_ptr<const UiSize>& SizeToConsider);

	/**
	 * Remove a UiSize to consider when calculating the bounds
	 * of this UiCompoundSize.
	 * 
	 * \param SizeToConsider The UiSize to remove.
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
	 * 
	 * \return The calculated label size, including spacing.
	 */
	virtual float GetLabelSizeWithSpacing() const override = 0;

	/**
	 * Get the calculated label size, excluding the ItemInnerSpacing
	 * between the element and its label.
	 * 
	 * \return The calculated label size, excluding spacing.
	 */
	virtual float GetLabelSizeWithoutSpacing() const override = 0;

	/**
	 * Get the calculated Minimum bound of this UiSize (including the label size).
	 * 
	 * \return The calculated Minimum bound of this UiSize (including the label size).
	 */
	virtual float GetMinWithLabel() const override = 0;

	/**
	 * Get the calculated Minimum bound of this UiSize (excluding the label size).
	 * 
	 * \return The calculated Minimum bound of this UiSize (excluding the label size).
	 */
	virtual float GetMinWithoutLabel() const override = 0;

	/**
	 * Get the calculated Maximum bound of this UiSize (including the label size).
	 * NOTE: this will return the Minimum bound if bIsFixedSize is true.
	 * 
	 * \return The calculated Maximum bound of this UiSize (including the label size).
	 * \note This will return the Minimum bound if bIsFixedSize is true.
	 */
	virtual float GetMaxWithLabel() const override = 0;

	/**
	 * Get the calculated Maximum bound of this UiSize (excluding the label size).
	 * NOTE: this will return the Minimum bound if bIsFixedSize is true.
	 * 
	 * \return The calculated Maximum bound of this UiSize (excluding the label size).
	 * \note This will return the Minimum bound if bIsFixedSize is true.
	 */
	virtual float GetMaxWithoutLabel() const override = 0;

protected:

	/** The UiSizes to consider when calculating the bounds of this UiCompoundSize. */
	std::vector<std::shared_ptr<const UiSize>> SizesToConsider;
};