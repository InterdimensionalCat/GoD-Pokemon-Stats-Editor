#include "include.h"

#include "UiSections/EvolutionInfo.h"
#include "Command/ModifyValue.h"
#include "Util/ItemSizeUtils.h"
#include "Util/FilterableComboBox.h"
#include "GoD-UI-Windows.h"

EvolutionInfo::EvolutionInfo(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize) : OldUiSection(InWindowName, InPos, InSize)
{
    for (int32_t i = 0; i < 5; i++)
    {
        MethodFilterStrings.push_back(std::make_shared<std::string>(""));
        FormFilterStrings.push_back(std::make_shared<std::string>(""));
        ConditionFilterStrings.push_back(std::make_shared<std::string>(""));

        EvolutionMethods.push_back(std::make_shared<std::string>("---"));
        EvolutionConditions.push_back(std::make_shared<std::string>("---"));
        EvolutionForms.push_back(std::make_shared<std::string>("---"));

        EvolutionConditionInts.push_back(std::make_shared<int32_t>(-1));
        EvolutionConditionItems.push_back(std::make_shared<std::string>("---"));
    }

    PokemonListFormatted = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey("Entry Name", true);

    EvolutionItemsListItems = GoDUIWindowsInstance::instance.ItemsCSV->GetItemsList();

    EvolutionStonesList.push_back(EvolutionItemsListItems.at(93));
    EvolutionStonesList.push_back(EvolutionItemsListItems.at(94));
    EvolutionStonesList.push_back(EvolutionItemsListItems.at(95));
    EvolutionStonesList.push_back(EvolutionItemsListItems.at(96));
    EvolutionStonesList.push_back(EvolutionItemsListItems.at(97));
    EvolutionStonesList.push_back(EvolutionItemsListItems.at(98));

    // Get all unique evolution methods
    // The methods go from 0 - 16 (inclusive) but 2, 3, and 13 are never used
    EvolutionMethodsList = std::vector<std::string>(17, "---");

    for (int32_t i = 0; i < 4; i++)
    {
        std::string EvolutionMethodKey = std::format("Evolutions {} Evolution Method", i + 1);
        auto AllEvolutionMethodEntries = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey(EvolutionMethodKey, false);
        for (auto& Method : AllEvolutionMethodEntries)
        {
            auto MethodInArrItr = std::find(EvolutionMethodsList.begin(), EvolutionMethodsList.end(), Method);
            if (MethodInArrItr == EvolutionMethodsList.end())
            {
                auto FirstParenth = Method.find_last_of("(");
                auto SecondParenth = Method.find_last_of(")");
                auto MethodSubstr = Method.substr(FirstParenth + 1, SecondParenth - (FirstParenth + 1));

                EvolutionMethodsList.at(stoi(MethodSubstr)) = Method;
            }
        }
    }

    EvolutionMethodsList.at(2) = "Happiness (Day) (2)";
    EvolutionMethodsList.at(3) = "Happiness (Night) (3)";
    EvolutionMethodsList.at(13) = "Ninjask evolution method (13)";

    // Evolution methods list:
    // None (0): No evolution,                                             Param: Always 0
    // Max Happiness (1): Evolves when happiness is maxed,                 Param: Always 0
    // Happiness (Day) (2): Unimplemented, used for Espeon in RSE,         Param: Always 0
    // Happiness (Night) (3): Unimplemented, used for Umbreon in RSE,      Param: Always 0
    // Level Up (4): Evolves when the level is reached,                    Param: The level needed to evolve
    // Trade (5): Evolves when traded,                                     Param: Always 0
    // Trade With Item (6): Evoles when traded with an item,               Param: The ID of the item needed to evolve
    // Evolution Stone (7): Evolves when exposed to its evolution stone,   Param: The item ID of the needed stone
    // Atk > Def (8): Evolves at the specified level if Atk > Def,         Param: The level needed to evolve
    // Atk = Def (9): Evolves at the specified level if Atk = Def,         Param: The level needed to evolve
    // Atk < Def (10): Evolves at the specified level if Atk < Def,        Param: The level needed to evolve
    // Silcoon evolution method (11): Evolves based on PID at the level,   Param: The level needed to evolve
    // Cascoon evolution method (12): Evolves based on PID at the level,   Param: The level needed to evolve
    // Ninjask evolution method (13): Unimplemented, for Ninjask in RSE,   Param: The level needed to evolve
    // Shedinja evolution method (14): Shedinja appears at this level,     Param: The level needed to evolve
    // Max Beauty (15): Evolves when Beauty is raised to the param value,  Param: The beauty value needed to evolve
    // Level Up With Key Item (16): Used to evolve Espeon/Umbreon,         Param: 516 for Espeon, 517 for Umbreon.

    // Fill the key items list, and modify their ids (add 150)
    for (int32_t i = 0; i < 20; i++)
    {
        auto KeyItem = EvolutionItemsListItems.at(350 + i);

        auto FirstParenth = KeyItem.find_last_of("(");
        auto SecondParenth = KeyItem.find_last_of(")");
        auto KeyItemBaseSubstr = KeyItem.substr(0, FirstParenth);
        auto KeyItemIntSubstr = KeyItem.substr(FirstParenth + 1, SecondParenth - (FirstParenth + 1));
        auto NewIntValue = std::format("{}({})", KeyItemBaseSubstr, stoi(KeyItemIntSubstr) + 150);

        KeyItemsList.push_back(NewIntValue);
    }

    // there are multiple labels on each line, so we will need to add all of them up
    for (int32_t i = 0; i < 5; i++)
    {
        std::string MethodLabel = std::format("Method {}", i + 1);
        std::string FormLabel = std::format("Form {}", i + 1);
        std::string ConditionLabel = std::format("Condition {}", i + 1);

        MaxMethodLabelLength = std::max(MaxMethodLabelLength, ImGui::CalcTextSize(MethodLabel.c_str()).x);
        MaxFormLabelLength = std::max(MaxFormLabelLength, ImGui::CalcTextSize(FormLabel.c_str()).x);
        MaxConditionLabelLength = std::max(MaxConditionLabelLength, ImGui::CalcTextSize(ConditionLabel.c_str()).x);
    }

    MinNeededLength = CalculateMinNeededLineLength();

    LargestLabelLength = CalculateLargestLabelLength();
    LargestElementLength = CalculateLargestElementLength();

    auto& Style = ImGui::GetStyle();

    MethodBoxSize = GetMaxTextSize(EvolutionMethodsList).first;

    MethodBoxSize += ImGui::GetFrameHeight(); // for dropdown button
    MethodBoxSize += Style.ItemSpacing.x * 2;
    MethodBoxSize += Style.FramePadding.x;

    // The condition box will need to be the biggest when it is an item dropdown
    ConditionBoxSize = GetMaxTextSize(EvolutionItemsListItems).first;

    ConditionBoxSize += ImGui::GetFrameHeight(); // for dropdown button
    ConditionBoxSize += Style.ItemSpacing.x * 2;
    ConditionBoxSize += Style.FramePadding.x;

    // Calc form input textbox size
    FormInputTextSize = -1.f;

    for (int32_t i = 0; i < 5; i++)
    {
        std::string FormKey = std::format("Evolutions {} Evolved Form", i + 1);
        auto PossibleForms = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey(FormKey, false);
        FormInputTextSize = std::max(FormInputTextSize, GetMaxTextSize(PossibleForms).first);
    }


    FormInputTextSize += Style.ItemInnerSpacing.x * 2 + Style.ItemSpacing.x * 2;
}

