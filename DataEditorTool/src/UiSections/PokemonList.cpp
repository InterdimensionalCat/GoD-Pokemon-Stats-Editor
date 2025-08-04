#include "include.h"

#include "UiSections/PokemonList.h"
#include "Command/SwitchActivePokemon.h"
#include "Util/ItemSizeUtils.h"
#include "GoD-UI-Windows.h"

PokemonList::PokemonList(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize) : UiSection(InWindowName, InPos, InSize)
{
    PokemonListItems = GoDUIWindowsInstance::instance.StatsCSV->GetPokemonList();

    MinNeededLength = CalculateMinNeededLineLength();

    LargestLabelLength = CalculateLargestLabelLength();
    LargestElementLength = CalculateLargestElementLength();
}

void PokemonList::UpdateElement()
{
    // Search bar
    auto& Style = ImGui::GetStyle();

    auto SpaceAvailable = ImGui::GetContentRegionAvail().x;
    float SpeciesTextBoxWidth = SpaceAvailable - (Style.FramePadding.x * 2);

    // Ensure we are never smaller than the min size needed
    if (SpeciesTextBoxWidth < LargestElementLength + Style.ScrollbarSize + Style.ItemInnerSpacing.x)
    {
        SpeciesTextBoxWidth = LargestElementLength + Style.ScrollbarSize + Style.ItemInnerSpacing.x;
    }

    ImGui::PushItemWidth(SpeciesTextBoxWidth);

    //ImGui::PushItemWidth(165);
    ImGuiInputTextFlags TextBoxFlags = 0;

    TextBoxFlags |= ImGuiInputTextFlags_CharsUppercase;   // Turn a..z into A..Z

    std::string PrevText = FilterString;
    ImGui::InputText("##PokemonListSearchBox", &FilterString, TextBoxFlags);
    auto TextBoxID = ImGui::GetItemID();
    bool bTextBoxActive = ImGui::IsItemActivated();

    if (bActivateTextBoxFromComboTyping)
    {
        if (ImGuiInputTextState * state{ ImGui::GetInputTextState(ImGui::GetItemID()) })
            state->ReloadUserBufAndMoveToEnd();
        bActivateTextBoxFromComboTyping = false;
    }

    // We want to filter pokemon based on whatever the user has typed since focusing this box
    std::vector<std::string> FilteredItemsArr;

    if (FilterString != "")
    {
        // Filter items from the combobox based on the typed string
        for (auto& Pokemon : PokemonListItems)
        {
            if (Pokemon.find(FilterString) != std::string::npos)
            {
                // Add this item if what has been typed is a substring of this pokemon
                FilteredItemsArr.push_back(Pokemon);
            }
        }
    }
    else {
        // If nothing has been typed show the full pokemon list
        FilteredItemsArr = PokemonListItems;
    }

    if (FilteredItemsArr.size() == 0) {
        // Clear string buffer and reset filtered items if we ever fail to find.
        FilteredItemsArr = PokemonListItems;
        FilterString = "";
    }
    // ImVec2(SpeciesTextBoxWidth, -FLT_MIN)

    if (ImGui::BeginListBox("##Current Pokemon-box", ImVec2(0,-FLT_MIN)))
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(Style.ItemSpacing.x, Style.ItemSpacing.y + 2.f));
        if (std::find(FilteredItemsArr.begin(), FilteredItemsArr.end(), CurrentlySelectedItem) == FilteredItemsArr.end() && FilteredItemsArr.size() != 0)
        {
            // Set the top result as the new selected item if the previous top result was removed from the search.
            Command::PushNewCommandAndExecute(std::make_shared<SwitchActivePokemon>(CurrentlySelectedItem, FilteredItemsArr.at(0), std::static_pointer_cast<PokemonList>(shared_from_this())));
            //SetCurrentlySelectedItem(FilteredItemsArr.at(0));
        }

        for (int32_t n = 0; n < FilteredItemsArr.size(); n++)
        {
            if (bScrollToItem && FilteredItemsArr.size() == PokemonListItems.size() && CurrentlySelectedItem == FilteredItemsArr.at(n))
            {
                ImGui::ScrollToItem(ImGuiScrollFlags_AlwaysCenterY);
                SetScrollToItem(false);
            }

            // Allows enter to close the combo box if something has been typed.
            bool EnterPressed = ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Enter, false);
            if (EnterPressed && FilterString != "") {
                FilterString = "";
                SetScrollToItem(true);
            }

            const bool bIsSelected = (CurrentlySelectedItem == FilteredItemsArr.at(n));
            if (ImGui::Selectable(FilteredItemsArr.at(n).c_str(), bIsSelected))
            {
                if (CurrentlySelectedItem != FilteredItemsArr.at(n))
                {
                    Command::PushNewCommandAndExecute(std::make_shared<SwitchActivePokemon>(CurrentlySelectedItem, FilteredItemsArr.at(n), std::static_pointer_cast<PokemonList>(shared_from_this())));
                }
                //SetCurrentlySelectedItem(FilteredItemsArr.at(n));
                if (FilterString != "") {
                    FilterString = "";
                    SetScrollToItem(true);
                }
            }

            if (bIsSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::PopStyleVar();
        ImGui::EndListBox();
    }
    else
    {
        // Clear filter string if this isn't selected.
        FilterString = "";
        SetScrollToItem(true);
    }

    // Make arrow keys transition to list box
    if (ImGui::GetFocusID() == TextBoxID)
    {
        // Up/Down arrow keys can change the filtered item even when the text box has focus
        if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_UpArrow, false))
        {
            auto FilteredItemItr = std::find(FilteredItemsArr.begin(), FilteredItemsArr.end(), CurrentlySelectedItem);
            if (FilteredItemItr != FilteredItemsArr.end() && FilteredItemItr != FilteredItemsArr.begin())
            {
                FilteredItemItr--;
                Command::PushNewCommandAndExecute(std::make_shared<SwitchActivePokemon>(CurrentlySelectedItem, *FilteredItemItr, std::static_pointer_cast<PokemonList>(shared_from_this())));
                ImGui::FocusItem();
            }
        }

        if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_DownArrow, false))
        {
            auto FilteredItemItr = std::find(FilteredItemsArr.begin(), FilteredItemsArr.end(), CurrentlySelectedItem);
            if (FilteredItemItr != FilteredItemsArr.end())
            {
                FilteredItemItr++;
                if (FilteredItemItr != FilteredItemsArr.end())
                {
                    Command::PushNewCommandAndExecute(std::make_shared<SwitchActivePokemon>(CurrentlySelectedItem, *FilteredItemItr, std::static_pointer_cast<PokemonList>(shared_from_this())));
                    ImGui::FocusItem();
                }
            }
        }
    }

    // Convert any newly typed characters to a string and add it to the filter string if this window is focused.
    // do not check characters if control is down though as to not interfere with commands
    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
    {
        if (!(ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
        {
            char Buffer[32];
            if (ImGui::GetIO().InputQueueCharacters.begin() != ImGui::GetIO().InputQueueCharacters.end() && !bTextBoxActive)
            {
                ImGui::ActivateItemByID(TextBoxID);
                ImTextStrToUtf8(Buffer, 32, ImGui::GetIO().InputQueueCharacters.begin(), ImGui::GetIO().InputQueueCharacters.end());
                std::string BufferStr = Buffer;
                std::cout << BufferStr << "\n";
                std::transform(BufferStr.begin(), BufferStr.end(), BufferStr.begin(), ::toupper);
                FilterString += BufferStr;
                bActivateTextBoxFromComboTyping = true;
            }
        }
    }
    else
    {
        // Clear filter string if this window isn't focused.
        //FilterString = "";
    }

    ImGui::PopItemWidth();
}

void PokemonList::SetScrollToItem(const bool InScrollToItem)
{
    bScrollToItem = InScrollToItem;
}

void PokemonList::SetCurrentlySelectedItem(const std::string& NewItemString)
{
    auto NewItemIndexIt = std::find(PokemonListItems.begin(), PokemonListItems.end(), NewItemString);
    int32_t NewItemIndex = static_cast<int32_t>(std::distance(PokemonListItems.begin(), NewItemIndexIt));
    
    bool ShouldUpdate = CurrentlySelectedItem != NewItemString;
    CurrentlySelectedItem = NewItemString;
    if (ShouldUpdate)
    {
        GoDUIWindowsInstance::instance.OnCurrentPokemonUpdated(NewItemIndex, true);
    }
}

const std::vector<std::string>& PokemonList::GetPokemonListItems()
{
    return PokemonListItems;
}

float PokemonList::CalculateMinNeededLineLength() const
{
    float MaxLabelLength = CalculateLargestLabelLength();
    float MaxElementLength = CalculateLargestElementLength();

    if (MaxLabelLength < 0 && MaxElementLength < 0)
    {
        return -1;
    }

    MaxLabelLength = std::max(MaxLabelLength, 0.f);
    MaxElementLength = std::max(MaxElementLength, 0.f);

    return MaxLabelLength + MaxElementLength;
}

float PokemonList::CalculateLargestLabelLength() const
{
    // No labels in the pokemon list
    return 0.f;
}

float PokemonList::CalculateLargestElementLength() const
{
    auto PossibleNames = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey("Entry Name", false);

    float MaxTextboxTextSize = GetMaxTextSize(PossibleNames).first;

    auto& Style = ImGui::GetStyle();

    return MaxTextboxTextSize + (Style.FramePadding.x * 2);
}

void PokemonList::OnFontUpdated()
{
    UiSection::OnFontUpdated();
    MinNeededLength = CalculateMinNeededLineLength();

    LargestLabelLength = CalculateLargestLabelLength();
    LargestElementLength = CalculateLargestElementLength();
}
