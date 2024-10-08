#include "Egg Moves.h"
#include "GoD-UI-Windows.h"
#include "Util/FilterableComboBox.h"
#include "Util/ItemSizeUtils.h"

#include "imgui/misc/cpp/imgui_stdlib.h"
#include "imgui/imgui_internal.h"

#include <algorithm>

EggMovesInfo::EggMovesInfo(UiSection* InParent, const std::string& InSubsectionName) : UiSubsection(InParent, InSubsectionName)
{
    MoveItems = GoDUIWindowsInstance::instance.MovesCSV->GetMovesList();

    for (int32_t i = 0; i < 8; i++)
    {
        EggMovesMove.push_back(std::make_shared<std::string>("---"));
        StringTypedWhileFocused.push_back(std::make_shared<std::string>(""));
    }
}

void EggMovesInfo::UpdateElement()
{

    auto& Style = ImGui::GetStyle();
    auto SpaceAvailable = ImGui::GetContentRegionAvail().x * 0.5f;
    float DropdownWidth = SpaceAvailable - (Style.ItemInnerSpacing.x) - (Style.ItemSpacing.x) - (Style.FramePadding.x);

    auto MinSizeForOneBox = Parent->MinSubsectionFieldSize / 2.f;

    // Ensure we are never smaller than the min size needed
    if (DropdownWidth < MinSizeForOneBox)
    {
        DropdownWidth = MinSizeForOneBox;
        ItemsPerLine = 1;
    }
    else 
    {
        ItemsPerLine = 2;
    }

    ImGui::PushItemWidth(DropdownWidth);

    for (int32_t i = 0; i < 8; i++)
    {
        std::string MoveTextBoxName = std::format("##Egg Move {}", i + 1);
        //ImGui::PushItemWidth(150);
        FilterableComboBox(Parent->shared_from_this(), MoveTextBoxName, MoveItems, EggMovesMove.at(i), StringTypedWhileFocused.at(i));
        if (i % 2 == 0 && ItemsPerLine != 1)
        {
            ImGui::SameLine();
        }
    }

    ImGui::PopItemWidth();
}

void EggMovesInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    for (int32_t i = 0; i < 8; i++)
    {
        std::string BaseString = "Egg Moves";

        (*EggMovesMove.at(i)) = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, std::format("{} {}", BaseString, i + 1));
    }
}

void EggMovesInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    for (int32_t i = 0; i < 8; i++)
    {
        std::string BaseString = "Egg Moves";

        (*PokemonStatsJson)[std::format("{} {}", BaseString, i + 1)] = *EggMovesMove.at(i);
    }
}

float EggMovesInfo::CalculateLargestLabelLength() const
{
    // All the labels are the same size
    return 0.f;
}

float EggMovesInfo::CalculateLargestElementLength() const
{
    // Two egg move text boxes are back to back in the layout
    auto PossibleNames = GoDUIWindowsInstance::instance.MovesCSV->GetAllEntriesOfKey("Entry Name", true);

    auto& Style = ImGui::GetStyle();

    float MaxTextboxSize = GetMaxTextSize(PossibleNames).first * 2;
    MaxTextboxSize += ImGui::GetFrameHeight() * 2; // for dropdown button
    MaxTextboxSize += Style.ItemInnerSpacing.x;
    MaxTextboxSize += Style.ItemSpacing.x;
    MaxTextboxSize += Style.FramePadding.x;

    return MaxTextboxSize;
}
