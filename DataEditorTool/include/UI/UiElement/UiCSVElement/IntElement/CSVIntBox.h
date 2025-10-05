#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class IntBox;

class CSVIntBox : public UiBasicCSVElement<int32_t>
{
public:

	CSVIntBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const int InStepSize = 0,
		const int InFastStepSize = 0
	);

	CSVIntBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const int InStepSize = 0,
		const int InFastStepSize = 0
	);

	virtual void Refresh() override;

	virtual void UiComponentUpdated() override;

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

	int GetIntBuffer() const;

	int GetMinValue() const;
	int GetMaxValue() const;

private:

	std::shared_ptr<IntBox> IntBoxComponent;

};