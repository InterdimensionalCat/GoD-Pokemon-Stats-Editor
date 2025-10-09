/*****************************************************************//**
 * \file   CSVIntBox.h
 * \brief  UiBasicCSVElement that displays and edits an int value from a specified column in a CSV file.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class IntBox;

/**
 * \brief  UiBasicCSVElement that displays and edits an int value from a specified column in a CSV file.
 * 
 * Contains an IntBox component and a ManagedValue
 * that serves as a buffer between the IntBox and the CSV file.
 * When this managed value is updated, the corresponding value in the CSV file
 * is updated via a ModifySingleCSVValue command pushed to the tab's command queue.
 */
class CSVIntBox : public UiBasicCSVElement<int32_t>
{
public:


	/**
	 * Construct a CSVIntBox with the supplied name, 
	 * parent section, CSV file name, and column name.
	 * 
	 * \param InName Name of this CSVIntBox.
	 * \param InParent Parent section of this CSVIntBox.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to display data from.
	 * \param InStepSize The amount to increment/decrement the value by when using the step buttons.
	 * \param InFastStepSize The amount to increment/decrement the value by when using the step buttons with Shift held.
	 */
	CSVIntBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const int InStepSize = 0,
		const int InFastStepSize = 0
	);

	/**
	 * Construct a CSVIntBox with the supplied name, 
	 * parent section, and CSV file name. The column name
	 * will be set to the same value as the name.
	 * 
	 * \param InName Name of this CSVIntBox.
	 * \param InParent Parent section of this CSVIntBox.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InStepSize The amount to increment/decrement the value by when using the step buttons.
	 * \param InFastStepSize The amount to increment/decrement the value by when using the step buttons with Shift held.
	 */
	CSVIntBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const int InStepSize = 0,
		const int InFastStepSize = 0
	);

	/**
	 * Refresh references to the underlying data this UiObject manages.
	 * 
	 * This will refresh the int buffer of the IntBox component
	 * in addition to updating the managed value from the CSV file.
	 */
	virtual void Refresh() override;

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * This implementation updates the managed value from the
	 * IntBox component's int buffer.
	 */
	virtual void UiComponentUpdated() override;

	/**
	 * Set this element's min required size by passing in the
	 * number of digits this should be able to show.
	 * Will factor in step counter size if enabled.
	 * 
	 * \param MinNumDigits The minimum number of digits this element should be able to show.
	 */
	void SetElementMinSize(const uint32_t MinNumDigits);

	/**
	 * Set this element's max required size by passing in the
	 * number of digits this should be able to show.
	 * Will factor in step counter size if enabled.
	 * 
	 * \param MaxNumDigits The maximum number of digits this element should be able to show.
	 */
	void SetElementMaxSize(const uint32_t MaxNumDigits);

	/**
	 * Set the Min/Max value bounds.
	 * 
	 * \param NewMinValue The new minimum value.
	 * \param NewMaxValue The new maximum value.
	 */
	void SetBounds(const int NewMinValue, const int NewMaxValue);

	/**
	 * Get the current value in the IntBox buffer.
	 * 
	 * \return The current value in the IntBox buffer.
	 */	
	int GetIntBuffer() const;

	/**
	 * Get the current min value bound.
	 * 
	 * \return The current min value bound.
	 */
	int GetMinValue() const;

	/**
	 * Get the current max value bound.
	 * 
	 * \return The current max value bound.
	 */
	int GetMaxValue() const;

private:

	/* The IntBox component used to display and edit the int value. */
	std::shared_ptr<IntBox> IntBoxComponent;

};