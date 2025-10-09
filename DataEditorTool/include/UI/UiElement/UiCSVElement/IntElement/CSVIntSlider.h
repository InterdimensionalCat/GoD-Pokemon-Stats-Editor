/*****************************************************************//**
 * \file   CSVIntSlider.h
 * \brief  UiCSVElement that displays and edits an integer value from a specified column in a CSV file,
 * but does so using an IntSlider component rather than an IntBox component.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class IntSlider;

/**
 * \brief  UiCSVElement that displays and edits an integer value from a specified column in a CSV file,
 * but does so using an IntSlider component rather than an IntBox component.
 * 
 * Contains a ManagedValue of type int32_t
 * that serves as a buffer between the UI component and the CSV file.
 * When this managed value is updated, the corresponding value in the CSV file
 * is updated via a ModifySingleCSVValue command pushed to the tab's command queue.
 */
class CSVIntSlider : public UiBasicCSVElement<int32_t>
{
public:

	/**
	 * Construct a CSVIntSlider with the supplied name, parent section, CSV file name, and column name.
	 * 
	 * \param InName Name of this CSVIntSlider.
	 * \param InParent Parent section of this CSVIntSlider.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to display data from.
	 * \param InMinValue The minimum value for the IntSlider. Default is 0.
	 * \param InMaxValue The maximum value for the IntSlider. Default is 3.
	 */
	CSVIntSlider
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const int InMinValue = 0,
		const int InMaxValue = 3
	);

	/**
	 * Construct a CSVIntSlider with the supplied name, parent section, and CSV file name.
	 * The column name will be set to the same value as the name.
	 * 
	 * \param InName Name of this CSVIntSlider.
	 * \param InParent Parent section of this CSVIntSlider.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InMinValue The minimum value for the IntSlider. Default is 0.
	 * \param InMaxValue The maximum value for the IntSlider. Default is 3.
	 */
	CSVIntSlider
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const int InMinValue = 0,
		const int InMaxValue = 3
	);

	/**
	 * Refresh references to the underlying data this UiObject manages.
	 * 
	 * This will refresh the int buffer of the IntSlider component
	 * in addition to updating the managed value from the CSV file.
	 */
	virtual void Refresh() override;

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * This implementation updates the managed value from the
	 * IntSlider component's int buffer.
	 */
	virtual void UiComponentUpdated() override;

	/**
	 * Set the Min/Max value bounds.
	 *
	 * \param NewMinValue The new minimum value for the IntSlider.
	 * \param NewMaxValue The new maximum value for the IntSlider.
	 */
	void SetBounds(const int NewMinValue, const int NewMaxValue);

	/**
	 * Get the minimum value for the IntSlider.
	 * 
	 * \return The minimum value for the IntSlider.
	 */
	int GetMinValue() const;

	/**
	 * Get the maximum value for the IntSlider.
	 * 
	 * \return The maximum value for the IntSlider.
	 */
	int GetMaxValue() const;

private:

	/* The IntSlider component used to display and edit the integer value. */
	std::shared_ptr<IntSlider> IntSliderComponent;

};