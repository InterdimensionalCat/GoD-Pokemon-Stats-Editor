#pragma once

#include "UI/UiComponent/UiComponent.h"

class ComboBox : public UiComponent
{

public:

	ComboBox
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	ComboBox
	(
		const std::string& InName,
		UiSingleElement* InParent,
		std::vector<std::string> InEntriesList
	);

	virtual void DisplayComponent() override;

	void SetSelectedEntry(const uint32_t NewSelectedEntry);

	void SetEntriesList(const std::vector<std::string>& InEntriesList);

	uint32_t GetSelectedEntry() const;

	const std::vector<std::string>& GetEntriesList() const;

	virtual float CalculateInternalSpace() const override;

private:

	/**
	 * Set the min size for this UiComponent to
	 * be big enough to fully display the largest entry.
	 */
	void SetMinContentSizeFromEntriesList();

	std::vector<std::string> EntriesList;

	uint32_t SelectedEntry = 0;

	ImGuiTextFilter EntryFilter;
};