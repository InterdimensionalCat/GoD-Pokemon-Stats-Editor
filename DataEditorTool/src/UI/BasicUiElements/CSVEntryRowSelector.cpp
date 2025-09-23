#include "include.h"
#include "UI/BasicUiElements/CSVEntryRowSelector.h"

#include "CSV/CSVDatabase.h"
#include "CSV/NewCSVData.h"
#include "UI/TabCSVState.h"

CSVEntryRowSelector::CSVEntryRowSelector
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName
) :
	UiCSVElement(InName, InParent, InCSVFileName, InColumnName)
{
	GetSize().SetSizeRule(UiSizeRule_Normal);
	SetSizeSource(UiSizeSource_Self);
}

void CSVEntryRowSelector::Refresh()
{
	auto CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile<GoDCSV::NewCSVData>(GetCSVFileName());
	EntriesList = CSVData->GetStringColumn(GetColumnName());
	CalculateMinSize();
}

void CSVEntryRowSelector::Tick()
{
	auto& Style = ImGui::GetStyle();

	// Show a ListBox with every entry
	const std::string ListBoxName = std::format("{}-{}", GetName(), "ListBox");
	if (ImGui::BeginListBox(ListBoxName.c_str(), ImVec2(0, -FLT_MIN)))
	{
		// Show a text box that acts as a filter for the EntriesList.
		ImGuiInputTextFlags FilterBoxFlags = 0;

		// Force input to be uppercase 
		FilterBoxFlags |= ImGuiInputTextFlags_CharsUppercase;

		// We want AutoSelectAll on now because we don't automatically
		// clear the filter when text is committed.
		FilterBoxFlags |= ImGuiInputTextFlags_AutoSelectAll;

		// User can Ctrl + F to jump to the search bar
		ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);

		// Filter box name is "##{ElementName}-FilterBox"
		const std::string FilterBoxName = std::format("{}-{}", GetName(), "FilterBox");

		// Display a text box that modifies the EntryFilter's input buffer.
		const bool FilterBoxActive = ImGui::InputTextEx
		(
			FilterBoxName.c_str(),
			"Search (Ctrl + F)",
			EntryFilter.InputBuf,
			IM_ARRAYSIZE(EntryFilter.InputBuf),
			ImVec2(-FLT_MIN, 0),
			FilterBoxFlags
		);

		// Rebuild the filter if we typed input into
		// the above text box
		if (FilterBoxActive)
		{
			EntryFilter.Build();
		}

		// Give this text box keyboard focus when this window appears
		if (ImGui::IsWindowAppearing())
		{
			ImGui::SetKeyboardFocusHere(-1);
		}

		if (!FilterBoxActive)
		{
			// If the text box is not active but the window is,
			// any text typing will activate the window and be
			// added to the filter string buffer.
			ActivateFilterTextBoxIfUserTypesInWindow();
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
					break;
				}
			}
		}

		// Space elements out a bit more vertically in the
		// list box so entries don't look super cramped.
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing,
			ImVec2(
				Style.ItemSpacing.x,
				Style.ItemSpacing.y + EntriesListExtraVerticalSpacing)
		);

		for (uint32_t Index = 0; Index < EntriesList.size(); Index++)
		{
			const std::string EntryValue = EntriesList.at(Index);
			const bool EntryIsSelected = SelectedEntry == Index;

			// Set the name of each selectable to "{EntryName}##{ListBoxName}"
			const std::string SelectableNameString = std::format("{}{}", EntryValue, ListBoxName);

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

		ImGui::PopStyleVar();
		ImGui::EndListBox();
	}
}

void CSVEntryRowSelector::SetSelectedEntry(const uint32_t NewSelectedEntry)
{
	// Only update the selected entry if
	// The new entry does not match it.
	if (SelectedEntry != NewSelectedEntry)
	{
		SelectedEntry = NewSelectedEntry;
		GetTabState()->SetCurrentRow(SelectedEntry);
	}
}

void CSVEntryRowSelector::ActivateFilterTextBoxIfUserTypesInWindow()
{
	// Convert any newly typed characters to a string and add it to the filter string if this window is focused.
	// do not check characters if control is down though as to not interfere with commands

	// If this UI section has focus but the filter text box does not,
	// we still want the filter text box to pick up the user's typed input.
	// This will detect any typed inputs and add it to the filter string.
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
	{
		// Only detect input if the CTRL keys are not held down,
		// as this will interfere with keyboard shortcuts otherwise.
		if (!(ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
		{

			const auto& CharactersTypedThisTick = ImGui::GetIO().InputQueueCharacters;

			const size_t NumCharactersTypedThisTick = std::distance(
				CharactersTypedThisTick.begin(),
				CharactersTypedThisTick.end()
			);

			// If the InputQueueCharacters length is more than zero,
			// the user typed a character this tick.
			if (NumCharactersTypedThisTick != 0)
			{
				// Grant keyboard focus to the previous element,
				// which will be filter text box.
				ImGui::SetKeyboardFocusHere(-1);

				// Grab the typed characters from the buffer and add it to the filter string,
				// This will cause whatever we typed just now to appear as typed in the
				// filter text box.
				char TypedCharacterBuffer[32];
				ImTextStrToUtf8(
					TypedCharacterBuffer,
					32,
					CharactersTypedThisTick.begin(),
					CharactersTypedThisTick.end()
				);

				// Will append new characters to the already existing
				// Filter string
				// std::string NewBufferString = EntryFilter.InputBuf;
				// NewBufferString.append(TypedCharacterBuffer);

				// Will clear the current filter and replace it
				// with whatever we started typing
				std::string NewBufferString = TypedCharacterBuffer;

				// Convert the typed characters to uppercase
				std::transform(
					NewBufferString.begin(),
					NewBufferString.end(),
					NewBufferString.begin(),
					::toupper
				);

				// Replace the filter buffer with this new string.
				size_t StringLength = std::min(NewBufferString.length(), sizeof(EntryFilter.InputBuf) - 1);
				NewBufferString.copy(EntryFilter.InputBuf, StringLength);
				EntryFilter.InputBuf[StringLength] = '\0';

				// Reload the buffer of the previous item,
				// which will be the Filter Text Box.
				ImGuiInputTextState* TextBoxState{ ImGui::GetInputTextState(ImGui::GetItemID()) };
				if (TextBoxState != nullptr)
				{
					// Reload the buffer to grab the updated filter string,
					// and move the cursor to the end of the string.
					TextBoxState->ReloadUserBufAndMoveToEnd();

					// Don't automatically select all when the text box
					// is focused in this way, this allows users to easily
					// append more to the filter string when navigating the
					// List Box
					TextBoxState->ClearSelection();

					EntryFilter.Build();
				}
				else
				{
					ICLogger::Warn("Filter Text Box EntryRowSelector {} had invalid state when user typed in the focused window.", GetName());
				}
			}
		}
	}
}

void CSVEntryRowSelector::CalculateMinSize()
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
		ICLogger::Warn("CSVEntryRowSelector CalculateMinSize called with an empty Entries List");
		return;
	}

	// Ensure the combo box is big enough to fully display the largest entry. This will also be
	// a reasonable min for the filter text entry.
	const std::string LongestEntry = *LongestEntryItr;
	GetSize().SetMinFromString(LongestEntry);
	GetSize().SetMax(FLT_MAX);

	// Add the size of the scrollbar and the spacing between the box and the scrollbar as padding space
	auto& Style = ImGui::GetStyle();
	const float ScrollbarPlusPadding = Style.ScrollbarSize + Style.ItemInnerSpacing.x;
	GetSize().SetPaddingSpace(ScrollbarPlusPadding);
}