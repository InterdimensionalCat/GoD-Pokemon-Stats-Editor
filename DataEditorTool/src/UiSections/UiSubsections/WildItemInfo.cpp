#include "include.h"

#include "UiSections/UiSubsections/WildItemInfo.h"
#include "Util/FilterableComboBox.h"
#include "Util/ItemSizeUtils.h"
#include "GoD-UI-Windows.h"

WildItemInfo::WildItemInfo(OldUiSection* InParent, const std::string& InSubsectionName) : UiSubsection(InParent, InSubsectionName)
{
    WildItemsListItems = GoDUIWindowsInstance::instance.ItemsCSV->GetItemsList();

    FieldLabels.insert(std::pair("Wild Item 1", "Wild Item 1"));
    FieldLabels.insert(std::pair("Wild Item 1", "Wild Item 1"));
}

void WildItemInfo::UpdateElement()
{
    //ImGui::PushItemWidth(160);
    FilterableComboBox(Parent->shared_from_this(), "Wild Item 1", WildItemsListItems, CurrentWildItem1, CurrentWildItem1Filter);

    //ImGui::PushItemWidth(160);
    FilterableComboBox(Parent->shared_from_this(), "Wild Item 2", WildItemsListItems, CurrentWildItem2, CurrentWildItem2Filter);
}

void WildItemInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    UiSubsection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
    (*CurrentWildItem1) = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Wild Items 1");
    (*CurrentWildItem2) = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Wild Items 2");
}

void WildItemInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    (*PokemonStatsJson)["Wild Items 1"] = *CurrentWildItem1;
    (*PokemonStatsJson)["Wild Items 2"] = *CurrentWildItem2;
}

float WildItemInfo::CalculateLargestLabelLength() const
{
    // All the labels are the same size
    return GetMaxTextSize(FieldLabels).first;
}

float WildItemInfo::CalculateLargestElementLength() const
{
    // The largest (and only) line has a text input box for the entry name stat, and a pokeface picture
    auto PossibleNames = GoDUIWindowsInstance::instance.ItemsCSV->GetAllEntriesOfKey("Entry Name", true);

    float MaxTextboxTextSize = GetMaxTextSize(PossibleNames).first;

    auto& Style = ImGui::GetStyle();

    return MaxTextboxTextSize + (Style.FramePadding.x * 2);
}


