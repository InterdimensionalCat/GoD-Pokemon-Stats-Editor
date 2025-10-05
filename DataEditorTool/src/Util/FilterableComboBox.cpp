#include "include.h"

#include "Util/FilterableComboBox.h"
#include "UiSections/UiSection.h"
#include "Command/ModifyValue.h"
#include "GoD-UI-Windows.h"

bool FilterableComboBox(std::shared_ptr<OldUiSection> CurrentSection, const std::string& ComboBoxName, std::vector<std::string> UnfilteredItemsList, std::shared_ptr<std::string> SelectedItemString, std::shared_ptr<std::string> FilterString)
{
    // We want to filter items based on whatever the user has typed since focusing this box
    std::vector<std::string> FilteredItemsArr;

    if ((*FilterString) != "")
    {
        // Filter items from the combobox based on the typed string
        for (auto& Item : UnfilteredItemsList)
        {
            std::string ItemAllUpper = Item;
            std::transform(ItemAllUpper.begin(), ItemAllUpper.end(), ItemAllUpper.begin(), ::toupper);
            if (ItemAllUpper.find(*FilterString) != std::string::npos)
            {
                // Add this item if what has been typed is a substring of this item
                FilteredItemsArr.push_back(Item);
            }
        }
    }
    else {
        // If nothing has been typed show the full list
        FilteredItemsArr = UnfilteredItemsList;
    }

    if (FilteredItemsArr.size() == 0) {
        // Clear string buffer and reset filtered items if we ever fail to find.
        FilteredItemsArr = UnfilteredItemsList;
        (*FilterString) = "";
    }

    // Allows enter to activate the combo box.
    ImGui::GetCurrentContext()->NavNextActivateFlags = ImGuiActivateFlags_PreferInput;

    if (ImGui::BeginCombo(ComboBoxName.c_str(), SelectedItemString->c_str(), 0))
    {
        // Allows enter to close the combo box if something has been typed.
        bool EnterPressed = ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Enter, false);
        if (EnterPressed && (*FilterString) != "") {
            ImGui::CloseCurrentPopup();
            (*FilterString) = "";
        }

        if (std::find(FilteredItemsArr.begin(), FilteredItemsArr.end(), *SelectedItemString) == FilteredItemsArr.end() && FilteredItemsArr.size() != 0)
        {
            // Set the top result as the new selected item if the previous top result was removed from the search.
            //Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<std::string>>(CurrentSection, SelectedItemString, *SelectedItemString, FilteredItemsArr.at(0), FilterString));
        }

        for (int32_t n = 0; n < FilteredItemsArr.size(); n++)
        {
            const bool is_selected = ((*SelectedItemString) == FilteredItemsArr.at(n));
            if (ImGui::Selectable(FilteredItemsArr.at(n).c_str(), is_selected))
            {
                // If we actually select an object, reset the filter string before the combo box is closed.
                //Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<std::string>>(CurrentSection, SelectedItemString, *SelectedItemString, FilteredItemsArr.at(n), FilterString));
                (*FilterString) = "";
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    else {
        // Clear filter string if this isn't selected.
        (*FilterString) = "";
        return false;
    }

    // Convert any newly typed characters to a string and add it to the filter string.
    char Buffer[32];
    if (ImGui::GetIO().InputQueueCharacters.begin() != ImGui::GetIO().InputQueueCharacters.end())
    {
        ImTextStrToUtf8(Buffer, 32, ImGui::GetIO().InputQueueCharacters.begin(), ImGui::GetIO().InputQueueCharacters.end());
        std::string BufferStr = Buffer;
        std::transform(BufferStr.begin(), BufferStr.end(), BufferStr.begin(), ::toupper);
        (*FilterString) += BufferStr;
    }

    // If a box is hovered, typing something will activate it without requiring an enter press.
    if (ImGui::IsItemHovered() && (*FilterString) != "")
    {
        ImGui::ActivateItemByID(ImGui::GetItemID());
    }

    return true;
}
