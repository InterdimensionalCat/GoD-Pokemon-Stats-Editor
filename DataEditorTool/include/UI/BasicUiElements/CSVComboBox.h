#pragma once

#include "UI/BasicUiElements/BasicUiElement.h"

class CSVComboBox : public BasicUiElement<std::string>
{

public:

	CSVComboBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const std::string& InColumnDatabaseCSVFileName
	);

	CSVComboBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnDatabaseCSVFileName
	);

	virtual void Refresh() override;

	virtual void Tick() override;

	void SetShouldReloadDatabaseOnRefresh(const bool ShouldReload);

private:

	void SetSelectedEntry(const uint32_t NewSelectedEntry);

	/**
	 * Sets the min size for this Entry Selector.
	 * The min size will always be just big enough
	 * to display the largest entry.
	 */
	void CalculateMinSize();

	std::string ColumnDatabaseCSVFileName;

	std::vector<std::string> EntriesList;

	uint32_t SelectedEntry = 0;

	ImGuiTextFilter EntryFilter;

	bool bShouldReloadDatabaseOnRefresh = true;
};
