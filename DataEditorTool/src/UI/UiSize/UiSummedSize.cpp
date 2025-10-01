#include "include.h"
#include "UI/UiSize/UiSummedSize.h"

UiSummedSize::UiSummedSize() : UiCompoundSize()
{

}

UiSummedSize::UiSummedSize(
const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider
) :
	UiCompoundSize(InSizesToConsider)
{

}

float UiSummedSize::GetLabelSizeWithSpacing() const
{
	float TotalLabelSize = 0.f;

	for (const auto& SizeToConsider : SizesToConsider)
	{
		TotalLabelSize += SizeToConsider->GetLabelSizeWithSpacing();
	}

	return TotalLabelSize;
}

float UiSummedSize::GetLabelSizeWithoutSpacing() const
{
	float TotalLabelSize = 0.f;

	for (const auto& SizeToConsider : SizesToConsider)
	{
		TotalLabelSize += SizeToConsider->GetLabelSizeWithoutSpacing();
	}

	return TotalLabelSize;
}

float UiSummedSize::GetMinWithLabel() const
{
	float TotalMin = 0.f;

	const auto& Style = ImGui::GetStyle();
	const int32_t NumItemSpaces = static_cast<int32_t>(SizesToConsider.size()) - 1;

	for (const auto& SizeToConsider : SizesToConsider)
	{
		TotalMin += SizeToConsider->GetMinWithLabel();
	}

	TotalMin += Style.ItemSpacing.x * NumItemSpaces;

	return TotalMin;
}

float UiSummedSize::GetMinWithoutLabel() const
{
	float TotalMin = 0.f;

	const auto& Style = ImGui::GetStyle();
	const int32_t NumItemSpaces = static_cast<int32_t>(SizesToConsider.size()) - 1;

	for (const auto& SizeToConsider : SizesToConsider)
	{
		TotalMin += SizeToConsider->GetMinWithoutLabel();
	}

	TotalMin += Style.ItemSpacing.x * NumItemSpaces;

	return TotalMin;
}

float UiSummedSize::GetMaxWithLabel() const
{
	float TotalMax = 0.f;
	for (const auto& SizeToConsider : SizesToConsider)
	{
		TotalMax += SizeToConsider->GetMaxWithLabel();
	}

	return TotalMax;
}

float UiSummedSize::GetMaxWithoutLabel() const
{
	float TotalMax = 0.f;
	for (const auto& SizeToConsider : SizesToConsider)
	{
		TotalMax += SizeToConsider->GetMaxWithoutLabel();
	}

	return TotalMax;
}