void EvolutionInfo::UpdateElement()
{
    auto& Style = ImGui::GetStyle();
    auto SpaceAvailable = ImGui::GetContentRegionAvail().x - (Style.FramePadding.x * 2);
    float ExtraMethodSpace = 0.f;
    float ExtraFormSpace = 0.f;
    float ExtraConditionSpace = 0.f;
    if (SpaceAvailable > MinNeededLength)
    {
        auto FreeSpace = SpaceAvailable - MinNeededLength ;
        ExtraMethodSpace = std::floor(FreeSpace * 0.5f);
        ExtraFormSpace = std::floor(FreeSpace * 0.25f);
        ExtraConditionSpace = std::floor(FreeSpace * 0.25f);
    }

    // Calc method box size
    //auto MethodBoxSize = GetMaxTextSize(EvolutionMethodsList).first;

    //MethodBoxSize += ImGui::GetFrameHeight(); // for dropdown button
    //MethodBoxSize += Style.ItemSpacing.x * 2;
    //MethodBoxSize += Style.FramePadding.x;

    // Calc space between each element.
    float SpaceBetweenElements = Style.ItemSpacing.x * 2.f;

    // Calc form input textbox size

    //auto FormInputTextSize = -1.f;

    //for (int32_t i = 0; i < 5; i++)
    //{
    //    std::string FormKey = std::format("Evolutions {} Evolved Form", i + 1);
    //    auto PossibleForms = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey(FormKey, false);
    //    FormInputTextSize = std::max(FormInputTextSize, GetMaxTextSize(PossibleForms).first);
    //}


    //FormInputTextSize += Style.ItemInnerSpacing.x * 2 + Style.ItemSpacing.x * 2;

    // The condition box will need to be the biggest when it is an item dropdown
    //float MaxTextboxTextSize = GetMaxTextSize(EvolutionItemsListItems).first;

    //MaxTextboxTextSize += ImGui::GetFrameHeight(); // for dropdown button
    //MaxTextboxTextSize += Style.ItemSpacing.x * 2;
    //MaxTextboxTextSize += Style.FramePadding.x;

    for (int32_t i = 0; i < 5; i++)
    {
        std::string EvolutionMethodStr = std::format("Method {}", i + 1);
        std::string EvolutionFormStr = std::format("Form {}", i + 1);
        std::string EvolutionConditionStr = std::format("Condition {}", i + 1);

        ImGui::PushItemWidth(MethodBoxSize + ExtraMethodSpace);
        FilterableComboBox(shared_from_this(), EvolutionMethodStr.c_str(), EvolutionMethodsList, EvolutionMethods.at(i), MethodFilterStrings.at(i));
        ImGui::PopItemWidth();

        ImGui::SameLine(0.0f, SpaceBetweenElements);
        ImGui::PushItemWidth(FormInputTextSize + ExtraFormSpace);
        //ImGui::InputText(EvolutionFormStr.c_str(), &EvolutionForms.at(i));

        FilterableComboBox(shared_from_this(), EvolutionFormStr.c_str(), PokemonListFormatted, EvolutionForms.at(i), FormFilterStrings.at(i));
        ImGui::PopItemWidth();

        ImGui::SameLine(0.0f, SpaceBetweenElements);
        ImGui::PushItemWidth(ConditionBoxSize + ExtraConditionSpace);

        switch (GetIntFromFormattedEntry(*EvolutionMethods.at(i)))
        {

        case 4:  // Level up
            UpdateConditionAsLevel(i);
            break;
        case 6:  // Trade With Item
            UpdateConditionAsItem(i);
            break;
        case 7:  // Evolution Stone
            UpdateConditionAsEvolutionStone(i);
            break;
        case 8:  // Atk > Def
        case 9:  // Atk = Def
        case 10: // Atk < Def
        case 11: // Silcoon evolution method
        case 12: // Cascoon evolution method
        case 13: // Ninjask evolution method (unimplemented)
        case 14: // Shedinja evolution method
        case 15: // Max Beauty
            // cases 8-14 use the condition as an evolution level
            // Although the param for case 15 is technically the beauty needed to evolve, the level logic will handle this correctly
            UpdateConditionAsLevel(i);
            break;
        case 16: // Level Up With Key Item
            UpdateConditionAsKeyItem(i);
            break;
        default:     
            // Each case not covered by the above logic does not use the Evolution condition.
            static std::string DummyText = "0 (0x0)";
            ImGui::BeginDisabled();
            ImGui::InputText(EvolutionConditionStr.c_str(), &DummyText);
            ImGui::EndDisabled();
        }
    }
}

