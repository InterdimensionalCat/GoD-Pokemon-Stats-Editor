#include "include.h"
#include "UI/BasicUiElements/CSVComboBoxInt.h"

#include "CSV/StringTypes/ParenthValueString.h"
#include "CSV/StringTypes/IntHexParenthValue.h"
#include "CSV/Databases/ColumnDatabase.h"

CSVComboBoxInt::CSVComboBoxInt
(
	const std::string& InName,
	UiSection* InParent, const
	std::string& InCSVFileName,
	const std::string& InColumnName,
	const std::string& InColumnDatabaseCSVFileName
) :
	BasicUiElement<std::string>(InName, InParent, InCSVFileName, InColumnName),
	ColumnDatabaseCSVFileName(InColumnDatabaseCSVFileName)
{
}

CSVComboBoxInt::CSVComboBoxInt
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnDatabaseCSVFileName
) :
	BasicUiElement<std::string>(InName, InParent, InCSVFileName, InName),
	ColumnDatabaseCSVFileName(InColumnDatabaseCSVFileName)
{
}

void CSVComboBoxInt::Refresh()
{
	// Reload the EntriesList database this combo box pulls from
	const std::string ColumnDatabaseName = std::format("{}-EntriesList", ColumnDatabaseCSVFileName);

	if (bShouldReloadDatabaseOnRefresh)
	{
		ColumnDatabase::LoadEntryNameDatabase(
			ColumnDatabaseName,
			ColumnDatabaseCSVFileName
		);
	}

	EntriesList = ColumnDatabase::GetColumnDatabase(ColumnDatabaseName)->GetEntriesAsStrings();

	// Refresh the current value in the CSV file.
	BasicUiElement::Refresh();
	IntHexParenthValue ManagedValueIntHex = IntHexParenthValue(GetManagedValue());
	int32_t ManagedIntVal = ManagedValueIntHex.GetValueAsInt();

	std::vector<ParenthValueString> EntriesAsParenthValues;
	EntriesAsParenthValues.reserve(EntriesList.size());

	for (auto Entry : EntriesList)
	{
		EntriesAsParenthValues.push_back(ParenthValueString(Entry));
	}

	auto EntryMatchingIntItr = std::find_if(
	EntriesAsParenthValues.begin(), 
	EntriesAsParenthValues.end(),
		[ManagedIntVal](const ParenthValueString& Entry)
		{
			return Entry.GetValue() == std::format("{}", ManagedIntVal);
		}
	);

	if (EntryMatchingIntItr != EntriesAsParenthValues.end())
	{
		SelectedEntry = std::distance(EntriesAsParenthValues.begin(), EntryMatchingIntItr);
	}
	else
	{
		SelectedEntry = 0;
	}

	CalculateMinSize();
}

void CSVComboBoxInt::Tick()
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
void CSVComboBoxInt::SetShouldReloadDatabaseOnRefresh(const bool ShouldReload)
{
	bShouldReloadDatabaseOnRefresh = ShouldReload;
}

void CSVComboBoxInt::SetSelectedEntry(const uint32_t NewSelectedEntry)
{
	// Only update the selected entry if
	// The new entry does not match it.
	if (SelectedEntry != NewSelectedEntry)
	{
		SelectedEntry = NewSelectedEntry;

		std::vector<ParenthValueString> EntriesAsParenthValues;
		EntriesAsParenthValues.reserve(EntriesList.size());

		for (auto Entry : EntriesList)
		{
			EntriesAsParenthValues.push_back(ParenthValueString(Entry));
		}

		IntHexParenthValue NewValue = IntHexParenthValue(stoi(EntriesAsParenthValues.at(SelectedEntry).GetValue()));
		SetManagedValue(NewValue.GetParenthValueString());
	}
}

void CSVComboBoxInt::CalculateMinSize()
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
		ICLogger::Warn("CSVComboBoxInt CalculateMinSize called with an empty Entries List");
		return;
	}

	// Ensure the combo box is big enough to fully display the largest entry. This will also be
	// a reasonable min for the filter text entry.
	const std::string LongestEntry = *LongestEntryItr;
	GetSize().SetMinFromString(LongestEntry);
	GetSize().SetMax(FLT_MAX);

	// Add the dropdown button and space between it as padding space. The dropdown button
	// Is the same size as one InputInt step button
	auto& Style = ImGui::GetStyle();

	const float ButtonText = ImGui::CalcTextSize("+").x;
	const float ButtonFramePadding = Style.FramePadding.x * 2;
	const float ButtonWidth = ButtonText + ButtonFramePadding;

	// Additionally, the combo box entry also has frame padding on either side,
	// so we need to include that in the padding space as well.
	const float ComboBoxPadding = Style.FramePadding.x * 2 + Style.ItemInnerSpacing.x;

	// There are 2 buttons, so we add the ButtonWidth padding twice
	GetSize().SetPaddingSpace(ButtonWidth + ComboBoxPadding);
}