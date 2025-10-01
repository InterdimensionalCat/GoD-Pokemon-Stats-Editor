#pragma once

#include "UI/UiElement/UiSingleElement.h"

class TabCSVState;

class UiCSVElement : public UiSingleElement
{

public:

	UiCSVElement(const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

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

	/**
	 * Should this element's current row match the
	 * current row of its Tab's TabCSVState?
	 * 
	 * Row syncing may not be desired for sections
	 * that display multiple rows of a CSV file.
	 */
	bool bShouldSyncRowToCSVState = true;
};
