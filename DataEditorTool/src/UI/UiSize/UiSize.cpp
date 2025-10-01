#include "include.h"
#include "Ui/UiSize/UiSize.h"

UiSizeBound::UiSizeBound(
	const std::string& InContentSize,
	const float InInternalSpace,
	const float InExtraSpace
) :
	ContentSize(InContentSize),
	InternalSpace(InInternalSpace),
	ExtraSpace(InExtraSpace)
{
}

float UiSizeBound::CalculateBound() const
{
	return ImGui::CalcTextSize(ContentSize.c_str()).x + 
		InternalSpace + 
		ExtraSpace;
}

UiSize::UiSize() :
	MinBound(UiSizeBound("", 0.f, 0.f)),
	MaxBound(UiSizeBound("", 0.f, FLT_MAX)),
	Label(""),
	bIsFixedSize(false)
{

}

UiSize::UiSize(
	const UiSizeBound& InMin,
	const UiSizeBound& InMax,
	const std::string& InLabel
) :
	MinBound(InMin),
	MaxBound(InMax),
	Label(InLabel),
	bIsFixedSize(false)
{

}

void UiSize::SetMin(const UiSizeBound& InMin)
{
	MinBound = InMin;
}

void UiSize::SetMax(const UiSizeBound& InMax)
{
	MaxBound = InMax;
}

void UiSize::SetIsFixedSize(const bool IsFixedSize)
{
	bIsFixedSize = IsFixedSize;
}

void UiSize::SetLabel(const std::string& InLabel)
{
	Label = InLabel;
}

//float UiSize::CalculateSizeFromSpaceAvailable(const float SpaceAvailable, const float LabelSize, const uint32_t NumItemsPerLine) const
//{
//	if (NumItemsPerLine == 0)
//	{
//		throw std::exception("Size must be calculated with at least 1 item per line");
//	}
//
//	const float SpaceAvailblePerLine = SpaceAvailable / (float)NumItemsPerLine;
//	const float MinSize = GetMin();
//	const float MaxSize = GetMax() / (float)NumItemsPerLine;
//
//	// Default to the min size available, never go lower than this.
//	float ElementSize = MinSize;
//
//	// If the constraints are invalid (Min is greater than Max), 
//	// or if the sizing rule is set to fixed size,
//	// fall back to a fixed size equal to the min.
//	if (MinSize > MaxSize || bIsFixedSize)
//	{
//		return ElementSize;
//	}
//
//	// If we have more space than the min available set the element size to the
//	// max space available, leaving room for the label, or the max size, whichever
//	// is smaller.
//	if (SpaceAvailblePerLine - LabelSize > ElementSize)
//	{
//		ElementSize = std::min(MaxSize, SpaceAvailblePerLine - LabelSize);
//	}
//
//	//// Attempt to make the element the max size with the label fully visible, 
//	//// but ensure it is no longer than the size available.
//	//ElementSize = std::min(MaxSize, SpaceAvailblePerLine - LabelSize);
//
//	//// If we have less than the max size available including the label,
//	//// then cut off the label to keep us at max size.
//	//if (SpaceAvailblePerLine < ElementSize + LabelSize)
//	//{
//	//	// If we have more space available than the max size, we can show some of the label
//	//	// by setting the element size equal to the max size.
//	//	if (SpaceAvailblePerLine > MaxSize)
//	//	{
//	//		ElementSize = MaxSize;
//	//	}
//	//	else
//	//	{
//	//		// But if we have less space available than even the max size, we then
//	//		// need to scale down to the space avalible. This will almost entirely
//	//		// cut off the label.
//	//		ElementSize = SpaceAvailblePerLine;
//	//	}
//	//}
//
//	//// If the element was set to the amount of space available, it might be lower than the minimum
//	//// element size, so we need to clamp it to the min size.
//	//ElementSize = std::max(ElementSize, MinSize);
//
//	return ElementSize;
//}

std::string UiSize::GetLabel() const
{
	return Label;
}

float UiSize::GetLabelSizeWithSpacing() const
{
	auto LabelSize = GetLabelSizeWithoutSpacing();

	// If the label size is not 0,
	// then return the label size + InnerItemSpacing,
	// otherwise return 0.
	if(LabelSize > 0.f)
	{
		auto& Style = ImGui::GetStyle();
		return LabelSize + Style.ItemInnerSpacing.x;
	}
	else
	{
		return 0.f;
	}
}

float UiSize::GetLabelSizeWithoutSpacing() const
{
	return ImGui::CalcTextSize(Label.c_str()).x;
}

float UiSize::GetMinWithLabel() const
{
	return GetMinWithoutLabel() + GetLabelSizeWithSpacing();
}

float UiSize::GetMinWithoutLabel() const
{
	return MinBound.CalculateBound();
}

float UiSize::GetMaxWithLabel() const
{
	if(GetIsFixedSize())
	{
		// If this is a fixed size element, ignore the max size
		// and return the min size.
		return GetMinWithLabel();
	}
	else
	{
		return GetMaxWithoutLabel() + GetLabelSizeWithSpacing();
	}
}

float UiSize::GetMaxWithoutLabel() const
{
	if (IsFixedSize())
	{
		// If this is a fixed size element, ignore the max size
		// and return the min size.
		return GetMinWithoutLabel();
	}
	else
	{
		return MaxBound.CalculateBound();
	}
}

bool UiSize::IsFixedSize() const
{
	return bIsFixedSize;
}
