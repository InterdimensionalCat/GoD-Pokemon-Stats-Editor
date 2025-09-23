#include "include.h"
#include "UI/UiTab.h"
#include "UI/UiSection.h"
#include "imgui/imgui_internal.h"

#include "UI/TabCSVState.h"
#include "CSV/CSVDatabase.h"
#include "CSV/NewCSVData.h"

/** TODO: recalc all sizes in a tab when the tab becomes active or the font type/size changes */

UiTab::UiTab(const std::string& InName, std::shared_ptr<ImGuiWindowClass> InTabDockspace) : 
    UiObject(InName, nullptr),
    TabDockspace(InTabDockspace)
{
    // Create a new SectionDockspace for this tab with a unique identifier.
    SectionDockspace = std::make_shared<ImGuiWindowClass>();
    SectionDockspace->ClassId = ImHashStr(GetName().c_str());
    UiTabID = ImHashStr(std::format("{}##UiTabDockspace", GetName()).c_str());

    TabState = std::make_shared<TabCSVState>(this);
}

void UiTab::Init()
{
    Refresh();
}

void UiTab::Refresh()
{
    for (std::shared_ptr<UiSection> UiSection : UiSections)
    {
        UiSection->Refresh();
    }
}

void UiTab::Tick()
{
    // Ensure Tab state is current
    TabState->Tick();

    // Show a new window for this UiTab.
    ImGui::SetNextWindowClass(TabDockspace.get());

    ImGuiWindowFlags WindowFlags = 0;
    WindowFlags |= ImGuiWindowFlags_NoCollapse;
    WindowFlags |= ImGuiWindowFlags_NoFocusOnAppearing;
    WindowFlags |= ImGuiWindowFlags_HorizontalScrollbar;

    // If any CSV files this tab manages have been marked as modified,
    // set the unsaved progress pip.
    bool bManagedCSVHasBeenModified = false;
    auto CSVDatabase = GoDCSV::CSVDatabase::Get();

    for (const auto& CSVFileName : GetRequiredForEditCSVFiles())
    {
        if (CSVDatabase->GetCSVFile<GoDCSV::NewCSVData>(CSVFileName)->HasCSVFileBeenModified())
        {
            bManagedCSVHasBeenModified = true;
            break;
        }
    }

    if (bManagedCSVHasBeenModified)
    {
        WindowFlags |= ImGuiWindowFlags_UnsavedDocument;
    }

    //auto& Style = ImGui::GetStyle();

    //const ImVec2 MinSize = ImVec2(GetMinNeededWidth() + (Style.WindowPadding.x * 2), 100);
    //const ImVec2 MaxSize = ImVec2(FLT_MAX, FLT_MAX);

    //ImGui::SetNextWindowSizeConstraints(MinSize, MaxSize);

    if (!ImGui::Begin(GetName().c_str(), nullptr, WindowFlags))
    {
        SetTabActive(true);
        ImGui::End();
        return;
    }
    else
    {
        SetTabActive(false);
    }

    // Cover the Section Dockspace over the entire UiTab.
    ImGui::DockSpace(UiTabID, ImVec2(0, 0), 0, SectionDockspace.get());

    ImGui::End();

    // Update each UI section in this window
    for (std::shared_ptr<UiSection> UiSection : UiSections)
    {
        UiSection->Tick();
    }
}

void UiTab::AddSection(const std::shared_ptr<UiSection> NewSection)
{
    UiSections.push_back(NewSection);
}

void UiTab::SetTabActive(const bool InTabActive)
{
    if (InTabActive && !bIsTabActive)
    {
        bIsTabActive = InTabActive;
        TabState->RefreshRow();
    }
    else
    {
        bIsTabActive = InTabActive;
    }
}

bool UiTab::LoadRequiredCSVFiles()
{
    ICLogger::Debug("Attempting to load all CSV files required for Tab {}", GetName());
    std::vector CombinedRequiredCSVFiles = GetRequiredForEditCSVFiles();
    CombinedRequiredCSVFiles.insert(
        CombinedRequiredCSVFiles.end(), 
        GetRequiredForViewingCSVFiles().begin(), 
        GetRequiredForViewingCSVFiles().end()
    );

    // TODO: Refactor this so a modal pops up with all the required files that could not be opened,
    // and the reasons they cannot be opened.
    try
    {
        auto CSVDatabase = GoDCSV::CSVDatabase::Get();

        for (const auto& CSVFileName : CombinedRequiredCSVFiles)
        {

            if (!CSVDatabase->IsCSVFileInDatabase(CSVFileName))
            {
                const std::string ErrorMessage = std::format("Required CSV file {} does not exist.", CSVFileName);
                throw std::exception(ErrorMessage.c_str());
            }

            auto CSVFile = CSVDatabase->GetCSVFile<GoDCSV::NewCSVData>(CSVFileName);
            if (CSVFile->IsCSVFileLoaded())
            {
                ICLogger::Debug("CSV File {} already loaded, skipping", CSVFileName);
            }
            else
            {
                CSVDatabase->LoadCSVFile(CSVFileName);
                if (!CSVFile->IsCSVFileLoaded())
                {
                    const std::string ErrorMessage = std::format("Required CSV file {} could not be loaded.", CSVFileName);
                    throw std::exception(ErrorMessage.c_str());
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        ICLogger::PushErrorNotification("Cannot open Tab", 10000, "Cannot open Tab {}: {}", GetName(), e.what());
        return false;
    }

    return true;
}

std::shared_ptr<TabCSVState> UiTab::GetTabCSVState()
{
    return TabState;
}

const std::vector<std::string>& UiTab::GetRequiredForEditCSVFiles() const
{
    return RequiredForEditCSVFileNames;
}

const std::vector<std::string>& UiTab::GetRequiredForViewingCSVFiles() const
{
    return RequiredForViewingCSVFileNames;
}

std::shared_ptr<ImGuiWindowClass> UiTab::GetSectionDockspace() const
{
    return SectionDockspace;
}