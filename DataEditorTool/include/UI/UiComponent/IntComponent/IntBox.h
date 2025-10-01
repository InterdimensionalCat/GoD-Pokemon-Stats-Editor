#pragma once
#include "UI/UiComponent/UiComponent.h"

class IntBox : public UiComponent
{
public:

	IntBox
	(
		const std::string& InName,
		UiSingleElement* InParent,
		const int InStepSize = 0,
		const int InFastStepSize = 0
	);

	virtual void DisplayElement() override;

	/**
	 * Set this element's min required size by passing in the
	 * number of digits this should be able to show.
	 * Will factor in step counter size if enabled.
	 */
	void SetElementMinSize(const uint32_t MinNumDigits);

	/**
	 * Set this element's max required size by passing in the
	 * number of digits this should be able to show.
	 * Will factor in step counter size if enabled.
	 */
	void SetElementMaxSize(const uint32_t MaxNumDigits);

	/** Set the Min/Max value bounds. */
	void SetBounds(const int NewMinValue, const int NewMaxValue);

	void SetIntBuffer(const int NewBufferValue);

	int GetIntBuffer() const;

	int GetMinValue() const;
	int GetMaxValue() const;

	virtual float CalculateInternalSpace() const override;

private:

	const int StepSize;

	const int FastStepSize;

	int MinValue;

	int MaxValue;

	int IntBuffer = -1;
};
