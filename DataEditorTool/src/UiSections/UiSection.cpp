#include "include.h"

#include "UiSections/UiSection.h"
#include "UiSections/UiSubsections/UiSubsection.h"
#include "GoD-UI-Windows.h"

UiSection::UiSection(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize) : WindowName(InWindowName), InitialPos(InPos), InitialSize(InSize), CurrentPokemonIndex(-1)
{
    //const float FontScale = 18.f / 14.f;
    //const ImGuiViewport* MainViewport = ImGui::GetMainViewport();
    //InitialPos = ImVec2((InitialPos.x - MainViewport->WorkPos.x) * FontScale + MainViewport->WorkPos.x, (InitialPos.y - MainViewport->WorkPos.y) * FontScale + MainViewport->WorkPos.y);
    //InitialSize = ImVec2(InitialSize.x * FontScale, InitialSize.y * FontScale);

    const ImGuiViewport* MainViewport = ImGui::GetMainViewport();
    InitialPos = ImVec2(MainViewport->WorkPos.x + InitialPos.x, MainViewport->WorkPos.y + InitialPos.y);
}

void UiSection::Tick()
{
    const ImGuiViewport* MainViewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(InitialPos, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(InitialSize, ImGuiCond_FirstUseEver);

    ImGuiWindowFlags WindowFlags = 0;
    WindowFlags |= ImGuiWindowFlags_NoCollapse;
    WindowFlags |= ImGuiWindowFlags_NoFocusOnAppearing;
    WindowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
    //WindowFlags |= ImGuiWindowFlags_NoMove;

    if (bSetWindowFocused)
    {
        ImGui::SetNextWindowFocus();
        bSetWindowFocused = false;
    }

    if (bUnsavedProgress)
    {
        WindowFlags |= ImGuiWindowFlags_UnsavedDocument;
    }

    auto& Style = ImGui::GetStyle();

    const ImVec2 MinSize = ImVec2(MinNeededLength + (Style.WindowPadding.x * 2), 100);
    const ImVec2 MaxSize = ImVec2(MaxAllowedLength, FLT_MAX);

    ImGui::SetNextWindowSizeConstraints(MinSize, MaxSize);

    if (!ImGui::Begin(WindowName.c_str(), nullptr, WindowFlags))
    {
        ImGui::End();
        return;
    }

    UpdateElement();

    ImGui::End();
}

void UiSection::UpdateElement()
{
    for (auto& Subsection : Subsections)
    {
        if (Subsection != *Subsections.begin())
        {
            auto& Style = ImGui::GetStyle(); 
            ImGui::Dummy(ImVec2(0.0f, Style.ItemSpacing.y * 5));
            ImGui::Separator();
        }
        ImGui::Text(Subsection->GetSubsectionName().c_str());
        Subsection->UpdateElement();
    }
}

void UiSection::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    if (ShouldSave)
    {
        SaveToPokemonStatsJson(GoDUIWindowsInstance::instance.StatsCSV->GetDataObject().at(CurrentPokemonIndex));
    }

    for (auto& Subsection : Subsections)
    {
        Subsection->CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
    }

    CurrentPokemonIndex = NewPokemonIndex;
}

void UiSection::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    for (auto& Subsection : Subsections)
    {
        Subsection->SaveToPokemonStatsJson(PokemonStatsJson);
    }
}

int32_t UiSection::GetCurrentPokemonIndex() const
{
    return CurrentPokemonIndex;
}

void UiSection::SetUnsavedProgress(const bool UnsavedProgress)
{
    bUnsavedProgress = UnsavedProgress;
}

bool UiSection::GetUnsavedProgress() const
{
    return bUnsavedProgress;
}

void UiSection::SetFocusedWindow()
{
    bSetWindowFocused = true;
}

void UiSection::OnFontUpdated()
{
    for (auto& Subsection : Subsections)
    {
        Subsection->OnFontUpdated();
    }
}

float UiSection::CalculateMinNeededLineLength() const
{
    return -1.f;
}

float UiSection::CalculateLargestLabelLength() const
{
    return -1.f;
}

float UiSection::CalculateLargestElementLength() const
{
    return -1.f;
}
