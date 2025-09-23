#pragma once

#include "UI/UiElement.h"

class TabCSVState;

class UiCSVElement : public UiElement
{

public:

	UiCSVElement(const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

	/** TODO: come up with a better system for setting the current row */
	// Idea: UiTab contains info about the current row for single row tabs,
	// for tabs with multi row ui elements, it calculates the correct row
	// for each element during Refresh.
	// Idea 2: Tabs contain a CSV state object. This stores needed state
	// For any CSV files that tab might edit (Just pokemon stats for the
	// pokemon stats tab, but might need Shadow pokemon and trainer data
	// for the trainer tab). This contains current row information, as well
	// as events for when a CSV file is modified or when the current row 
	// changes. The CSV state object is passed in to refresh and each
	// element can set info about it (like its current row) from the
	// CSV state object
	// The UiTab is in charge of updating the current row state of
	// each CSV file it needs
	// 
	// Separate update row and update value for ui elements
	// Some Ui sections might override the default behavior and not use 
	// CSV file state. For example a section that just lists every
	// row for a column would not need info from the current CSV state
	void SetCurrentRow(const int32_t NewCurrentRow);
	void SetShouldSyncRowToCSVState(const bool bShouldSync);

	std::string GetCSVFileName() const;
	std::string GetColumnName() const;
	int32_t GetCurrentRow() const;
	bool ShouldSyncRowToCSVState() const;

protected:

	std::shared_ptr<TabCSVState> GetTabState();

private:

	std::shared_ptr<TabCSVState> TabState;

	const std::string CSVFileName;

	const std::string ColumnName;

	int32_t CurrentRow = 0;

	bool bShouldSyncRowToCSVState = true;
};