void EvolutionInfo::UpdateConditionAsLevel(const int32_t i)
{
    std::string EvolutionConditionStr = std::format("Condition {}", i + 1);

    // Set the level as an int, but convert it to a hex value in the underlying string data.
    const int32_t PrevConditionInt = *EvolutionConditionInts.at(i);
    if (ImGui::InputInt(EvolutionConditionStr.c_str(), EvolutionConditionInts.at(i).get()))
    {
        //Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(shared_from_this(), EvolutionConditionInts.at(i), PrevConditionInt, *EvolutionConditionInts.at(i)));
        (*EvolutionConditions.at(i)) = std::format("{:x}", (*EvolutionConditionInts.at(i)));
        std::transform(EvolutionConditions.at(i)->begin(), EvolutionConditions.at(i)->end(), EvolutionConditions.at(i)->begin(), ::toupper);
        (*EvolutionConditions.at(i)) = std::format("{} (0x{})", (*EvolutionConditionInts.at(i)), (*EvolutionConditions.at(i)));
    }
}

void EvolutionInfo::UpdateConditionAsItem(const int32_t i)
{
    std::string EvolutionConditionStr = std::format("Condition {}", i + 1);

    int32_t ConditionIndex = stoi(EvolutionConditions.at(i)->substr(0, EvolutionConditions.at(i)->find(" ")));
    std::string ConditionItem = *EvolutionConditionItems.at(i);
    if (ConditionItem != "---")
    {
        if (ConditionIndex != GetIntFromFormattedEntry(ConditionItem))
        {
            ConditionIndex = GetIntFromFormattedEntry(ConditionItem);
        }
    }

    // Show Items as a filterable combo box.
    if (!FilterableComboBox(shared_from_this(), EvolutionConditionStr.c_str(), EvolutionItemsListItems, EvolutionConditionItems.at(i), ConditionFilterStrings.at(i)))
    {
        if (ConditionIndex >= 500)
        {
            // If >= 500, this was a key item using the other item index
            ConditionIndex -= 150;
        }
        (*EvolutionConditionItems.at(i)) = EvolutionItemsListItems.at(ConditionIndex);
    }
    else {
        int32_t ConditionValue = GetIntFromFormattedEntry(*EvolutionConditionItems.at(i));

        (*EvolutionConditions.at(i)) = std::format("{:x}", ConditionValue);
        std::transform(EvolutionConditions.at(i)->begin(), EvolutionConditions.at(i)->end(), EvolutionConditions.at(i)->begin(), ::toupper);
        (*EvolutionConditions.at(i)) = std::format("{} (0x{})", ConditionValue, (*EvolutionConditions.at(i)));
    }
}

