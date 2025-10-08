/*****************************************************************//**
 * \file   UiSyncedSize.h
 * \brief  UiCompoundSize that computes its bounds as the largest min and smallest max of multiple UiSizes.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSize/UiCompoundSize.h"

/**
 * \brief	UiSize that computes its bounds as the largest min and smallest max of multiple UiSizes.
 */
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
	 * 
	 * \param InSizesToConsider The UiSizes to consider when calculating bounds.
	 */
	UiSyncedSize(const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider);

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