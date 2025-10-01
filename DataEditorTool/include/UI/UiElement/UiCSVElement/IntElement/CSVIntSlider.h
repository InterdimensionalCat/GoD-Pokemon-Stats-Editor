#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class IntSlider;

class CSVIntSlider : public UiBasicCSVElement<int32_t>
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

	virtual void UiComponentUpdated() override;

	/** Set the Min/Max value bounds. */
	void SetBounds(const int NewMinValue, const int NewMaxValue);

	int GetMinValue() const;
	int GetMaxValue() const;

private:

	std::shared_ptr<IntSlider> IntSliderComponent;

};