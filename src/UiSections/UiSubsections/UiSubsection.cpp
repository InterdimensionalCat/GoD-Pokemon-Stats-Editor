#include "UiSubsection.h"
#include "UiSections/UiSection.h"
#include "GoD-UI-Windows.h"

UiSubsection::UiSubsection(UiSection* InParent, const std::string& InSubsectionName) : Parent(InParent), SubsectionName(InSubsectionName)
{

}

void UiSubsection::UpdateElement()
{
}

void UiSubsection::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    if (ShouldSave)
    {
        SaveToPokemonStatsJson(GoDUIWindowsInstance::instance.StatsCSV->GetDataObject().at(Parent->GetCurrentPokemonIndex()));
    }
}

void UiSubsection::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{

}

std::string UiSubsection::GetSubsectionName() const
{
    return SubsectionName;
}

float UiSubsection::CalculateLargestLabelLength() const
{
    return -1.f;
}

float UiSubsection::CalculateLargestElementLength() const
{
    return -1.f;
}

void UiSubsection::OnFontUpdated()
{

}
