#include "include.h"
#include "UI/BasicUiElements/IntHexStringBox.h"

#include "CSV/StringTypes/IntHexParenthValue.h"

IntHexStringBox::IntHexStringBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName,
	const int InStepSize,
	const int InFastStepSize
) :
	BasicUiElement<std::string>(InName, InParent, InCSVFileName, InColumnName),
	StepSize(InStepSize),
	FastStepSize(InFastStepSize),
	MinValue(std::numeric_limits<int>().min()),
	MaxValue(std::numeric_limits<int>().max())
{
	//GetSize().SetMaxFromStringLength(25);
	//GetSize().SetMinFromStringLength(3);
}

IntHexStringBox::IntHexStringBox
(
	const std::string& InName, 
	UiSection* InParent, 
	const std::string& InCSVFileName, 
	const int InStepSize, 
	const int InFastStepSize
) :
	IntHexStringBox(InName, InParent, InCSVFileName, InName, InStepSize, InFastStepSize)
{

}

void IntHexStringBox::Refresh()
{
	BasicUiElement::Refresh();

	// The managed value for this UI type will be in the form
	// "{int} (0x{HEX})", for example, "31 (0x1F)". We need to
	// convert this into an int to set the buffer.
	const IntHexParenthValue IntHexString(GetManagedValue());

	IntBuffer = static_cast<int>(IntHexString.GetValueAsInt());
}

void IntHexStringBox::Tick()
{
	// Show an int entry box, this will be converted to an int + hex string when
	// sent to the CSV File
	ImGui::InputInt(GetName().c_str(), &IntBuffer, StepSize, FastStepSize);

	if (ImGui::IsItemDeactivated())
	{
		// Clamp the buffer to the Min/Max of this box
		IntBuffer = std::clamp(IntBuffer, MinValue, MaxValue);

		// Convert the buffer to the correct format and set the managed value to it.
		SetManagedValueFromBuffer();
	}
}

void IntHexStringBox::SetElementMinSize(const uint32_t MinNumDigits)
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
		GetSize().SetPaddingSpace(0.f);
	}
}

void IntHexStringBox::SetElementMaxSize(const uint32_t MaxNumDigits)
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

void IntHexStringBox::SetBounds(const int NewMinValue, const int NewMaxValue)
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

int IntHexStringBox::GetMinValue() const
{
	return MinValue;
}

int IntHexStringBox::GetMaxValue() const
{
	return MaxValue;
}

void IntHexStringBox::SetManagedValueFromBuffer()
{
	// The managed value for this UI type is in the form
	// "{int} (0x{HEX})", for example, "31 (0x1F)". We need to
	// convert the buffer to this form before setting it.
	const IntHexParenthValue IntHexString(static_cast<int32_t>(IntBuffer));
	SetManagedValue(IntHexString.GetParenthValueString());
}