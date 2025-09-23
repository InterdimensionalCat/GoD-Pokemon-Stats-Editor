#include "include.h"
#include "UI/BasicUiElements/IntBox.h"

IntBox::IntBox
(
	const std::string& InName,
	UiSection* InParent,
	const int InStepSize,
	const int InFastStepSize
) :
	UiElement(InName, InParent),
	StepSize(InStepSize),
	FastStepSize(InFastStepSize),
	MinValue(std::numeric_limits<int>().min()),
	MaxValue(std::numeric_limits<int>().max())
{

}

void IntBox::Tick()
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
	GetSize().SetMinFromString(MinNumString);

	// If the step buttons are enabled, we need to update the
	// Padding on this size to include the size of both step buttons
	auto& Style = ImGui::GetStyle();
	if (StepSize != 0)
	{
		// Calculate the size of one step button

		// Each button's width is equal to the size of one character of text
		// plus frame padding on either side.
		const float ButtonText = ImGui::CalcTextSize("+").x;
		const float ButtonFramePadding = Style.FramePadding.x * 2;
		const float ButtonWidth = ButtonText + ButtonFramePadding;

		// Additionally, the int box entry also has frame padding on either side,
		// so we need to include that in the padding space as well.
		const float IntBoxPadding = Style.FramePadding.x * 2 + Style.ItemInnerSpacing.x;

		// There are 2 buttons, so we add the ButtonWidth padding twice
		GetSize().SetPaddingSpace((ButtonWidth * 2) + IntBoxPadding);
	}
	else
	{
		GetSize().SetPaddingSpace(Style.FramePadding.x * 2);
	}
}

void IntBox::SetElementMaxSize(const uint32_t MaxNumDigits)
{
	std::string MaxNumString = std::string(MaxNumDigits, '9');
	GetSize().SetMaxFromString(MaxNumString);

	// If the step buttons are enabled, we need to update the
	// Padding on this size to include the size of both step buttons
	if (StepSize != 0)
	{
		// Calculate the size of one step button
		auto& Style = ImGui::GetStyle();

		// Each button's width is equal to the size of one character of text
		// plus frame padding on either side.
		const float ButtonText = ImGui::CalcTextSize("+").x;
		const float ButtonFramePadding = Style.FramePadding.x * 2;
		const float ButtonWidth = ButtonText + ButtonFramePadding;

		// Additionally, the int box entry also has frame padding on either side,
		// so we need to include that in the padding space as well.
		const float IntBoxPadding = Style.FramePadding.x * 2;

		// There are 2 buttons, so we add the ButtonWidth padding twice
		GetSize().SetPaddingSpace((ButtonWidth * 2) + IntBoxPadding);
	}
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
}

int IntBox::GetMinValue() const
{
	return MinValue;
}

int IntBox::GetMaxValue() const
{
	return MaxValue;
}