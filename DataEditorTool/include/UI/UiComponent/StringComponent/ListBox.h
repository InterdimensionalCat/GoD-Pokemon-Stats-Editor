/*****************************************************************//**
 * \file   ListBox.h
 * \brief  UiComponent that displays a list box with a list of entries to select from.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiComponent/UiComponent.h"

/**
 * \brief  UiComponent that displays a list box with a list of entries to select from.
 */
class ListBox : public UiComponent
{

public:

	/**
	 * Construct a ListBox with the supplied name and parent element, and no entries.
	 * This ListBox will have a label by default.
	 * 
	 * \param InName Name of this ListBox.
	 * \param InParent Parent UiSingleElement of this ListBox.
	 * 
	 * \note The ListBox will need to have its entries list set to function properly.
	 */
	ListBox
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	/**
	 * Construct a ListBox with the supplied name, parent element,
	 * and entries list. This ListBox will have a label by default.
	 * 
	 * \param InName Name of this ListBox.
	 * \param InParent Parent UiSingleElement of this ListBox.
	 * \param InEntriesList The list of entries to display in the list box.
	 */
	ListBox
	(
		const std::string& InName,
		UiSingleElement* InParent,
		std::vector<std::string> InEntriesList
	);

	/**
	 * Display this ListBox using ImGui::ListBox.
	 * 
	 * TODO: If the entries list is empty, a disabled list box will be displayed.
	 * If the selected entry is out of bounds, it will be clamped to the valid range.
	 * The entries list can be filtered using a text filter.
	 */
	virtual void DisplayComponent() override;

	/**
	 * Set the selected entry by index.
	 * TODO: If the index is out of bounds, it will be clamped to the valid range.
	 * 
	 * \param NewSelectedEntry The index of the new selected entry.
	 */
	void SetSelectedEntry(const uint32_t NewSelectedEntry);

	/**
	 * Set the list of entries to display in the list box.
	 * 
	 * \param InEntriesList The new list of entries to display in the list box.
	 */
	void SetEntriesList(const std::vector<std::string>& InEntriesList);

	/**
	 * Get the index of the currently selected entry.
	 * 
	 * \return The index of the currently selected entry.
	 */
	uint32_t GetSelectedEntry() const;

	/**
	 * Calculate the internal space required by this ListBox,
	 * excluding label size.
	 * 
	 * \return The internal space required by this ListBox, excluding label size.
	 */
	virtual float CalculateInternalSpace() const override;

private:

	/**
	 * Set the min size for this UiComponent to
	 * be big enough to fully display the largest entry.
	 */
	void SetMinContentSizeFromEntriesList();

	/**
	 * If the user types while the window containing
	 * this ListBox is focused, activate the filter 
	 * text box so they can filter the entries list.
	 */
	void ActivateFilterTextBoxIfUserTypesInWindow();

	/* The list of entries to display in the list box. */
	std::vector<std::string> EntriesList;

	/* The index of the currently selected entry in the list box. */
	uint32_t SelectedEntry = 0;

	/* Text filter to filter the entries list. */
	ImGuiTextFilter EntryFilter;

	/**
	 * Space elements out a bit more vertically in the
	 * list box so entries don't look super cramped.
	 */
	const float EntriesListExtraVerticalSpacing = 2.f;
};