#include "include.h"

#include "UiSections/UiSubsections/TypeInfo.h"
#include "Util/FilterableComboBox.h"
#include "Util/ItemSizeUtils.h"
#include "GoD-UI-Windows.h"

TypeInfo::TypeInfo(OldUiSection* InParent, const std::string& InSubsectionName) : UiSubsection(InParent, InSubsectionName)
{
    TypesListItems = GoDUIWindowsInstance::instance.TypesCSV->GetTypesList();

    FieldLabels.insert(std::pair("Type 1", "Type 1"));
    FieldLabels.insert(std::pair("Type 2", "Type 2"));
}

void TypeInfo::UpdateElement()
{
    //ImGui::PushItemWidth(160);
    FilterableComboBox(Parent->shared_from_this(), "Type 1", TypesListItems, CurrentType1, CurrentType1Filter);

    //ImGui::PushItemWidth(160);
    FilterableComboBox(Parent->shared_from_this(), "Type 2", TypesListItems, CurrentType2, CurrentType2Filter);
}

void TypeInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    UiSubsection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
	*CurrentType1 = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Types 1");
	*CurrentType2 = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Types 2");
}

void TypeInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    (*PokemonStatsJson)["Types 1"] = *CurrentType1;
    (*PokemonStatsJson)["Types 2"] = *CurrentType2;
}

float TypeInfo::CalculateLargestLabelLength() const
{
    // All the labels are the same size
    return GetMaxTextSize(FieldLabels).first;
}

float TypeInfo::CalculateLargestElementLength() const
{
    // The largest (and only) line has a text input box for the entry name stat, and a pokeface picture
    auto PossibleNames = GoDUIWindowsInstance::instance.TypesCSV->GetAllEntriesOfKey("Entry Name", true);

    float MaxTextboxTextSize = GetMaxTextSize(PossibleNames).first;

    auto& Style = ImGui::GetStyle();

    return MaxTextboxTextSize + (Style.FramePadding.x * 2);
}