void EvolutionInfo::UpdateConditionAsEvolutionStone(const int32_t i)
{
    std::string EvolutionConditionStr = std::format("Condition {}", i + 1);

    int32_t ConditionIndex = stoi(EvolutionConditions.at(i)->substr(0, EvolutionConditions.at(i)->find(" ")));
    std::string ConditionItem = *EvolutionConditionItems.at(i);
    if (ConditionItem != "---")
    {
        if (ConditionIndex != GetIntFromFormattedEntry(ConditionItem))
        {
            ConditionIndex = GetIntFromFormattedEntry(ConditionItem);
        }
    }

    // Show Items as a filterable combo box.
    if (!FilterableComboBox(shared_from_this(), EvolutionConditionStr.c_str(), EvolutionStonesList, EvolutionConditionItems.at(i), ConditionFilterStrings.at(i)))
    {
        if (ConditionIndex < 93 || ConditionIndex > 98)
        {
            // If out of evol. stone range, set to the first stone
            ConditionIndex = 93;
        }
        (*EvolutionConditionItems.at(i)) = EvolutionItemsListItems.at(ConditionIndex);
    }
    else {
        int32_t ConditionValue = GetIntFromFormattedEntry(*EvolutionConditionItems.at(i));

        (*EvolutionConditions.at(i)) = std::format("{:x}", ConditionValue);
        std::transform(EvolutionConditions.at(i)->begin(), EvolutionConditions.at(i)->end(), EvolutionConditions.at(i)->begin(), ::toupper);
        (*EvolutionConditions.at(i)) = std::format("{} (0x{})", ConditionValue, (*EvolutionConditions.at(i)));
    }
}

