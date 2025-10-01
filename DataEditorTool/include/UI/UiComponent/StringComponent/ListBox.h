#pragma once

#include "UI/UiComponent/UiComponent.h"

class ListBox : public UiComponent
{

public:

	ListBox
	(
		const std::string& InName,
		UiSingleElement* InParent,
		std::vector<std::string> InEntriesList
	);

	virtual void DisplayComponent() override;

	void SetSelectedEntry(const uint32_t NewSelectedEntry);

	void SetEntriesList(const std::vector<std::string>& InEntriesList);

	uint32_t GetSelectedEntry() const;

	virtual float CalculateInternalSpace() const override;

private:

	/**
	 * Set the min size for this UiComponent to
	 * be big enough to fully display the largest entry.
	 */
	void SetMinContentSizeFromEntriesList();

	void ActivateFilterTextBoxIfUserTypesInWindow();

	std::vector<std::string> EntriesList;

	uint32_t SelectedEntry = 0;

	ImGuiTextFilter EntryFilter;

	/**
	 * Space elements out a bit more vertically in the
	 * list box so entries don't look super cramped.
	 */
	const float EntriesListExtraVerticalSpacing = 2.f;
};