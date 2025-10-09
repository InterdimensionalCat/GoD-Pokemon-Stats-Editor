/*****************************************************************//**
 * \file   CSVRowSelector.h
 * \brief  UiCSVElement that displays and edits the selected row index from a specified CSV file
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiElement/UiCSVElement/UiCSVElement.h"

class ListBox;

/**
 * \brief  UiCSVElement that displays and edits the selected row index from a specified CSV file
 * via a ListBox. The entries in the ListBox are populated from the "Entry Name" column of the specified CSV file.
 */
class CSVRowSelector : public UiCSVElement
{


public:

	/**
	 * Construct a CSVRowSelector with the supplied name, parent section,
	 * CSV file name, and column name.
	 * 
	 * \param InName Name of this CSVRowSelector.
	 * \param InParent Parent section of this CSVRowSelector.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to display data from.
	 */
	CSVRowSelector
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

	/**
	 * Refresh references to the underlying data this CSVRowSelector manages.
	 * 
	 * For a CSVRowSelector, this just reloads the entries list from the specified CSV file.
	 */
	virtual void Refresh() override;

	/**
	 * Called whenever the ListBox component is updated.
	 * 
	 * For a CSVRowSelector, this pushes a ChangeRow command to the Tab's TabCSVState
	 * to change the current row to the selected entry in the ListBox.
	 */
	virtual void UiComponentUpdated() override;

	/**
	 * Get the currently selected entry index in the ListBox.
	 * 
	 * \return The currently selected entry index in the ListBox.
	 */
	uint32_t GetSelectedEntry() const;

private:

	/**
	 * Reload the entries list from the specified CSV file.
	 */
	void UpdateEntriesList();

	/* The ListBox component managed by this element. */
	std::shared_ptr<ListBox> ListBoxComponent;

};