void EvolutionInfo::UpdateConditionAsKeyItem(const int32_t i)
{
    std::string EvolutionConditionStr = std::format("Condition {}", i + 1);

    int32_t ConditionIndex = stoi(EvolutionConditions.at(i)->substr(0, EvolutionConditions.at(i)->find(" ")));
    std::string ConditionItem = *EvolutionConditionItems.at(i);
    if (ConditionItem != "---")
    {
        if (ConditionIndex != GetIntFromFormattedEntry(ConditionItem))
        {
            ConditionIndex = GetIntFromFormattedEntry(ConditionItem);
        }
    }

    // Show Items as a filterable combo box.
    if (!FilterableComboBox(shared_from_this(), EvolutionConditionStr.c_str(), KeyItemsList, EvolutionConditionItems.at(i), ConditionFilterStrings.at(i)))
    {
        (*EvolutionConditionItems.at(i)) = KeyItemsList.at(std::max(0, ConditionIndex - 500));
    }
    else {
        int32_t ConditionValue = GetIntFromFormattedEntry(*EvolutionConditionItems.at(i));

        (*EvolutionConditions.at(i)) = std::format("{:x}", ConditionValue);
        std::transform(EvolutionConditions.at(i)->begin(), EvolutionConditions.at(i)->end(), EvolutionConditions.at(i)->begin(), ::toupper);
        (*EvolutionConditions.at(i)) = std::format("{} (0x{})", ConditionValue, (*EvolutionConditions.at(i)));
    }
}

void EvolutionInfo::SaveLevelCondition(std::shared_ptr<nlohmann::json> PokemonStatsJson, const int32_t i)
{
    std::string EvolutionConditionKey = std::format("Evolutions {} Evolution Condition", i + 1);

    (*EvolutionConditions.at(i)) = std::format("{:x}", (*EvolutionConditionInts.at(i)));
    std::transform(EvolutionConditions.at(i)->begin(), EvolutionConditions.at(i)->end(), EvolutionConditions.at(i)->begin(), ::toupper);
    (*EvolutionConditions.at(i)) = std::format("{} (0x{})", (*EvolutionConditionInts.at(i)), (*EvolutionConditions.at(i)));

    (*PokemonStatsJson)[EvolutionConditionKey] = (*EvolutionConditions.at(i));
}

void EvolutionInfo::SaveItemCondition(std::shared_ptr<nlohmann::json> PokemonStatsJson, const int32_t i)
{
    std::string EvolutionConditionKey = std::format("Evolutions {} Evolution Condition", i + 1);

    int32_t ConditionValue = GetIntFromFormattedEntry(*EvolutionConditionItems.at(i));

    (*EvolutionConditions.at(i)) = std::format("{:x}", ConditionValue);
    std::transform(EvolutionConditions.at(i)->begin(), EvolutionConditions.at(i)->end(), EvolutionConditions.at(i)->begin(), ::toupper);
    (*EvolutionConditions.at(i)) = std::format("{} (0x{})", ConditionValue, (*EvolutionConditions.at(i)));
    std::cout << EvolutionConditions.at(i) << "\n";

    (*PokemonStatsJson)[EvolutionConditionKey] = *EvolutionConditions.at(i);
}

void EvolutionInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    OldUiSection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
    for (int32_t i = 0; i < 5; i++)
    {
        std::string EvolutionMethodKey = std::format("Evolutions {} Evolution Method", i + 1);
        std::string EvolutionConditionKey = std::format("Evolutions {} Evolution Condition", i + 1);
        std::string EvolutionFormKey = std::format("Evolutions {} Evolved Form", i + 1);
        *EvolutionMethods.at(i) = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, EvolutionMethodKey);
        *EvolutionConditions.at(i) = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, EvolutionConditionKey);
        *EvolutionForms.at(i) = GoDUIWindowsInstance::instance.StatsCSV->GetStringAtKeyAndIndex(NewPokemonIndex, EvolutionFormKey);

        // Give Condition Items and Condition Ints a default value so that they don't cause crashes
        *EvolutionConditionItems.at(i) = EvolutionItemsListItems.at(0);
        *EvolutionConditionInts.at(i) = 0;

        // Must update level int if the method is an int method

        // TODO: UPDATE TO INCLUDE SETTING EVOLUTION CONDITION ITEMS
        int32_t ConditionIntValue = stoi((*EvolutionConditions.at(i)).substr(0, (*EvolutionConditions.at(i)).find(" ")));
        switch (GetIntFromFormattedEntry(*EvolutionMethods.at(i)))
        {
        case 4:  // Level up
            *EvolutionConditionInts.at(i) = ConditionIntValue;
            break;
        case 6:  // Trade With Item
        case 7:  // Evolution Stone
            *EvolutionConditionItems.at(i) = EvolutionItemsListItems.at(ConditionIntValue);
            break;
        case 8:  // Atk > Def
        case 9:  // Atk = Def
        case 10: // Atk < Def
        case 11: // Silcoon evolution method
        case 12: // Cascoon evolution method
        case 13: // Ninjask evolution method
        case 14: // Shedinja evolution method
        case 15: // Max Beauty
            *EvolutionConditionInts.at(i) = ConditionIntValue;
            break;
        case 16: // Level Up With Key Item
            *EvolutionConditionItems.at(i) = KeyItemsList.at(ConditionIntValue - 500);
            break;
        default:
            break;
        }
    }
}

void EvolutionInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    for (int32_t i = 0; i < 5; i++)
    {
        std::string EvolutionMethodKey = std::format("Evolutions {} Evolution Method", i + 1);
        std::string EvolutionConditionKey = std::format("Evolutions {} Evolution Condition", i + 1);
        std::string EvolutionFormKey = std::format("Evolutions {} Evolved Form", i + 1);

        (*PokemonStatsJson)[EvolutionMethodKey] = *EvolutionMethods.at(i);
        (*PokemonStatsJson)[EvolutionFormKey] = *EvolutionForms.at(i);

        // Saving is more complicated for the evolution condition, as it depends on what the method is.
        switch (GetIntFromFormattedEntry(*EvolutionMethods.at(i)))
        {
        case 4:  // Level up
            SaveLevelCondition(PokemonStatsJson, i);
            break;
        case 6:  // Trade With Item
            SaveItemCondition(PokemonStatsJson, i);
            break;
        case 7:  // Evolution Stone
            SaveItemCondition(PokemonStatsJson, i);
            break;
        case 8:  // Atk > Def
        case 9:  // Atk = Def
        case 10: // Atk < Def
        case 11: // Silcoon evolution method
        case 12: // Cascoon evolution method
        case 13: // Ninjask evolution method
        case 14: // Shedinja evolution method
        case 15: // Max Beauty
            // Although the param here is technically the beauty needed to evolve, the level logic will handle this correctly
            SaveLevelCondition(PokemonStatsJson, i);
            break;
        case 16: // Level Up With Key Item
            // This logic will work correctly even though the Key item id is +150 compared to the normal id.
            SaveItemCondition(PokemonStatsJson, i);
            break;
        default:
            // Each case not covered by the above logic does not use the Evolution condition.
            std::string DummyText = "0 (0x0)";
            (*PokemonStatsJson)[EvolutionConditionKey] = DummyText;
        }
    }
}

int32_t EvolutionInfo::GetIntFromFormattedEntry(const std::string& Entry)
{
    auto FirstParenth = Entry.find_last_of("(");
    auto SecondParenth = Entry.find_last_of(")");
    auto Substr = Entry.substr(FirstParenth + 1, SecondParenth - (FirstParenth + 1));

    int32_t RetVal = (int32_t)stoi(Substr);
    return RetVal;
}

float EvolutionInfo::CalculateMinNeededLineLength() const
{
    float MaxLabelLength = CalculateLargestLabelLength() + MaxConditionLabelLength + MaxFormLabelLength + MaxMethodLabelLength;
    float MaxElementLength = CalculateLargestElementLength();

    return MaxLabelLength + MaxElementLength;
}

float EvolutionInfo::CalculateLargestLabelLength() const
{
    // There are multiple labels on each line, so returning something here will not be helpful
    return 0.f;
}

