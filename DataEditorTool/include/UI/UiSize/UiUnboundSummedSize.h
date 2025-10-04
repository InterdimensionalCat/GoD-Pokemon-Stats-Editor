#pragma once

#include "UI/UiSize/UiSummedSize.h"

class UiUnboundSummedSize : public UiSummedSize
{
public:

	UiUnboundSummedSize();
	UiUnboundSummedSize(const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider);

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