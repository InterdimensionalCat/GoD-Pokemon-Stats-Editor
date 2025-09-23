#include "include.h"

#include "UiSections/UiSubsections/IdentificationInfo.h"
#include "Command/ModifyValue.h"
#include "Util/ItemSizeUtils.h"
#include "GoD-UI-Windows.h"

IdentificationInfo::IdentificationInfo(OldUiSection* InParent, const std::string& InSubsectionName) : UiSubsection(InParent, InSubsectionName)
{
    FieldLabels.insert(std::pair("Name", "Name ID"));
    FieldLabels.insert(std::pair("Species", "Species Name ID"));
    FieldLabels.insert(std::pair("Index", "Index"));
    FieldLabels.insert(std::pair("RegionDex", "Hoenn Dex ID"));
    FieldLabels.insert(std::pair("NatDex", "National Dex ID"));
}

// Contains Name ID, index, species Name ID
void IdentificationInfo::UpdateElement()
{
    std::string PrevNameId = *CurrentNameID;
    if (ImGui::InputText(FieldLabels.at("Name").c_str(), CurrentNameID.get()))
    {
        Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<std::string>>(Parent->shared_from_this(), CurrentNameID, PrevNameId, *CurrentNameID));
    }
    //ImGui::PushItemWidth(160);
    std::string PrevSpeciesNameID = *CurrentSpeciesNameID;
    if (ImGui::InputText(FieldLabels.at("Species").c_str(), CurrentSpeciesNameID.get()))
    {
        Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<std::string>>(Parent->shared_from_this(), CurrentSpeciesNameID, PrevSpeciesNameID, *CurrentSpeciesNameID));
    }

    ImGui::BeginDisabled();

    //ImGui::PushItemWidth(160);
    ImGui::InputText(FieldLabels.at("Index").c_str(), &CurrentIndex);
    //ImGui::PushItemWidth(160);
    ImGui::InputInt(FieldLabels.at("RegionDex").c_str(), &CurrentRegionalDexID);
    //ImGui::PushItemWidth(160);
    ImGui::InputInt(FieldLabels.at("NatDex").c_str(), &CurrentNationalDexID);

    ImGui::EndDisabled();
}

void IdentificationInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    UiSubsection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);

    *CurrentNameID = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Name ID");
    *CurrentSpeciesNameID = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Species Name ID");
    CurrentIndex = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Unknown 1");
    CurrentRegionalDexID = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Hoenn dex regional id");
    CurrentNationalDexID = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "National Dex Index");
}

void IdentificationInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    UiSubsection::SaveToPokemonStatsJson(PokemonStatsJson);

    (*PokemonStatsJson)["Name ID"] = *CurrentNameID;
    (*PokemonStatsJson)["Species Name ID"] = *CurrentSpeciesNameID;
    (*PokemonStatsJson)["Unknown 1"] = CurrentIndex;

    (*PokemonStatsJson)["Hoenn dex regional id"] = std::format("{}", CurrentRegionalDexID);
    (*PokemonStatsJson)["National Dex Index"] = std::format("{}", CurrentNationalDexID);
}

float IdentificationInfo::CalculateLargestLabelLength() const
{
    // All the labels are the same size
    return GetMaxTextSize(FieldLabels).first;
}

float IdentificationInfo::CalculateLargestElementLength() const
{
    // The largest (and only) line has a text input box for the entry name stat, and a pokeface picture
    auto PossibleNames = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey("Name ID", false);
    auto PossibleSpecies = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey("Species Name ID", false);

    float MaxTextboxTextSize = GetMaxTextSize(PossibleNames).first;
    MaxTextboxTextSize = std::max(MaxTextboxTextSize, GetMaxTextSize(PossibleSpecies).first);

    auto& Style = ImGui::GetStyle();

    return MaxTextboxTextSize + (Style.FramePadding.x * 2);
}
