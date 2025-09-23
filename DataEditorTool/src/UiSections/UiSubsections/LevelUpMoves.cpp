#include "include.h"

#include "UiSections/UiSubsections/LevelUpMoves.h"
#include "Command/ModifyValue.h"
#include "Command/SwapMoves.h"
#include "Util/FilterableComboBox.h"
#include "Util/ItemSizeUtils.h"
#include "GoD-UI-Windows.h"

LevelUpMovesInfo::LevelUpMovesInfo(OldUiSection* InParent, const std::string& InSubsectionName) : UiSubsection(InParent, InSubsectionName)
{
    MoveItems = GoDUIWindowsInstance::instance.MovesCSV->GetMovesList();

    for (int32_t i = 0; i < 19; i++)
    {
        LevelUpMovesMove.push_back(std::make_shared<std::string>("---"));
        LevelUpMovesLevels.push_back(std::make_shared<int32_t>(-1));
        StringTypedWhileFocused.push_back(std::make_shared<std::string>(""));
    }

    auto PossibleNames = GoDUIWindowsInstance::instance.MovesCSV->GetAllEntriesOfKey("Entry Name", true);

    MaxMoveTextSize = GetMaxTextSize(PossibleNames).first;
}

void LevelUpMovesInfo::UpdateElement()
{
    //ImGui::NewLine();
    //ImGui::Separator();
    //ImGui::Dummy()
    //ImGui::SameLine(60);
    //ImGui::Text("Move");
    //ImGui::SameLine(225); 
    //ImGui::Text("Level");

    // each of the 19 level up level elements are identical
    for (int32_t i = 0; i < 19; i++)
    {
        std::string MoveTextBoxName = std::format("##Move {}", i + 1);
        std::string LevelTextBoxName = std::format("##Level {}", i + 1);
        std::string UpArrowName = std::format("##up {}", i + 1);
        std::string DownArrowName = std::format("##down {}", i + 1);

        // Draw the swap up/down arrow buttons.
        if (i != 0)
        {
            if (ImGui::ArrowButton(UpArrowName.c_str(), ImGuiDir_Up)) { 
                Command::PushNewCommandAndExecute(std::make_shared<SwapMovesCommand>(Parent->shared_from_this(), std::static_pointer_cast<LevelUpMovesInfo>(shared_from_this()), i, i - 1));
            }
        }
        else {
            // Disable the up arrow if this is the top move.
            ImGui::BeginDisabled();
            ImGui::ArrowButton(UpArrowName.c_str(), ImGuiDir_Up);
            ImGui::EndDisabled();
        }

        auto& Style = ImGui::GetStyle();

        ImGui::SameLine(0.0f, Style.ItemSpacing.x);
        if (i != 18)
        {
            if (ImGui::ArrowButton(DownArrowName.c_str(), ImGuiDir_Down)) {
                Command::PushNewCommandAndExecute(std::make_shared<SwapMovesCommand>(Parent->shared_from_this(), std::static_pointer_cast<LevelUpMovesInfo>(shared_from_this()), i, i + 1));
            }
        }
        else
        {
            // Disable the down arrow if this is the bottom move.
            ImGui::BeginDisabled();
            ImGui::ArrowButton(DownArrowName.c_str(), ImGuiDir_Down);
            ImGui::EndDisabled();
        }

        ImGui::SameLine(0.0f, Style.ItemSpacing.x);

        // Calc space between two elements
        float SpaceBetweenTextAndInt = Style.ItemSpacing.x * 2.f;

        // Calc int input textbox size
        
        auto IntInputTextSize = ImGui::CalcTextSize("999").x;
        IntInputTextSize += Style.ItemInnerSpacing.x * 2;

        // Calc int input step buttons
        float ButtonSize = ImGui::GetFrameHeight();
        ButtonSize = (ButtonSize + Style.ItemInnerSpacing.x) * 2.f;

        auto SpaceAvailable = ImGui::GetContentRegionAvail().x;
        float DropdownWidth = SpaceAvailable - SpaceBetweenTextAndInt - IntInputTextSize - ButtonSize - (Style.FramePadding.x);

        float MaxTextboxSize = MaxMoveTextSize;
        MaxTextboxSize += ImGui::GetFrameHeight(); // for dropdown button
        MaxTextboxSize += Style.ItemSpacing.x;
        MaxTextboxSize += Style.FramePadding.x;

        //MaxTextboxSize += Style.ItemInnerSpacing.x;
        //MaxTextboxSize += Style.ItemSpacing.x;
        //MaxTextboxSize += Style.FramePadding.x;

        // Ensure we are never smaller than the min size needed
        if (DropdownWidth < MaxTextboxSize)
        {
            DropdownWidth = MaxTextboxSize;
        }

        ImGui::PushItemWidth(DropdownWidth);

        FilterableComboBox(Parent->shared_from_this(), MoveTextBoxName, MoveItems, LevelUpMovesMove.at(i), StringTypedWhileFocused.at(i));

        ImGui::SameLine(0.0f, SpaceBetweenTextAndInt);
        ImGui::PushItemWidth(IntInputTextSize + ButtonSize);
        const int32_t PrevLevel = *LevelUpMovesLevels.at(i);
        if (ImGui::InputInt(LevelTextBoxName.c_str(), LevelUpMovesLevels.at(i).get()))
        {
            Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), LevelUpMovesLevels.at(i), PrevLevel, *LevelUpMovesLevels.at(i)));
        }
        ImGui::PopItemWidth();
    }
}

