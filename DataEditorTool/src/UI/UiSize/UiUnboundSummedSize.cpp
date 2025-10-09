#include "include.h"
#include "UI/UiSize/UiUnboundSummedSize.h"

UiUnboundSummedSize::UiUnboundSummedSize()
	: UiSummedSize()
{

}

UiUnboundSummedSize::UiUnboundSummedSize(const std::vector<std::shared_ptr<const UiSize>>& InSizesToConsider)
	: UiSummedSize(InSizesToConsider)
{

}

float UiUnboundSummedSize::GetMaxWithLabel() const
{
	return FLT_MAX;
}

float UiUnboundSummedSize::GetMaxWithoutLabel() const
{
	return FLT_MAX;
}
