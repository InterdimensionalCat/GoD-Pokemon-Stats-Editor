#include "include.h"
#include "Ui/UiSize.h"

UiSize::UiSize() :
	SizeRule(UiSizeRule_Normal),
	MinWidth(static_cast<float>(0.f)),
	MaxWidth(static_cast<float>(FLT_MAX))
{
	auto& Style = ImGui::GetStyle();
	SetPaddingSpace(Style.FramePadding.x * 2);
}

UiSize::UiSize(const float InMin, const float InMax) : UiSize()
{
	SetMin(InMin);
	SetMax(InMax);

	auto& Style = ImGui::GetStyle();
	SetPaddingSpace(Style.FramePadding.x * 2);
}

void UiSize::SetMin(const float NewMin)
{
	MinWidth = NewMin;
}

void UiSize::SetMax(const float NewMax)
{
	MaxWidth = NewMax;
}

void UiSize::SetMinFromString(const std::string& NewMinString)
{
	MinWidth = static_cast<std::string>(NewMinString);
}

void UiSize::SetMinFromLongestString(const std::vector<std::string>& MaxStrings)
{
	std::string MaxString = "";
	for (const auto& StringEntry : MaxStrings)
	{
		if (StringEntry.length() > MaxString.length())
		{
			MaxString = StringEntry;
		}
	}

	SetMinFromString(MaxString);
}

void UiSize::SetMaxFromString(const std::string& NewMaxString)
{
	MaxWidth = static_cast<std::string>(NewMaxString);
}

void UiSize::SetMaxFromLongestString(const std::vector<std::string>& MaxStrings)
{
	std::string MaxString = "";
	for (const auto& StringEntry : MaxStrings)
	{
		if (StringEntry.length() > MaxString.length())
		{
			MaxString = StringEntry;
		}
	}

	SetMaxFromString(MaxString);
}

void UiSize::SetMinFromStringLength(const uint32_t NewMinStringLength)
{
	std::string NewMinString = std::string(NewMinStringLength, '-');
	SetMinFromString(NewMinString);
}

void UiSize::SetMaxFromStringLength(const uint32_t NewMaxStringLength)
{
	std::string NewMaxString = std::string(NewMaxStringLength, '-');
	SetMaxFromString(NewMaxString);
}

void UiSize::SetPaddingSpace(const float NewPaddingSpace)
{
	PaddingSpace = NewPaddingSpace;
}

void UiSize::SetSizeRule(const UiSizeRule NewSizeRule)
{
	SizeRule = NewSizeRule;
}

float UiSize::CalculateSizeFromSpaceAvailable(const float SpaceAvailable, const float LabelSize, const uint32_t NumItemsPerLine) const
{
	if (NumItemsPerLine == 0)
	{
		throw std::exception("Size must be calculated with at least 1 item per line");
	}

	const float SpaceAvailblePerLine = SpaceAvailable / (float)NumItemsPerLine;
	const float MinSize = GetMin();
	const float MaxSize = GetMax() / (float)NumItemsPerLine;

	// Default to the min size available, never go lower than this.
	float ElementSize = MinSize;

	// If the constraints are invalid (Min is greater than Max), 
	// or if the sizing rule is set to fixed size,
	// fall back to a fixed size equal to the min.
	if (MinSize > MaxSize || SizeRule == UiSizeRule_FixedSize)
	{
		return ElementSize;
	}

	// If we have more space than the min available set the element size to the
	// max space available, leaving room for the label, or the max size, whichever
	// is smaller.
	if (SpaceAvailblePerLine - LabelSize > ElementSize)
	{
		ElementSize = std::min(MaxSize, SpaceAvailblePerLine - LabelSize);
	}

	//// Attempt to make the element the max size with the label fully visible, 
	//// but ensure it is no longer than the size available.
	//ElementSize = std::min(MaxSize, SpaceAvailblePerLine - LabelSize);

	//// If we have less than the max size available including the label,
	//// then cut off the label to keep us at max size.
	//if (SpaceAvailblePerLine < ElementSize + LabelSize)
	//{
	//	// If we have more space available than the max size, we can show some of the label
	//	// by setting the element size equal to the max size.
	//	if (SpaceAvailblePerLine > MaxSize)
	//	{
	//		ElementSize = MaxSize;
	//	}
	//	else
	//	{
	//		// But if we have less space available than even the max size, we then
	//		// need to scale down to the space avalible. This will almost entirely
	//		// cut off the label.
	//		ElementSize = SpaceAvailblePerLine;
	//	}
	//}

	//// If the element was set to the amount of space available, it might be lower than the minimum
	//// element size, so we need to clamp it to the min size.
	//ElementSize = std::max(ElementSize, MinSize);

	return ElementSize;
}

float UiSize::GetMin() const
{
	if (std::holds_alternative<std::string>(MinWidth))
	{
		return ImGui::CalcTextSize(std::get<std::string>(MinWidth).c_str()).x + GetPaddingSpace();
	}
	else
	{
		return std::get<float>(MinWidth) + GetPaddingSpace();
	}
}

float UiSize::GetMax() const
{
	if (std::holds_alternative<std::string>(MaxWidth))
	{
		return ImGui::CalcTextSize(std::get<std::string>(MaxWidth).c_str()).x - GetPaddingSpace();
	}
	else
	{
		return std::get<float>(MaxWidth) - GetPaddingSpace();
	}
}

float UiSize::GetPaddingSpace() const
{
	return PaddingSpace;
}

UiSizeRule UiSize::GetSizeRule() const
{
	return SizeRule;
}
