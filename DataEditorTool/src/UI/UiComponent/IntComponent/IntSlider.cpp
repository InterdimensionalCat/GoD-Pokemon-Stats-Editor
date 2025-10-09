#include "include.h"
#include "UI/UiComponent/IntComponent/IntSlider.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"

IntSlider::IntSlider
(
	const std::string& InName,
	UiSingleElement* InParent,
	const int InMinValue,
	const int InMaxValue
) :
	UiComponent(InName, InParent),
	MinValue(InMinValue),
	MaxValue(InMaxValue)
{

}

void IntSlider::DisplayComponent()
{
	// Show an int entry box.
	auto SliderFlags = ImGuiSliderFlags_AlwaysClamp
		| ImGuiSliderFlags_ClampOnInput;

	ImGui::SliderInt(GetName().c_str(), &IntBuffer, MinValue, MaxValue, "%d", SliderFlags);

	if (ImGui::IsItemDeactivated())
	{
		// Clamp the buffer to the Min/Max of this box
		IntBuffer = std::clamp(IntBuffer, MinValue, MaxValue);

		// Notify the ParentElement that the value changed.
		ComponentUpdated();
	}
}

void IntSlider::SetBounds(const int NewMinValue, const int NewMaxValue)
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

void IntSlider::SetSliderMinSize(const float InMinSize)
{
	// Sliders don't have a content string they need to be big enough to display,
	// so we set a min size in pixels using the ExtraSpace parameter.
	ComponentSize->SetMin(UiSizeBound("", CalculateInternalSpace(), InMinSize));
}

void IntSlider::SetIntBuffer(const int NewBufferValue)
{
	IntBuffer = NewBufferValue;
}

int IntSlider::GetIntBuffer() const
{
	return IntBuffer;
}


int IntSlider::GetMinValue() const
{
	return MinValue;
}

int IntSlider::GetMaxValue() const
{
	return MaxValue;
}

float IntSlider::CalculateInternalSpace() const
{
	// IntSliders are one of the only UiComponents that
	// do not have frame padding either side. They have
	// no internal space requirements at all.
	return 0.f;
}