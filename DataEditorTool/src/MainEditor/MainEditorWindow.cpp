#include "include.h"
#include "MainEditor/MainEditorWindow.h"

#include "MainMenu/MainMenu.h"
#include "Settings/AppSettings.h"
#include "Font/FontManager.h"
#include "Modal/ModalManager.h"
#include "Modal/BlockUnsavedProgress.h"
#include "CSV/CSVDatabase.h"
#include "Contexts/WindowContext.h"
#include "Contexts/GuiContext.h"
#include "UI/UiTab.h"
#include "Editors/PokemonStats/PokemonStatsEditor.h"

void MainEditorWindow::Init()
{
    try
    {
        MainWindowContext = std::make_shared<WindowContext>();

        // Try to init the Window context (currently GLFW + GLAD openGL)
        // This will throw if initalization fails.
        MainWindowContext->Init();

        MainGuiContext = std::make_shared<GuiContext>();

        // Try to init the Gui context (currently ImGui with GLFW and OpenGL 3)
        // This requires a valid WindowContext and will throw if initalization fails.
        MainGuiContext->Init(MainWindowContext);
    }
    catch (const std::exception& e)
    {
        ICLogger::Critical("Main Editor initializtaion failed: {}", e.what());
        DataEditorInstance::Get()->Exit();
    }

    // Init settings.
    MainAppSettings = std::make_shared<AppSettings>();
    MainAppSettings->Init();

    // Init font loader, this will find fonts available in the fonts folder.
    MainFontManager = std::make_shared<FontManager>();
    MainFontManager->Init();

    // Init Modal Manager
    MainModalManager = std::make_shared<ModalManager>();

    // Init main menu.
    EditorMainMenu = std::make_shared<MainMenu>();

    // Create top level dockspace for the tool.
    // UiTabs will be docked as tabs in this dockspace
    MainWindowDockspace = std::make_shared<ImGuiWindowClass>();
    MainWindowDockspace->ClassId = ImHashStr("IC_MainWindowDockspace");
    MainWindowDockspace->DockingAllowUnclassed = false;

    // TODO: Add initial tabs?
    // TilesetEditorWindowElement = std::make_shared<TilesetEditorTab>(EditorTabsDockspace);

    // EditorTabs.push_back(TilesetEditorWindowElement);
}

void MainEditorWindow::Exit()
{
    // Update font settings with our current font settings so
    // The same font is displayed the next time we start the program
    MainFontManager->SaveCurrentFontToFontSettings();

    // Shutdown settings, this will save our current settings to a file.
    MainAppSettings->Exit();



    // Terminate the window context and close the window
    if (MainWindowContext != nullptr)
    {
        MainWindowContext->Exit();
    }
}

void MainEditorWindow::PollEvents()
{
    // Events are handled by the Window context.
    MainWindowContext->PollEvents();
}

void MainEditorWindow::Tick()
{
    // Pause ticks for 10 ms if the window is minimized.
    if (MainWindowContext->IsWindowIconified())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        return;
    }
    
    // Tick the window context. This is only needed to determine if we need to
    // Show the window for the first time.
    MainWindowContext->Tick();

    // Check if the font settings have changed since last frame, and if they have
    // load the new current font into memory. This must happen before we begin the
    // new ImGui frame.
    MainFontManager->CheckForFontChanged();

    // Start new ImGui frame. Any ImGui updates run this frame must
    // run after this function.
    MainGuiContext->BeginTick();

    // Set font
    MainFontManager->SetupFontForFrame();

    // Tick Main Menu, this will display the menu sections at the top of the window.
    // This will also check for keyboard shortcuts corresponding to active menu section options.
    EditorMainMenu->Tick();

    //ImGui::ShowDemoWindow();

    // Notifications style setup
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f); // Disable round borders
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f); // Disable borders

    // Notifications color setup
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.10f, 0.10f, 0.10f, 1.00f)); // Background color

    // Main rendering function for notifications
    ImGui::RenderNotifications();

    // Pop notifications style and color.
    ImGui::PopStyleVar(2); // Notification style vars
    ImGui::PopStyleColor(1); // Notification bg color

    // Tick the modal manager, this will tick the active blocking modal if there is any.
    MainModalManager->Tick();

    // Tick all UiWindows directly after this code to ensure they are all in the top level dockspace.
    MainDockspaceId = ImGui::DockSpaceOverViewport(0U, NULL, ImGuiDockNodeFlags_None, MainWindowDockspace.get());

    if(PauseUiTickTimer <= 0)
    {
		for (std::shared_ptr<UiTab> EditorTab : EditorTabs)
		{
			EditorTab->Tick();
		}
	}
    else
    {
		PauseUiTickTimer--;

        if (PauseUiTickTimer < 0)
        {
			PauseUiTickTimer = 0;
        }
    }


    MainFontManager->EndFontForFrame();

    // End the ImGui frame.
    MainGuiContext->EndTick();
}

