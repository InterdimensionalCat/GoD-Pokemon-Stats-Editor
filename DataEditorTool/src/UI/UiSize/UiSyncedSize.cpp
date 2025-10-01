#include "include.h"
#include "UI/UiSize/UiSyncedSize.h"

UiSyncedSize::UiSyncedSize() : UiCompoundSize()
{

}

UiSyncedSize::UiSyncedSize(
	const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider
) :
	UiCompoundSize(InSizesToConsider)
{

}

float UiSyncedSize::GetLabelSizeWithSpacing() const
{
	float LargestLabelSize = 0.f;

	for (const auto& SizeToConsider : SizesToConsider)
	{
		LargestLabelSize = std::max(LargestLabelSize, SizeToConsider->GetLabelSizeWithSpacing());
	}

	return LargestLabelSize;
}

float UiSyncedSize::GetLabelSizeWithoutSpacing() const
{
	float LargestLabelSize = 0.f;

	for (const auto& SizeToConsider : SizesToConsider)
	{
		LargestLabelSize = std::max(LargestLabelSize, SizeToConsider->GetLabelSizeWithoutSpacing());
	}

	return LargestLabelSize;
}

float UiSyncedSize::GetMinWithLabel() const
{
	float LargestMin = 0.f;
	const float LargestLabelWithSpacing = GetLabelSizeWithSpacing();

	// For bounds calculations with labels, we use the largest label size
	// of all considered sizes, instead of each size's individual label size.
	for (const auto& SizeToConsider : SizesToConsider)
	{
		LargestMin = std::max(LargestMin, SizeToConsider->GetMinWithoutLabel() + LargestLabelWithSpacing);
	}

	return LargestMin;
}

float UiSyncedSize::GetMinWithoutLabel() const
{
	float LargestMin = 0.f;

	for (const auto& SizeToConsider : SizesToConsider)
	{
		LargestMin = std::max(LargestMin, SizeToConsider->GetMinWithoutLabel());
	}

	return LargestMin;
}

float UiSyncedSize::GetMaxWithLabel() const
{
	float SmallestMax = std::numeric_limits<float>::max();
	const float LargestLabelWithSpacing = GetLabelSizeWithSpacing();

	// For bounds calculations with labels, we use the largest label size
	// of all considered sizes, instead of each size's individual label size.
	for (const auto& SizeToConsider : SizesToConsider)
	{
		SmallestMax = std::min(SmallestMax, SizeToConsider->GetMaxWithoutLabel() + LargestLabelWithSpacing);
	}

	return SmallestMax;
}

float UiSyncedSize::GetMaxWithoutLabel() const
{
	float SmallestMax = std::numeric_limits<float>::max();

	for (const auto& SizeToConsider : SizesToConsider)
	{
		SmallestMax = std::min(SmallestMax, SizeToConsider->GetMaxWithoutLabel());
	}

	return SmallestMax;
}