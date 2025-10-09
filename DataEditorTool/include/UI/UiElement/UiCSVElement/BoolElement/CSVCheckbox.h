/*****************************************************************//**
 * \file   CSVCheckbox.h
 * \brief  UiBasicCSVElement that displays and edits a bool value from a specified column in a CSV file.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class CheckBox;

/**
 * \brief   UiBasicCSVElement that displays and edits a bool value from a specified column in a CSV file.
 * 
 * Contains a Checkbox component and a ManagedValue
 * that serves as a buffer between the CheckBox and the CSV file.
 * When this managed value is updated, the corresponding value in the CSV file
 * is updated via a ModifySingleCSVValue command pushed to the tab's command queue.
 */
class CSVCheckbox : public UiBasicCSVElement<bool>
{

public:

	/** 
	 * Construct a CSVCheckbox with the supplied name, parent section,
	 * CSV file name, and column name.
	 *
	 * \param InName Name of this CSVCheckbox.
	 * \param InParent Parent section of this CSVCheckbox.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to display data from.
	 */
	CSVCheckbox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

	/**
	 * Construct a CSVCheckbox with the supplied name, parent section,
	 * and CSV file name. The column name will be set to the same value as the name.
	 *
	 * \param InName Name of this CSVCheckbox.
	 * \param InParent Parent section of this CSVCheckbox.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 */
	CSVCheckbox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName
	);

	/**
	 * Refresh references to the underlying data this UiObject manages.
	 * 
	 * This will refresh the bool buffer of the CheckBox component
	 * in addition to updating the managed value from the CSV file.
	 */
	virtual void Refresh() override;

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 * 
	 * This implementation updates the managed value from the
	 * CheckBox component's bool buffer.
	 */
	virtual void UiComponentUpdated() override;

private:

	/* The CheckBox component managed by this CSVCheckbox. */
	std::shared_ptr<CheckBox> CheckBoxComponent;
};
