#pragma once

#include "UI/BasicUiElements/BasicUiElement.h"

class CSVIntSlider : public BasicUiElement<int32_t>
{
public:

	CSVIntSlider
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const int InMinValue = 0,
		const int InMaxValue = 3
	);

	CSVIntSlider
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const int InMinValue = 0,
		const int InMaxValue = 3
	);

	virtual void Refresh() override;

	virtual void Tick() override;

	/** Set the Min/Max value bounds. */
	void SetBounds(const int NewMinValue, const int NewMaxValue);

	int GetMinValue() const;
	int GetMaxValue() const;

private:

	int MinValue;

	int MaxValue;

	int IntBuffer = 0;
};