/*****************************************************************//**
 * \file   CSVRadioButton.h
 * \brief  UiBasicCSVElement that displays and edits a bool value from a specified column in a CSV file.
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class RadioButton;

/**
 * \brief   UiBasicCSVElement that displays and edits a bool value from a specified column in a CSV file.
 *
 * Contains a RadioButton component and a ManagedValue
 * that serves as a buffer between the RadioButton and the CSV file.
 * When this managed value is updated, the corresponding value in the CSV file
 * is updated via a ModifySingleCSVValue command pushed to the tab's command queue.
 */
class CSVRadioButton : public UiBasicCSVElement<bool>
{

public:

	/**
	 * Construct a CSVRadioButton with the supplied name, parent section,
	 * CSV file name, and column name.
	 *
	 * \param InName Name of this CSVRadioButton.
	 * \param InParent Parent section of this CSVRadioButton.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to display data from.
	 */
	CSVRadioButton
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

	/**
	 * Construct a CSVRadioButton with the supplied name, parent section,
	 * and CSV file name. The column name will be set to the same value as the name.
	 *
	 * \param InName Name of this CSVRadioButton.
	 * \param InParent Parent section of this CSVRadioButton.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 */
	CSVRadioButton
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName
	);

	/**
	 * Refresh references to the underlying data this UiObject manages.
	 *
	 * This will refresh the bool buffer of the RadioButton component
	 * in addition to updating the managed value from the CSV file.
	 */
	virtual void Refresh() override;

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * This implementation updates the managed value from the
	 * RadioButton component's bool buffer.
	 */
	virtual void UiComponentUpdated() override;

private:

	/* The RadioButton component managed by this CSVRadioButton. */
	std::shared_ptr<RadioButton> RadioButtonComponent;
};