void LevelUpMovesInfo::SwapMoves(const int32_t MoveOneIndex, const int32_t MoveTwoIndex)
{
    std::string MoveOneMove = *LevelUpMovesMove.at(MoveOneIndex);
    int32_t MoveOneLevel = *LevelUpMovesLevels.at(MoveOneIndex);

    *LevelUpMovesMove.at(MoveOneIndex) = *LevelUpMovesMove.at(MoveTwoIndex);
    *LevelUpMovesLevels.at(MoveOneIndex) = *LevelUpMovesLevels.at(MoveTwoIndex);

    *LevelUpMovesMove.at(MoveTwoIndex) = MoveOneMove;
    *LevelUpMovesLevels.at(MoveTwoIndex) = MoveOneLevel;
}

void LevelUpMovesInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    for (int32_t i = 0; i < 19; i++)
    {
        std::string BaseString = "Level Up Moves";

        std::string MoveString = "Move";
        std::string LevelString = "Level";

        *LevelUpMovesMove.at(i) = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, std::format("{} {} {}", BaseString, i + 1, MoveString));
        *LevelUpMovesLevels.at(i) = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, std::format("{} {} {}", BaseString, i + 1, LevelString));
    }
}

void LevelUpMovesInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    for (int32_t i = 0; i < 19; i++)
    {
        std::string BaseString = "Level Up Moves";

        std::string MoveString = "Move";
        std::string LevelString = "Level";

        (*PokemonStatsJson)[std::format("{} {} {}", BaseString, i + 1, MoveString)] = *LevelUpMovesMove.at(i);
        (*PokemonStatsJson)[std::format("{} {} {}", BaseString, i + 1, LevelString)] = std::format("{}", *LevelUpMovesLevels.at(i));
    }
}

float LevelUpMovesInfo::CalculateLargestLabelLength() const
{
    // All the labels are the same size
    return 0.f;
}

float LevelUpMovesInfo::CalculateLargestElementLength() const
{
    auto& Style = ImGui::GetStyle();

    // Calc swap arrow button size
    auto ArrowButtonSizex2 = (ImGui::GetFrameHeight() * 2) + (Style.ItemSpacing.x * 2);

    // Calc size of one move text box
    auto PossibleNames = GoDUIWindowsInstance::instance.MovesCSV->GetAllEntriesOfKey("Entry Name", true);

    float MaxTextboxSize = GetMaxTextSize(PossibleNames).first;
    MaxTextboxSize += ImGui::GetFrameHeight(); // for dropdown button
    MaxTextboxSize += Style.ItemSpacing.x * 2;
    MaxTextboxSize += Style.FramePadding.x;

    // Calc space between two elements
    float SpaceBetweenTextAndInt = Style.ItemSpacing.x * 2.f;

    // Calc int input textbox size
    auto IntInputTextSize = GetMaxTextSize<std::array<std::string, 1>>({ "999" }).first;
    IntInputTextSize += Style.ItemInnerSpacing.x * 2;

    // Calc int input step buttons
    float ButtonSize = ImGui::GetFrameHeight();
    ButtonSize = (ButtonSize + Style.ItemInnerSpacing.x) * 2.f;

    return ArrowButtonSizex2 + MaxTextboxSize + SpaceBetweenTextAndInt + IntInputTextSize + ButtonSize + Style.FramePadding.x * 2.f;
}

void LevelUpMovesInfo::OnFontUpdated()
{
    auto PossibleNames = GoDUIWindowsInstance::instance.MovesCSV->GetAllEntriesOfKey("Entry Name", true);
    MaxMoveTextSize = GetMaxTextSize(PossibleNames).first;
}
