/*****************************************************************//**
 * \file   UiCSVElement.h
 * \brief  UiSngleElement that displays a single value from a specified column in a CSV file.
 *
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiSingleElement.h"

class TabCSVState;

/**
 * \brief  UiSngleElement that displays single value from a specified column in a CSV file.
 *
 * This element can be linked to a TabCSVState to sync its current row
 * with the tab's current row. This is useful for creating editors
 * that display and edit data from a CSV file, where multiple elements
 * need to stay in sync with the same current row.
 *
 * If bShouldSyncRowToCSVState is false, then this element's current row
 * will be independent of the tab's current row. This is useful for
 * sections that display multiple rows of a CSV file, such as a list
 * of entries.
 */
class UiCSVElement : public UiSingleElement
{

public:

	/**
	 * Construct a UiCSVElement with the supplied name, parent section,
	 * CSV file name, and column name.
	 *
	 * \param InName Name of this UiCSVElement.
	 * \param InParent Parent section of this UiCSVElement.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to display data from.
	 */
	UiCSVElement(const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

	/**
	 * Set the current row for this element.
	 *
	 * \param NewCurrentRow The new current row for this element.
	 */
	void SetCurrentRow(const int32_t NewCurrentRow);

	/**
	 * Set whether or not this element's current row should match
	 * the current row of its Tab's TabCSVState.
	 *
	 * Row syncing may not be desired for sections
	 * that display multiple rows of a CSV file.
	 *
	 * \param bShouldSync True if this element's current row should match the tab's current row.
	 */
	void SetShouldSyncRowToCSVState(const bool bShouldSync);

	/**
	 * Get the CSV file name this element is linked to.
	 *
	 * \return The CSV file name this element is linked to.
	 */
	std::string GetCSVFileName() const;

	/**
	 * Get the column name this element is linked to.
	 *
	 * \return The column name this element is linked to.
	 */
	std::string GetColumnName() const;

	/**
	 * Get the current row for this element.
	 *
	 * \return The current row for this element.
	 */
	int32_t GetCurrentRow() const;

	/**
	 * Should this element's current row match the
	 * current row of its Tab's TabCSVState?
	 *
	 * Row syncing may not be desired for sections
	 * that display multiple rows of a CSV file.
	 *
	 * \return True if this element's current row should match the tab's current row.
	 */
	bool ShouldSyncRowToCSVState() const;

protected:

	/**
	 * Get the TabCSVState this element uses to sync its row.
	 *
	 * \return The TabCSVState this element uses to sync its row.
	 */
	std::shared_ptr<TabCSVState> GetTabState();

private:

	/* The TabCSVState this element uses to sync its row. */
	std::shared_ptr<TabCSVState> TabState;

	/* The CSV file name this element is linked to. */
	const std::string CSVFileName;

	/* The column name this element is linked to. */
	const std::string ColumnName;

	/* The current row for this element. */
	int32_t CurrentRow = 0;

	/**
	 * Should this element's current row match the
	 * current row of its Tab's TabCSVState?
	 *
	 * Row syncing may not be desired for sections
	 * that display multiple rows of a CSV file.
	 */
	bool bShouldSyncRowToCSVState = true;
};
