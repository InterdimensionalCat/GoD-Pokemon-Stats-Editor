#pragma once

#include "UI/BasicUiElements/BasicUiElement.h"

/**
 * TODO: a better system for elements/element sizing:
 * problems: we need both CSV modifying and regular elements,
 * we need to allow for mult element objects and elements
 * on the same line, we need elements of the same type that
 * manage different underlying data types (int combo box vs string
 * combo box).
 * 
 * Potential solution: seperate the ui functionality/buffers
 * into UiComponent classes, then each implementation interacts
 * with the buffer and can convert it to whatever it needs
 */

class CSVComboBox : public BasicUiElement<std::string>
{

public:

	CSVComboBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	CSVComboBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	virtual void Refresh() override;

	virtual void Tick() override;

	uint32_t GetSelectedEntry() const;

private:

	void SetSelectedEntry(const uint32_t NewSelectedEntry);

	/**
	 * Sets the min size for this Entry Selector.
	 * The min size will always be just big enough
	 * to display the largest entry.
	 */
	void CalculateMinSize();

	std::string EntriesListCSVFileName;

	std::string EntriesListColumnName;

	std::vector<std::string> EntriesList;

	uint32_t SelectedEntry = 0;

	ImGuiTextFilter EntryFilter;
};
