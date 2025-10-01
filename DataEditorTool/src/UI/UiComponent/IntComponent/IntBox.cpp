#include "include.h"
#include "UI/UiComponent/IntComponent/IntBox.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"

IntBox::IntBox
(
	const std::string& InName,
	UiSingleElement* InParent,
	const int InStepSize,
	const int InFastStepSize
) :
	UiComponent(InName, InParent),
	StepSize(InStepSize),
	FastStepSize(InFastStepSize),
	MinValue(std::numeric_limits<int>().min()),
	MaxValue(std::numeric_limits<int>().max())
{

}

void IntBox::DisplayElement()
{
	// Show an int entry box.
	ImGui::InputInt(GetName().c_str(), &IntBuffer, StepSize, FastStepSize);

	if (ImGui::IsItemDeactivated())
	{
		// Clamp the buffer to the Min/Max of this box
		SetIntBuffer(std::clamp(IntBuffer, MinValue, MaxValue));
	}
}

void IntBox::SetElementMinSize(const uint32_t MinNumDigits)
{
	std::string MinNumString = std::string(MinNumDigits, '9');
	SetMinContentSizeFromString(MinNumString);
}

void IntBox::SetElementMaxSize(const uint32_t MaxNumDigits)
{
	std::string MaxNumString = std::string(MaxNumDigits, '9');
	SetMaxContentSizeFromString(MaxNumString);
}

void IntBox::SetBounds(const int NewMinValue, const int NewMaxValue)
{
	// Ensure that the Min/Max value are not outside the numeric limit range.
	int ClampedMinValue = std::clamp(
		NewMinValue,
		std::numeric_limits<int>().min(),
		std::numeric_limits<int>().max()
	);

	int ClampedMaxValue = std::clamp(
		NewMaxValue,
		std::numeric_limits<int>().min(),
		std::numeric_limits<int>().max()
	);

	// Ensure that the max value is never less than the min value.
	// If it is, then set it equal to the min value.
	// This is why both bounds must be set at the same time, as
	// If the max is set before the min it can lead to unintuitive bugs.
	if (ClampedMaxValue < ClampedMinValue)
	{
		ClampedMaxValue = ClampedMinValue;
	}

	MinValue = ClampedMinValue;
	MaxValue = ClampedMaxValue;
}

void IntBox::SetIntBuffer(const int NewBufferValue)
{
	IntBuffer = NewBufferValue;
	ComponentUpdated();
}

int IntBox::GetIntBuffer() const
{
	return IntBuffer;
}

int IntBox::GetMinValue() const
{
	return MinValue;
}

int IntBox::GetMaxValue() const
{
	return MaxValue;
}

float IntBox::CalculateInternalSpace() const
{
	float InternalSize = 0.f;
	auto& Style = ImGui::GetStyle();

	// 2 cases: either step size buttons are enabled or they are not.
	if (StepSize == 0)
	{
		// Case 1, no step buttons.
		// In this case, there is frame padding on either side of the box
		// text entry.
		InternalSize += Style.FramePadding.x * 2;
	}
	else
	{
		// Case 2, step buttons are enabled.
		// In this case, there is still frame padding on 
		// either side of the box, but there is also at least
		// 2 ItemInnerSpacing spaces between the two step buttons.
		// The size of each button (which is included in the internal size)
		// Is equal to the ImGui frame height, as it uses the text size +
		// the FramePadding.y * 2.f to determine its square width and height.
		InternalSize += Style.FramePadding.x * 2;

		InternalSize += Style.ItemInnerSpacing.x * 2;

		InternalSize += ImGui::GetFrameHeight() * 2.f;
	}

	return InternalSize;
}