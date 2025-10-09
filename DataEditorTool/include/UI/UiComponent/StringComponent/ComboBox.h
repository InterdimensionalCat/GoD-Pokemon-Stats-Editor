/*****************************************************************//**
 * \file   ComboBox.h
 * \brief  UiComponent that displays a combo box with a list of entries to select from.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiComponent/UiComponent.h"

/**
 * \brief  UiComponent that displays a combo box with a list of entries to select from.
 */
class ComboBox : public UiComponent
{

public:

	/**
	 * Construct a ComboBox with the supplied name and parent element, and no entries.
	 * This ComboBox will have a label by default.
	 * 
	 * \param InName Name of this ComboBox.
	 * \param InParent Parent UiSingleElement of this ComboBox.
	 * 
	 * \note The ComboBox will need to have its entries list set to function properly.
	 */
	ComboBox
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	/**
	 * Construct a ComboBox with the supplied name, parent element,
	 * and entries list.
	 * This ComboBox will have a label by default.
	 * 
	 * \param InName Name of this ComboBox.
	 * \param InParent Parent UiSingleElement of this ComboBox.
	 * \param InEntriesList The list of entries to display in the combo box.
	 */
	ComboBox
	(
		const std::string& InName,
		UiSingleElement* InParent,
		std::vector<std::string> InEntriesList
	);

	/**
	 * Display this ComboBox using ImGui::Combo.
	 * 
	 * TODO: If the entries list is empty, a disabled combo box will be displayed.
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
	 * Set the list of entries to display in the combo box.
	 * This will also update the minimum content size to fit the largest entry.
	 * 
	 * TODO: If the selected entry is out of bounds after setting the new entries list,
	 * it should be clamped to the valid range.
	 * 
	 * \param InEntriesList The new list of entries to display in the combo box.
	 */
	void SetEntriesList(const std::vector<std::string>& InEntriesList);

	/**
	 * Get the index of the currently selected entry in the ComboBox.
	 * 
	 * \return The index of the currently selected entry in the ComboBox.
	 */
	uint32_t GetSelectedEntry() const;

	/**
	 * Get the list of entries in the ComboBox.
	 * 
	 * \return The list of entries in the ComboBox.
	 */
	const std::vector<std::string>& GetEntriesList() const;

	/**
	 * Calculate the internal space required by this ComboBox,
	 * excluding label size.
	 * 
	 * This will be the width of the largest entry in the entries list,
	 * plus some padding for the combo box arrow and text filter.
	 * 
	 * \return The internal space required by this ComboBox, excluding label size.
	 */
	virtual float CalculateInternalSpace() const override;

private:

	/**
	 * Set the min size for this UiComponent to
	 * be big enough to fully display the largest entry.
	 */
	void SetMinContentSizeFromEntriesList();

	/* The list of entries to display in the combo box. */
	std::vector<std::string> EntriesList;
	
	/* The index of the currently selected entry in the combo box. */
	uint32_t SelectedEntry = 0;

	/* Text filter to filter the entries list. */
	ImGuiTextFilter EntryFilter;
};