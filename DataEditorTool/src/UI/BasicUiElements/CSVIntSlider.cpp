#include "include.h"
#include "UI/BasicUiElements/CSVIntSlider.h"

CSVIntSlider::CSVIntSlider
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName,
	const int InMinValue,
	const int InMaxValue
) :
	BasicUiElement<int32_t>(InName, InParent, InCSVFileName, InColumnName),
	MinValue(InMinValue),
	MaxValue(InMaxValue)
{

}

CSVIntSlider::CSVIntSlider
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const int InMinValue,
	const int InMaxValue
) :
	CSVIntSlider(InName, InParent, InCSVFileName, InName, InMinValue, InMaxValue)
{

}

void CSVIntSlider::Refresh()
{
	BasicUiElement::Refresh();
	IntBuffer = GetManagedValue();
}

void CSVIntSlider::Tick()
{
	// Show an int entry box.
	auto SliderFlags = ImGuiSliderFlags_AlwaysClamp 
		| ImGuiSliderFlags_ClampOnInput;

	ImGui::SliderInt(GetName().c_str(), &IntBuffer, MinValue, MaxValue, "%d", SliderFlags);

	if (ImGui::IsItemDeactivated())
	{
		// Clamp the buffer to the Min/Max of this box
		IntBuffer = std::clamp(IntBuffer, MinValue, MaxValue);

		// Set the managed value from the buffer.
		SetManagedValue(static_cast<int32_t>(IntBuffer));
	}
}

void CSVIntSlider::SetBounds(const int NewMinValue, const int NewMaxValue)
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

int CSVIntSlider::GetMinValue() const
{
	return MinValue;
}

int CSVIntSlider::GetMaxValue() const
{
	return MaxValue;
}