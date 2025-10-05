#include "include.h"

#include "UiSections/UiSubsections/MiscInfo.h"
#include "Command/ModifyHappiness.h"
#include "Util/FilterableComboBox.h"
#include "Util/ItemSizeUtils.h"
#include "GoD-UI-Windows.h"



MiscInfo::MiscInfo(OldUiSection* InParent, const std::string& InSubsectionName) : UiSubsection(InParent, InSubsectionName)
{
    // Get all unique Exp Rate values.
    ExpRateList = std::vector<std::string>(6, "---");

    auto AllExpYieldEntries = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey("Level up Rate", false);

    for (auto& Rate : AllExpYieldEntries)
    {
        auto RateInArrItr = std::find(ExpRateList.begin(), ExpRateList.end(), Rate);
        if (RateInArrItr == ExpRateList.end())
        {
            auto FirstParenth = Rate.find("(");
            auto SecondParenth = Rate.find(")");
            auto RateSubstr = Rate.substr(FirstParenth + 1, SecondParenth - (FirstParenth + 1));

            ExpRateList.at(stoi(RateSubstr)) = Rate;
        }
    }

    // Xp Rate Documentation:
    // Standard (0):   Medium Fast
    // Very Fast (1):  Erratic
    // Slowest (2)     Fluctuating
    // Slow (3):       Medium Slow
    // Fast (4):       Fast
    // Very Slow (5):  Slow

    // Get all unique Gender Ratio values.
    GenderRatioList = std::vector<std::string>();

    auto AllGenderRatioEntries = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey("Gender Ratio", false);

    for (auto& Ratio : AllGenderRatioEntries)
    {
        auto RatioInArrItr = std::find(GenderRatioList.begin(), GenderRatioList.end(), Ratio);
        if (RatioInArrItr == GenderRatioList.end())
        {
            GenderRatioList.push_back(Ratio);
        }
    }

    std::sort(GenderRatioList.begin(), GenderRatioList.end(), [] (const std::string& A, const std::string& B)
        {
            auto AFirstParenth = A.find("(");
            auto ASecondParenth = A.find(")");
            auto ASubstr = A.substr(AFirstParenth + 1, ASecondParenth - (AFirstParenth + 1));

            auto BFirstParenth = B.find("(");
            auto BSecondParenth = B.find(")");
            auto BSubstr = B.substr(BFirstParenth + 1, BSecondParenth - (BFirstParenth + 1));

            return stoi(ASubstr) < stoi(BSubstr);
        }
    );

    // For some reason 87.5% female is never used, so this list will have 7 entries instead of 8.

    FieldLabels.insert(std::pair("Level Up Rate", "Level Up Rate"));
    FieldLabels.insert(std::pair("Exp Yield", "Exp Yield"));
    FieldLabels.insert(std::pair("Gender Ratio", "Gender Ratio"));
    FieldLabels.insert(std::pair("Catch Rate", "Catch Rate"));
    FieldLabels.insert(std::pair("Height (Meters)", "Height (Meters)"));
    FieldLabels.insert(std::pair("Weight (Kg)", "Weight (Kg)"));
    FieldLabels.insert(std::pair("Base Happiness", "Base Happiness"));

}

void MiscInfo::UpdateElement()
{
    //ImGui::PushItemWidth(160);
    FilterableComboBox(Parent->shared_from_this(), "Level Up Rate", ExpRateList, ExpRate, ExpRateFilterString);

    //ImGui::PushItemWidth(160);
    const int32_t PrevExpYield = *ExpYield;
    if (ImGui::InputInt("Exp Yield", ExpYield.get()))
    {
        //Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), ExpYield, PrevExpYield, *ExpYield));
    }

    //ImGui::PushItemWidth(160);
    FilterableComboBox(Parent->shared_from_this(), "Gender Ratio", GenderRatioList, GenderRatio, GenderRatioFilterString);

    //ImGui::PushItemWidth(160);
    const int32_t PrevCatchRate = *CatchRate;
    if (ImGui::InputInt("Catch Rate", CatchRate.get()))
    {
        //Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), CatchRate, PrevCatchRate, *CatchRate));
    }

    //ImGui::PushItemWidth(160);
    const int32_t PrevHeight = *Height;
    if (ImGui::InputInt("Height (Meters)", Height.get())) {
        //Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), Height, PrevHeight, *Height));
    }

    //ImGui::PushItemWidth(160);
    const int32_t PrevWeight = *Weight;
    if(ImGui::InputInt("Weight (Kg)", Weight.get()))
    {
        //Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), Weight, PrevWeight, *Weight));
    }

    //ImGui::PushItemWidth(160);
    const int32_t PrevHappiness = *HappinessInt;
    if (ImGui::InputInt("Base Happiness", HappinessInt.get()))
    {
        //Command::PushNewCommandAndExecute(std::make_shared<ModifyHappiness>(Parent->shared_from_this(), HappinessString, HappinessInt, PrevHappiness, *HappinessInt));
    }
}

void MiscInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    UiSubsection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
    *ExpRate = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Level up Rate");
    *ExpYield = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Exp yield");

    *GenderRatio = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Gender Ratio");
    *CatchRate = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Catch Rate");

    *Height = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Height");
    *Weight = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Weight");

    *HappinessString = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, "Base Happiness");

    // For some reason happiness is stored in the form "{int} (0x{hex})", so we need to convert it to an int.
    *HappinessInt = stoi(HappinessString->substr(0, HappinessString->find(" ")));
}

void MiscInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    (*PokemonStatsJson)["Level up Rate"] = *ExpRate;
    (*PokemonStatsJson)["Exp yield"] = std::format("{}", *ExpYield);

    (*PokemonStatsJson)["Gender Ratio"] = *GenderRatio;
    (*PokemonStatsJson)["Catch Rate"] = std::format("{}", *CatchRate);

    (*PokemonStatsJson)["Height"] = std::format("{}", *Height);
    (*PokemonStatsJson)["Weight"] = std::format("{}", *Weight);

    (*PokemonStatsJson)["Base Happiness"] = *HappinessString;
}

float MiscInfo::CalculateLargestLabelLength() const
{
    // All the labels are the same size
    return GetMaxTextSize(FieldLabels).first;
}

float MiscInfo::CalculateLargestElementLength() const
{
    // The largest (and only) line has a text input box for the entry name stat, and a pokeface picture
    auto PossibleRates = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey("Level up Rate", false);
    auto PossibleRatios = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey("Gender Ratio", false);

    float MaxTextboxTextSize = GetMaxTextSize(PossibleRates).first;
    MaxTextboxTextSize = std::max(MaxTextboxTextSize, GetMaxTextSize(PossibleRatios).first);

    auto& Style = ImGui::GetStyle();

    return MaxTextboxTextSize + (Style.FramePadding.x * 2);
}
