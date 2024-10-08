#include "AbilityInfo.h"
#include "GoD-UI-Windows.h"
#include "Util/FilterableComboBox.h"
#include "imgui/misc/cpp/imgui_stdlib.h"
#include "Util/ItemSizeUtils.h"

AbilityInfo::AbilityInfo(UiSection* InParent, const std::string& InSubsectionName) : UiSubsection(InParent, InSubsectionName)
{
    AbilitiesListItems = GoDUIWindowsInstance::instance.AbilitiesCSV->GetAbilitiesList();

    FieldLabels.insert(std::pair("Ability 1", "Ability 1"));
    FieldLabels.insert(std::pair("Ability 2", "Ability 2"));
}

void AbilityInfo::UpdateElement()
{
    //ImGui::PushItemWidth(160);
    FilterableComboBox(Parent->shared_from_this(), "Ability 1", AbilitiesListItems, CurrentAbility1, CurrentAbility1Filter);

    //ImGui::PushItemWidth(160);
    FilterableComboBox(Parent->shared_from_this(), "Ability 2", AbilitiesListItems, CurrentAbility2, CurrentAbility2Filter);
}

void AbilityInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    UiSubsection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
    *CurrentAbility1 = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Abilities 1");
    *CurrentAbility2 = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Abilities 2");
}

void AbilityInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    (*PokemonStatsJson)["Abilities 1"] = *CurrentAbility1;
    (*PokemonStatsJson)["Abilities 2"] = *CurrentAbility2;
}

float AbilityInfo::CalculateLargestLabelLength() const
{
    // All the labels are the same size
    return GetMaxTextSize(FieldLabels).first;
}

float AbilityInfo::CalculateLargestElementLength() const
{
    // The largest (and only) line has a text input box for the entry name stat, and a pokeface picture
    auto PossibleNames = GoDUIWindowsInstance::instance.AbilitiesCSV->GetAllEntriesOfKey("Entry Name", true);

    float MaxTextboxTextSize = GetMaxTextSize(PossibleNames).first;

    auto& Style = ImGui::GetStyle();

    return MaxTextboxTextSize + (Style.FramePadding.x * 2);
}
