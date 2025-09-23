#pragma once

#include "UI/UiCSVElement.h"

class CSVEntryRowSelector : public UiCSVElement
{

public:

	CSVEntryRowSelector
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

	virtual void Refresh() override;

	virtual void Tick() override;

private:

	void SetSelectedEntry(const uint32_t NewSelectedEntry);

	void ActivateFilterTextBoxIfUserTypesInWindow();

	/**
	 * Sets the min size for this Entry Selector.
	 * The min size will always be just big enough
	 * to display the largest entry.
	 */
	void CalculateMinSize();

	std::vector<std::string> EntriesList;

	uint32_t SelectedEntry = 0;

	ImGuiTextFilter EntryFilter;

	/**
	 * Space elements out a bit more vertically in the
	 * list box so entries don't look super cramped.
	 */
	const float EntriesListExtraVerticalSpacing = 2.f;

	// TODO: Keyboard focus should always be
	// on the text input whenever this section
	// is focused.

	// TODO: We should always scroll to an item when:
	// 1) text matching an element is committed
	// 2) text match no elements is commited,
	// in which case we select the first entry and scroll
	// to the top
	// 3) We click a selectable when a filter is active,
	// this is needed because the filter will be cleared when
	// we select the selectable
	// 4) the list box is not selected (in which case the filter is
	// reset and we shoudl scroll to the item)
};
