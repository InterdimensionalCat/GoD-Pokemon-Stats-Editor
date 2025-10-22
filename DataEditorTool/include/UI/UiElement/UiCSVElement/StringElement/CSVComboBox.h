/*****************************************************************//**
 * \file   CSVComboBox.h
 * \brief  UiCSVElement that displays and edits a string value from a specified column in a CSV file
 * via a ComboBox. The entries in the ComboBox are populated from another specified CSV file and column.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class ComboBox;

/** 
 * \brief  UiCSVElement that displays and edits a string value from a specified column in a CSV file
 * via a ComboBox. The entries in the ComboBox are populated from another specified CSV file and column.
 */
class CSVComboBox : public UiBasicCSVElement<std::string>
{

public:

	/** 
	 * Construct a CSVComboBox with the supplied name, parent section,
	 * CSV file name, column name, entries list CSV file name, and entries list column name.
	 * 
	 * \param InName Name of this CSVComboBox.
	 * \param InParent Parent section of this CSVComboBox.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to display data from.
	 * \param InEntriesListCSVFileName The name of the CSV file to get ComboBox entries from, without the ".csv" extension.
	 * \param InEntriesListColumnName The name of the column in the entries list CSV file to get ComboBox entries from.
	 */
	CSVComboBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	/** 
	 * Construct a CSVComboBox with the supplied name, parent section,
	 * CSV file name, entries list CSV file name, and entries list column name.
	 * The column name will be set to the same value as the name.
	 * 
	 * \param InName Name of this CSVComboBox.
	 * \param InParent Parent section of this CSVComboBox.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InEntriesListCSVFileName The name of the CSV file to get ComboBox entries from, without the ".csv" extension.
	 * \param InEntriesListColumnName The name of the column in the entries list CSV file to get ComboBox entries from.
	 */
	CSVComboBox
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
	 * For a CSVComboBox, this will set the selected entry to match the found
	 * index of the managed value string in the entries list, and refresh the
	 * entries list from the entries list CSV file and column.
	 */
	virtual void Refresh() override;

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * This implementation updates the managed value from the
	 * ComboBox component's selected entry string.
	 */
	virtual void UiComponentUpdated() override;

	void SetSizeConstraintsDisabled(const bool bInDisableSizeConstraints);

	/**
	 * Get the index of the currently selected entry in the ComboBox.
	 * 
	 * \return The index of the currently selected entry in the ComboBox.
	 */
	uint32_t GetSelectedEntry() const;

protected:

	/* The ComboBox component managed by this element. */
	std::shared_ptr<ComboBox> ComboBoxComponent;

private:
	
	/**
	 * Update the entries list from the entries list CSV file and column.
	 * If the entries list CSV file or column are invalid, the entries list
	 * will be cleared.
	 */
	void UpdateEntriesList();

	/* The name of the CSV file to get ComboBox entries from, without the ".csv" extension. */
	std::string EntriesListCSVFileName;

	/* The name of the column in the entries list CSV file to get ComboBox entries from. */
	std::string EntriesListColumnName;

	bool bDisableSizeConstraints = false;
};
