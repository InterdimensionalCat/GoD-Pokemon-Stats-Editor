/*****************************************************************//**
 * \file   CSVIntHexComboBox.h
 * \brief  UiCSVElement that displays and edits a string value from a specified column in a CSV file
 * via a ComboBox. However, the underlying data is an IntHexParenthValue representation of the selected
 * entry's parenth value.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class ComboBox;

/**
 * \brief  UiCSVElement that displays and edits a string value from a specified column in a CSV file
 * via a ComboBox. However, the underlying data is an IntHexParenthValue representation of the selected
 * entry's parenth value.
 * 
 * The entries in the ComboBox are populated from another CSV file and column,
 * where each entry in that column is expected to be a ParenthValueString.
 * 
 * This element assumes that the column it is linked to contains values
 * that can be parsed as IntHexParenthValues.
 */
class CSVIntHexComboBox : public UiBasicCSVElement<std::string>
{

public:
	
	/**
	 * Construct a CSVIntHexComboBox with the supplied name, parent section,
	 * CSV file name, column name, entries list CSV file name, and entries list column name.
	 * 
	 * \param InName Name of this CSVIntHexComboBox.
	 * \param InParent Parent section of this CSVIntHexComboBox.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to display data from.
	 * \param InEntriesListCSVFileName The name of the CSV file to pull entries from, without the ".csv" extension.
	 * \param InEntriesListColumnName The name of the column in the entries list CSV file to pull entries from.
	 */
	CSVIntHexComboBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	/**
	 * Construct a CSVIntHexComboBox with the supplied name, parent section,
	 * CSV file name, entries list CSV file name, and entries list column name.
	 * The column name will be set to the same value as the name.
	 * 
	 * \param InName Name of this CSVIntHexComboBox.
	 * \param InParent Parent section of this CSVIntHexComboBox.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InEntriesListCSVFileName The name of the CSV file to pull entries from, without the ".csv" extension.
	 * \param InEntriesListColumnName The name of the column in the entries list CSV file to pull entries from.
	 */
	CSVIntHexComboBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	/** 
	 * Refresh references to the underlying data this UiObject manages.
	 * 
	 * For a CSVIntHexComboBox, this will set the selected entry to match the parenth value
	 * of the string of the managed value string, and refresh the
	 * entries list from the entries list CSV file and column.
	 */
	virtual void Refresh() override;

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * This implementation updates the managed value from the
	 * selected entry's parenth value string.
	 */
	virtual void UiComponentUpdated() override;

	/**
	 * Get the index of the currently selected entry in the ComboBox.
	 * 
	 * \return The index of the currently selected entry in the ComboBox.
	 */
	uint32_t GetSelectedEntry() const;

protected:

	/**
	 * Reload the entries list from the specified CSV file and column.
	 */
	virtual void UpdateEntriesList();

	/* The ComboBox component managed by this element. */
	std::shared_ptr<ComboBox> ComboBoxComponent;

	/* The name of the CSV file to get ComboBox entries from, without the ".csv" extension. */
	std::string EntriesListCSVFileName;

	/* The name of the column in the entries list CSV file to get ComboBox entries from. */
	std::string EntriesListColumnName;
};
