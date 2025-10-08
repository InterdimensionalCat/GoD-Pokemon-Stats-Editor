/*****************************************************************//**
 * \file   UiSummedSize.h
 * \brief  UiCompoundSize that computes its bounds as the sum of multiple UiSizes.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSize/UiCompoundSize.h"

/**
 * \brief	UiSize that computes its bounds as the sum of multiple UiSizes.
 */
class UiSummedSize : public UiCompoundSize
{
public:

	/** Constructs a UiSummedSize with no size constraints. */
	UiSummedSize();

	/**
	 * Constructs a UiSummedSize that computes its bounds from
	 * the supplied UiSizes. A UiSummedSize's bounds are the sum
	 * of the bounds of its considered sizes.
	 * 
	 * \param InSizesToConsider The UiSizes to consider when calculating bounds.
	 */
	UiSummedSize(const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider);

	/**
	* Get the calculated label size, including the ItemInnerSpacing
	* between the element and its label.
	* 
	* \return The calculated label size, including spacing.
	*/
	virtual float GetLabelSizeWithSpacing() const override;

	/**
	 * Get the calculated label size, excluding the ItemInnerSpacing
	 * between the element and its label.
	 * 
	 * \return The calculated label size, excluding spacing.
	 */
	virtual float GetLabelSizeWithoutSpacing() const override;

	/**
	 * Get the calculated Minimum bound of this UiSize (including the label size).
	 * 
	 * \return The calculated Minimum bound of this UiSize (including the label size).
	 */
	virtual float GetMinWithLabel() const override;

	/**
	 * Get the calculated Minimum bound of this UiSize (excluding the label size).
	 * 
	 * \return The calculated Minimum bound of this UiSize (excluding the label size).
	 */
	virtual float GetMinWithoutLabel() const override;

	/**
	 * Get the calculated Maximum bound of this UiSize (including the label size).
	 * NOTE: this will return the Minimum bound if bIsFixedSize is true.
	 * 
	 * \return The calculated Maximum bound of this UiSize (including the label size).
	 * \note This will return the Minimum bound if bIsFixedSize is true.
	 */
	virtual float GetMaxWithLabel() const override;

	/**
	 * Get the calculated Maximum bound of this UiSize (excluding the label size).
	 * NOTE: this will return the Minimum bound if bIsFixedSize is true.
	 * 
	 * \return The calculated Maximum bound of this UiSize (excluding the label size).
	 * \note This will return the Minimum bound if bIsFixedSize is true.
	 */
	virtual float GetMaxWithoutLabel() const override;
};