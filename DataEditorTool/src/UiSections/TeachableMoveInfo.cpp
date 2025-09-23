#include "include.h"

#include "UiSections/TeachableMoveInfo.h"
#include "Command/ModifyValue.h"
#include "Util/ItemSizeUtils.h"
#include "GoD-UI-Windows.h"

TeachableMoveInfo::TeachableMoveInfo(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize) : OldUiSection(InWindowName, InPos, InSize), TMLearnField(), HMLearnField(), TutorLearnField()
{
    TMCheckboxNames = std::vector<std::string>(50, "");
    HMCheckboxNames = std::vector<std::string>(8, "");
    TutorCheckboxNames = std::vector<std::string>(12, "");

    auto StatsHeaderArray = GoDUIWindowsInstance::instance.StatsCSV->GetHeaderArray();

    // Cache all the TM header column names.
    for (int32_t i = 0; i < 50; i++)
    {
        // The first TM starts at column 23 (0 indexed)
        TMCheckboxNames.at(i) = StatsHeaderArray.at(i + 23);
        TMLearnField.push_back(std::make_shared<bool>(false));
    }

    // Cache all the HM header column names.
    for (int32_t i = 0; i < 8; i++)
    {
        // The first HM starts at column 73 (0 indexed)
        HMCheckboxNames.at(i) = StatsHeaderArray.at(i + 73);
        HMLearnField.push_back(std::make_shared<bool>(false));
    }

    // Unlike TMs and HMs Tutor Moves annoyingly are stored out of order in the Stats data, 
    // but we will cache and display them in order

    // The order the are stored in is: 08, 11, 03, 01, 06, 02, 05, 04, 07, 10, 12, 09
    // Tutor moves start at 81, so TutorCheckBoxNames[tutor move num - 1] = i + 81 will ensure the moves are in order.
    std::array<int32_t, 12> TutorMoveOrder{ 8, 11, 3, 1, 6, 2, 5, 4, 7, 10, 12, 9 };
    for (int32_t i = 0; i < 12; i++)
    {
        TutorCheckboxNames.at(TutorMoveOrder.at(i) - 1) = StatsHeaderArray.at(i + 81);
        TutorLearnField.push_back(std::make_shared<bool>(false));
    }
    
    MinNeededLength = CalculateMinNeededLineLength();

    LargestLabelLength = CalculateLargestLabelLength();
    LargestElementLength = CalculateLargestElementLength();
}

// Contains Name ID, index, species Name ID
void TeachableMoveInfo::UpdateElement()
{
    auto& Style = ImGui::GetStyle();
    auto SpaceAvailable = ImGui::GetCursorPos().x + ImGui::GetContentRegionAvail().x;

    ItemsPerLine = 1;

    if (SpaceAvailable > MinNeededLength)
    {
        ItemsPerLine = (int32_t)std::floor(SpaceAvailable / MinNeededLength);
    }

    // Display TMs
    ImGui::Text("TMs");
    for (int32_t i = 0; i < 50; i++)
    {
        const bool bPrevTM = *TMLearnField.at(i);
        if (ImGui::Checkbox(TMCheckboxNames.at(i).c_str(), TMLearnField.at(i).get()))
        {
            Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<bool>>(shared_from_this(), TMLearnField.at(i), bPrevTM, (*TMLearnField.at(i))));
        }

        // Display x check boxes on each line
        int32_t RowIndex = (i + 1) % ItemsPerLine;
        if (RowIndex != 0 && i != 49)
        {
            ImGui::SameLine(MinNeededLength * RowIndex);
        }
    }

    ImGui::Dummy(ImVec2(0.0f, Style.ItemSpacing.y * 4));

    // Display HMs
    ImGui::Text("HMs");
    for (int32_t i = 0; i < 8; i++)
    {
        const bool bPrevHM = *HMLearnField.at(i);
        if (ImGui::Checkbox(HMCheckboxNames.at(i).c_str(), HMLearnField.at(i).get()))
        {
            Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<bool>>(shared_from_this(), HMLearnField.at(i), bPrevHM, (*HMLearnField.at(i))));
        }

        // Display x check boxes on each line
        int32_t RowIndex = (i + 1) % ItemsPerLine;
        if (RowIndex != 0 && i != 7)
        {
            ImGui::SameLine(MinNeededLength * RowIndex);
        }
    }

    ImGui::Dummy(ImVec2(0.0f, Style.ItemSpacing.y * 4));

    // Display Tutor Moves
    ImGui::Text("Tutor Moves");
    for (int32_t i = 0; i < 12; i++)
    {
        const bool bPrevTutor = *TutorLearnField.at(i);
        if (ImGui::Checkbox(TutorCheckboxNames.at(i).c_str(), TutorLearnField.at(i).get()))
        {
            Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<bool>>(shared_from_this(), TutorLearnField.at(i), bPrevTutor, (*TutorLearnField.at(i))));
        }

        // Display x check boxes on each line
        int32_t RowIndex = (i + 1) % ItemsPerLine;
        if (RowIndex != 0 && i != 12)
        {
            ImGui::SameLine(MinNeededLength * RowIndex);
        }
    }
    
}

void TeachableMoveInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    OldUiSection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);

    // Update TMs
    for (int32_t i = 0; i < 50; i++)
    {
        // TM keys are in one of two formats, TM0(i) or TM(i) depending on if i is one or two digets.
        std::string BaseKey = "TM";

        if((i + 1) < 10)
        {
            BaseKey += "0";
        }

        BaseKey = std::format("{}{}", BaseKey, i + 1);

        *TMLearnField.at(i) = GoDUIWindowsInstance::instance.StatsCSV->CanPokemonLearn(NewPokemonIndex, BaseKey);
    }

    // Update HMs
    for (int32_t i = 0; i < 8; i++)
    {
        // HM keys are always HM0(i), since they never exceed 1 diget.
        std::string BaseKey = "HM";
        BaseKey = std::format("{}0{}", BaseKey, i + 1);

        *HMLearnField.at(i) = GoDUIWindowsInstance::instance.StatsCSV->CanPokemonLearn(NewPokemonIndex, BaseKey);
    }

    // Update Tutor Moves
    for (int32_t i = 0; i < 12; i++)
    {
        // Tutor Move keys are in one of two formats, TutorMove0(i) or TutorMove(i) depending on if i is one or two digets.
        std::string BaseKey = "TutorMove";

        if ((i + 1) < 10)
        {
            BaseKey += "0";
        }

        BaseKey = std::format("{}{}", BaseKey, i + 1);

        *TutorLearnField.at(i) = GoDUIWindowsInstance::instance.StatsCSV->CanPokemonLearn(NewPokemonIndex, BaseKey);
    }
}

void TeachableMoveInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    // Save TMs
    auto HeaderArray = GoDUIWindowsInstance::instance.StatsCSV->GetHeaderArray();

    for (int32_t i = 0; i < 50; i++)
    {
        // TM keys are in one of two formats, TM0(i) or TM(i) depending on if i is one or two digets.
        std::string BaseKey = "TM";

        if ((i + 1) < 10)
        {
            BaseKey += "0";
        }

        BaseKey = std::format("{}{}", BaseKey, i + 1);

        std::string NewVal = *TMLearnField.at(i) ? "true" : "false";

        // Although the TM/Tutor/HM headers can vary, they will always contain a substr. of TM0X, TMXX, HM0X, TutorMove0X, or TutorMoveXX
        auto RealKey = std::find_if(HeaderArray.begin(), HeaderArray.end(), [BaseKey](const std::string& elt)
            { return elt.find(BaseKey) != std::string::npos; }
        );

        (*PokemonStatsJson)[*RealKey] = NewVal;
    }

    // Update HMs
    for (int32_t i = 0; i < 8; i++)
    {
        // HM keys are always HM0(i), since they never exceed 1 diget.
        std::string BaseKey = "HM";
        BaseKey = std::format("{}0{}", BaseKey, i + 1);

        std::string NewVal = *HMLearnField.at(i) ? "true" : "false";

        // Although the TM/Tutor/HM headers can vary, they will always contain a substr. of TM0X, TMXX, HM0X, TutorMove0X, or TutorMoveXX
        auto RealKey = std::find_if(HeaderArray.begin(), HeaderArray.end(), [BaseKey](const std::string& elt)
            { return elt.find(BaseKey) != std::string::npos; }
        );

        (*PokemonStatsJson)[*RealKey] = NewVal;
    }

    // Update Tutor Moves
    for (int32_t i = 0; i < 12; i++)
    {
        // Tutor Move keys are in one of two formats, TutorMove0(i) or TutorMove(i) depending on if i is one or two digets.
        std::string BaseKey = "TutorMove";

        if ((i + 1) < 10)
        {
            BaseKey += "0";
        }

        BaseKey = std::format("{}{}", BaseKey, i + 1);

        std::string NewVal = *TutorLearnField.at(i) ? "true" : "false";

        // Although the TM/Tutor/HM headers can vary, they will always contain a substr. of TM0X, TMXX, HM0X, TutorMove0X, or TutorMoveXX
        auto RealKey = std::find_if(HeaderArray.begin(), HeaderArray.end(), [BaseKey](const std::string& elt)
            { return elt.find(BaseKey) != std::string::npos; }
        );

        (*PokemonStatsJson)[*RealKey] = NewVal;
    }
}

float TeachableMoveInfo::CalculateMinNeededLineLength() const
{
    float MaxLabelLength = CalculateLargestLabelLength();
    float MaxElementLength = CalculateLargestElementLength();

    return MaxLabelLength + MaxElementLength;
}

float TeachableMoveInfo::CalculateLargestLabelLength() const
{
    auto& Style = ImGui::GetStyle();
    auto MaxLabelSize = GetMaxTextSize(TMCheckboxNames).first;
    MaxLabelSize = std::max(MaxLabelSize, GetMaxTextSize(HMCheckboxNames).first);
    MaxLabelSize = std::max(MaxLabelSize, GetMaxTextSize(TutorCheckboxNames).first);
    MaxLabelSize += Style.ItemSpacing.x;
    MaxLabelSize += Style.ItemInnerSpacing.x;

    return MaxLabelSize;
}

float TeachableMoveInfo::CalculateLargestElementLength() const
{
    // The only element that needs to be on one line is a single checkbox
    auto& Style = ImGui::GetStyle();

    return ImGui::GetFrameHeight() + (Style.FramePadding.x * 2.f);
}

void TeachableMoveInfo::OnFontUpdated()
{
    OldUiSection::OnFontUpdated();
    MinNeededLength = CalculateMinNeededLineLength();

    LargestLabelLength = CalculateLargestLabelLength();
    LargestElementLength = CalculateLargestElementLength();
}