void MainEditorWindow::Render()
{
    MainWindowContext->BeginRender();

    // Render the updated ImGui graphics to the screen.
    MainGuiContext->Render();

    // Tabs do not handle their own rendering, all the logic for rendering them
    // is set up during the tick function.

    MainWindowContext->EndRender();
}

void MainEditorWindow::OnProjectRootPathSet()
{
    EditorTabs.clear();
    std::shared_ptr<PokemonStatsEditor> StatsEditor = std::make_shared<PokemonStatsEditor>(MainWindowDockspace);
    OpenNewEditorTab(StatsEditor);

    if (!MainWindowContext->IsWindowMaximized() && EditorTabs.size() != 0)
    {
        MainWindowContext->MaximizeWindow();

        // Pause UI ticks for 1 frame to allow window to resize properly.
		PauseUiTickTimer = 1;
    }
}

void MainEditorWindow::OnProjectRootPathClosed()
{
    EditorTabs.clear();
}

void MainEditorWindow::OpenNewEditorTab(std::shared_ptr<UiTab> NewTab)
{
    if (NewTab->LoadRequiredCSVFiles())
    {
        NewTab->Init();
        EditorTabs.push_back(NewTab);
    }
    else
    {
        ICLogger::Warn("Could not open tab {}, some required CSV files could not be loaded.", NewTab->GetName());
    }
}

void MainEditorWindow::SatLastFocusedTab(UiTab* NewLastFocusedTab)
{
    LastFocusedTab = NewLastFocusedTab;
}

void MainEditorWindow::RefreshTabDocksace()
{
    auto DockspaceForTabs = GetMainDockspaceId();

	ImGui::DockBuilderRemoveNode(DockspaceForTabs);
	ImGui::DockBuilderAddNode(DockspaceForTabs);
	ImGui::DockBuilderSetNodeSize(DockspaceForTabs, ImGui::GetMainViewport()->Size);

    for (std::shared_ptr<UiTab> EditorTab : EditorTabs)
    {
        ImGui::DockBuilderDockWindow(EditorTab->GetName().c_str(), DockspaceForTabs);
    }

    ImGui::DockBuilderFinish(DockspaceForTabs);
}

//std::shared_ptr<GLFWwindow> MainEditorWindow::GetWindow()
//{
//    return MainWindowContext->GetManagedWindow();
//}

std::shared_ptr<GuiContext> MainEditorWindow::GetGuiContext()
{
    return MainGuiContext;
}

std::shared_ptr<AppSettings> MainEditorWindow::GetSettings()
{
    return MainAppSettings;
}

std::shared_ptr<FontManager> MainEditorWindow::GetFontManager()
{
    return MainFontManager;
}

std::shared_ptr<ModalManager> MainEditorWindow::GetModalManager()
{
    return MainModalManager;
}

ImGuiID MainEditorWindow::GetMainDockspaceId() const
{
    return MainDockspaceId;
}

UiTab* MainEditorWindow::GetLastFocusedTab()
{
    return LastFocusedTab;
}

std::shared_ptr<MainEditorWindow> MainEditorWindow::Get()
{
    return DataEditorInstance::Get()->GetMainEditorWindow();
}

void MainEditorWindow::OnAttemptWindowClose()
{
    // If we have unsaved progress, block window close and show
    // the unsaved progress modal, otherwise just close the window.
	if (GoDCSV::CSVDatabase::Get()->AreAnyCSVFilesModified())
	{
        auto ModalManager = MainEditorWindow::Get()->GetModalManager();

        std::shared_ptr<BlockUnsavedProgress> Modal = std::make_shared<BlockUnsavedProgress>(
                "Save progress before closing?", 
                std::bind(&WindowContext::CloseWindow, MainEditorWindow::Get()->MainWindowContext)
            );

        ModalManager->SetCurrentlyActiveModal(Modal);
	}
    else
    {
        MainEditorWindow::Get()->MainWindowContext->CloseWindow();
    }
}