float EvolutionInfo::CalculateLargestElementLength() const
{
    // Each row has a method box, method label, form box, form label, condition box, and condition label
    auto& Style = ImGui::GetStyle();

    // Calc method box size
    auto MethodBoxSize = GetMaxTextSize(EvolutionMethodsList).first;

    MethodBoxSize += ImGui::GetFrameHeight(); // for dropdown button
    MethodBoxSize += Style.ItemSpacing.x * 2;
    MethodBoxSize += Style.FramePadding.x;

    // Calc space between each element.
    float SpaceBetweenElements = Style.ItemSpacing.x * 2.f;

    // Calc form input textbox size

    auto FormInputTextSize = -1.f;

    for (int32_t i = 0; i < 5; i++)
    {
        std::string FormKey = std::format("Evolutions {} Evolved Form", i + 1);
        auto PossibleForms = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey(FormKey, false);
        FormInputTextSize = std::max(FormInputTextSize, GetMaxTextSize(PossibleForms).first);
    }


    FormInputTextSize += Style.ItemInnerSpacing.x * 2 + Style.ItemSpacing.x * 2;

    // The condition box will need to be the biggest when it is an item dropdown

    float MaxTextboxTextSize = GetMaxTextSize(EvolutionItemsListItems).first;

    MaxTextboxTextSize += ImGui::GetFrameHeight(); // for dropdown button
    MaxTextboxTextSize += Style.ItemSpacing.x * 2;
    MaxTextboxTextSize += Style.FramePadding.x;

    return MethodBoxSize + (SpaceBetweenElements * 2.f) + FormInputTextSize + MaxTextboxTextSize + (Style.FramePadding.x * 2.f);
}

void EvolutionInfo::OnFontUpdated()
{
    OldUiSection::OnFontUpdated();

    MaxMethodLabelLength = -1;
    MaxFormLabelLength = -1;
    MaxConditionLabelLength = -1;
    // there are multiple labels on each line, so we will need to add all of them up
    for (int32_t i = 0; i < 5; i++)
    {
        std::string MethodLabel = std::format("Method {}", i + 1);
        std::string FormLabel = std::format("Form {}", i + 1);
        std::string ConditionLabel = std::format("Condition {}", i + 1);

        MaxMethodLabelLength = std::max(MaxMethodLabelLength, ImGui::CalcTextSize(MethodLabel.c_str()).x);
        MaxFormLabelLength = std::max(MaxFormLabelLength, ImGui::CalcTextSize(FormLabel.c_str()).x);
        MaxConditionLabelLength = std::max(MaxConditionLabelLength, ImGui::CalcTextSize(ConditionLabel.c_str()).x);
    }

    MinNeededLength = CalculateMinNeededLineLength();

    LargestLabelLength = CalculateLargestLabelLength();
    LargestElementLength = CalculateLargestElementLength();

    auto& Style = ImGui::GetStyle();

    MethodBoxSize = GetMaxTextSize(EvolutionMethodsList).first;

    MethodBoxSize += ImGui::GetFrameHeight(); // for dropdown button
    MethodBoxSize += Style.ItemSpacing.x * 2;
    MethodBoxSize += Style.FramePadding.x;

    // The condition box will need to be the biggest when it is an item dropdown
    ConditionBoxSize = GetMaxTextSize(EvolutionItemsListItems).first;

    ConditionBoxSize += ImGui::GetFrameHeight(); // for dropdown button
    ConditionBoxSize += Style.ItemSpacing.x * 2;
    ConditionBoxSize += Style.FramePadding.x;

    // Calc form input textbox size
    FormInputTextSize = -1.f;

    for (int32_t i = 0; i < 5; i++)
    {
        std::string FormKey = std::format("Evolutions {} Evolved Form", i + 1);
        auto PossibleForms = GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey(FormKey, false);
        FormInputTextSize = std::max(FormInputTextSize, GetMaxTextSize(PossibleForms).first);
    }


    FormInputTextSize += Style.ItemInnerSpacing.x * 2 + Style.ItemSpacing.x * 2;
}
