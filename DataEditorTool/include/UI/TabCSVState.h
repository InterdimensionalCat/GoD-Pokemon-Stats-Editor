#pragma once

class UiTab;
class UiCSVElement;

class TabCSVState
{

public:

	/**
	 * TODO: Allow multiple CSV files to have a current row so we can link entries from multiple
	 * CSV files together in one tab.
	 */
	TabCSVState(UiTab* InParentTab);

	void Tick();

	void RefreshTab();

	void RefreshRow();

	void AddElementToUpdate(std::shared_ptr<UiCSVElement> NewElement);

	void SetCurrentRow(const int32_t NewRowValue);

	int32_t GetCurrentRow() const;

private:

	bool bShouldRefreshTab = false;

	bool bShouldRefreshRow = false;

	/** Smart pointer not needed because we don't own this object. */
	UiTab* ParentTab;

	int32_t CurrentRow = 0;

	std::vector<std::shared_ptr<UiCSVElement>> ElementsToUpdate;
};
