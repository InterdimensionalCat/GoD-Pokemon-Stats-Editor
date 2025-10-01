#include "include.h"
#include "UI/UiComponent/StringComponent/ComboBox.h"
#include "UI/UiElement/UiSingleElement.h"

ComboBox::ComboBox
(
	const std::string& InName,
	UiSingleElement* InParent
) :
	UiComponent(InName, InParent),
	EntriesList()
{

}

ComboBox::ComboBox
(
	const std::string& InName,
	UiSingleElement* InParent,
	std::vector<std::string> InEntriesList
) :
	UiComponent(InName, InParent),
	EntriesList()
{
	SetEntriesList(InEntriesList);
}

void ComboBox::DisplayComponent()
{
	auto& Style = ImGui::GetStyle();

	// Show a ListBox with every entry
	auto PopupItemWidth = ImGui::CalcItemWidth();

	if (ImGui::BeginCombo(GetName().c_str(), EntriesList.at(SelectedEntry).c_str()))
	{
		// Show a text box that acts as a filter for the EntriesList.
		ImGuiInputTextFlags FilterBoxFlags = 0;

		// Force input to be uppercase 
		FilterBoxFlags |= ImGuiInputTextFlags_CharsUppercase;

		// Filter box name is "##{ElementName}-FilterBox"
		const std::string FilterBoxName = std::format("{}-{}", GetInvisibleName(), "FilterBox");

		// Display a text box that modifies the EntryFilter's input buffer.
		const bool FilterBoxActive = ImGui::InputTextEx
		(
			FilterBoxName.c_str(),
			"Search",
			EntryFilter.InputBuf,
			IM_ARRAYSIZE(EntryFilter.InputBuf),
			ImVec2(PopupItemWidth, 0),
			FilterBoxFlags
		);

		// Rebuild the filter if we typed input into
		// the above text box
		if (FilterBoxActive)
		{
			EntryFilter.Build();
		}

		// Give this text box keyboard focus when this window appears,
		// This will focus the text box every time the combo box popup appears
		if (ImGui::IsWindowAppearing())
		{
			ImGui::SetKeyboardFocusHere(-1);
		}

		// If we deactivate the text box with results passing the filter,
		// Automatically set the selected entry to the topmost result.
		if (ImGui::IsItemDeactivatedAfterEdit())
		{
			for (uint32_t Index = 0; Index < EntriesList.size(); Index++)
			{
				const std::string EntryValue = EntriesList.at(Index);

				if (EntryFilter.PassFilter(EntryValue.c_str()))
				{
					SetSelectedEntry(Index);
					ImGui::CloseCurrentPopup();
					EntryFilter.Clear();
					break;
				}
			}
		}

		for (uint32_t Index = 0; Index < EntriesList.size(); Index++)
		{
			const std::string EntryValue = EntriesList.at(Index);
			const bool EntryIsSelected = SelectedEntry == Index;

			// Set the name of each selectable to "{EntryName}{InvisListBoxName}"
			const std::string SelectableNameString = std::format("{}{}", EntryValue, GetInvisibleName());

			// If this entry passes the filter, show a selectable for it.
			if (EntryFilter.PassFilter(EntryValue.c_str()))
			{
				if (ImGui::Selectable(SelectableNameString.c_str(), EntryIsSelected))
				{
					// Update the selected entry if this
					// index has become newly selected
					SetSelectedEntry(Index);
				}
			}
		}

		ImGui::EndCombo();
	}
	else
	{
		// We don't want the text in the filter box to persist after an
		// entry is selected, so clear it whenever this combo box is inactive
		EntryFilter.Clear();
	}
}

void ComboBox::SetSelectedEntry(const uint32_t NewSelectedEntry)
{
	// Only update the selected entry if
	// The new entry does not match it.
	if (SelectedEntry != NewSelectedEntry)
	{
		SelectedEntry = NewSelectedEntry;
		ComponentUpdated();
	}
}

void ComboBox::SetEntriesList(const std::vector<std::string>& InEntriesList)
{
	EntriesList = InEntriesList;
	SetMinContentSizeFromEntriesList();
}

uint32_t ComboBox::GetSelectedEntry() const
{
	return SelectedEntry;
}

const std::vector<std::string>& ComboBox::GetEntriesList() const
{
	return EntriesList;
}

float ComboBox::CalculateInternalSpace() const
{
	float InternalSize = 0.f;
	auto& Style = ImGui::GetStyle();

	// There is frame padding on either side of the box
	// text entry.
	InternalSize += Style.FramePadding.x * 2;

	// Even though it doesn't look like it, there is also 
	// ItemInnerSpacing space between the text box and the dropdown button.
	InternalSize += Style.ItemInnerSpacing.x;

	// Then finally there is the size of the button,
	// the size of square buttons is always equal to ImGui::GetFrameHeight()
	InternalSize += ImGui::GetFrameHeight();

	return InternalSize;
}

void ComboBox::SetMinContentSizeFromEntriesList()
{
	// Get the longest element in the Entries list
	const auto LongestEntryItr = std::max_element(EntriesList.begin(), EntriesList.end(),
		[](const std::string& lhs, const std::string& rhs)
		{
			return lhs.length() < rhs.length();
		}
	);

	if (LongestEntryItr == EntriesList.end())
	{
		ICLogger::Warn("ComboBox CalculateMinSize called with an empty Entries List");
		return;
	}

	// Ensure the combo box is big enough to fully display the largest entry. This will also be
	// a reasonable min for the filter text entry.
	const std::string LongestEntry = *LongestEntryItr;
	SetMinContentSizeFromString(LongestEntry);
}