#pragma once

#include "UI/UiComponent/UiComponent.h"

class UiElement;

class IntSlider : public UiComponent
{
public:

	IntSlider
	(
		const std::string& InName,
		UiSingleElement* InParent,
		const int InMinValue = 0,
		const int InMaxValue = 3
	);

	virtual void DisplayComponent() override;

	/** Set the Min/Max value bounds. */
	void SetBounds(const int NewMinValue, const int NewMaxValue);

	void SetSliderMinSize(const float InMinSize);

	void SetIntBuffer(const int NewBufferValue);

	int GetIntBuffer() const;

	int GetMinValue() const;
	int GetMaxValue() const;

	virtual float CalculateInternalSpace() const override;

private:

	int MinValue;

	int MaxValue;

	int IntBuffer = 0;
};