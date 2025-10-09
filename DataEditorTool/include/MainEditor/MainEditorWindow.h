/*****************************************************************//**
 * \file   MainEditorWindow.h
 * \brief  Manager for all visual elements of the tool, including
 * the window context, GUI context, and UI tabs.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

class MainMenu;
class AppSettings;
class FontManager;
class ModalManager;
class WindowContext;
class GuiContext;
class UiTab;

/**
 * \brief Manager for all visual elements of the tool, including
 * the window context, GUI context, and UI tabs.
 */
class MainEditorWindow
{
public:

	/**
	 * Construct a MainEditorWindow.
	 * This will not be valid for use until Init() is called.
	 */
	MainEditorWindow() = default;

	/**
	 * Initialize the MainEditorWindow and its
	 * WindowContext and GuiContext. This will
	 * create and display the main window.
	 */
	void Init();

	/**
	 * Exit the MainEditorWindow, this will close
	 * the main window and destroy its WindowContext
	 * and GuiContext.
	 */
	void Exit();

	/** Poll events from the window context. */
	void PollEvents();

	/**
	 * This is the primary update function for visuals in the tool.
	 * This will update the UI and window contexts, as well as begin
	 * a new ImGui frame and tick all open UiTabs.
	 * 
	 * The settings and font managers are also ticked here.
	 */
	void Tick();

	/**
	 * Display the created ImGui frame through the window context.
	 */
	void Render();

	/**
	 * Called when a project root path is set.
	 * 
	 * This will open a new PokemonStatsEditor tab.
	 */
	void OnProjectRootPathSet();

	/**
	 * Called when the current project root path is closed.
	 * 
	 * This will close all currently open tabs.
	 */
	void OnProjectRootPathClosed();

	/**
	 * Attempt to open the supplied tab.
	 * 
	 * Opening a tab can fail if one or more
	 * required CSV files for the tab are not
	 * present in the CSV database, or are
	 * unable to be loaded.
	 * 
	 * \param NewTab The tab to open.
	 */
	void OpenNewEditorTab(std::shared_ptr<UiTab> NewTab);

	/**
	 * Set the supplied UiTab as the last tab to receive focus.
	 * 
	 * This is used so that the main menu bar displays tab
	 * specific options for the currently focused tab.
	 * 
	 * \param NewLastFocusedTab The tab to set as the last focused tab.
	 */
	void SatLastFocusedTab(UiTab* NewLastFocusedTab);

	/**
	 * Re-create the UiTab dockspace for this frame and
	 * re-dock every open tab to it.
	 */
	void RefreshTabDocksace();

	/**
	 * Get the GuiContext used by this MainEditorWindow.
	 * 
	 * \return Shared pointer to the GuiContext.
	 */
	std::shared_ptr<GuiContext> GetGuiContext();

	/**
	 * Get the AppSettings used by this MainEditorWindow.
	 * 
	 * \return Shared pointer to the AppSettings.
	 */
	std::shared_ptr<AppSettings> GetSettings();

	/**
	 * Get the FontManager used by this MainEditorWindow.
	 * 
	 * \return Shared pointer to the FontManager.
	 */
	std::shared_ptr<FontManager> GetFontManager();

	/**
	 * Get the ModalManager used by this MainEditorWindow.
	 * 
	 * \return Shared pointer to the ModalManager.
	 */
	std::shared_ptr<ModalManager> GetModalManager();

	/**
	 * Get the current ID of the main dockspace
	 * used for UiTabs.
	 * 
	 * \return The ImGuiID of the main dockspace.
	 */
	ImGuiID GetMainDockspaceId() const;

	/**
	 * Get the last focused tab.
	 * 
	 * Can return nullptr if no tab
	 * has been focused yet, or if the last
	 * focused tab was closed.
	 * 
	 * \return Pointer to the last focused UiTab, or nullptr if none exists.
	 */
	UiTab* GetLastFocusedTab();

	/**
	 * Get the global instance of this MainEditorWindow located
	 * on the global DataEditorInstance.
	 * 
	 * \return Shared pointer to the global MainEditorWindow instance.
	 */
	static std::shared_ptr<MainEditorWindow> Get();

	/**
	 * Called when the user attempts to close the main window.
	 * 
	 * This will check for any open tabs with unsaved changes,
	 * and if any are found, a blocking modal will be opened
	 * to confirm the user wants to close the window and lose
	 * their unsaved changes.
	 */
	static void OnAttemptWindowClose();

private:

	/** Backend Contexts. */
	std::shared_ptr<WindowContext> MainWindowContext;
	std::shared_ptr<GuiContext> MainGuiContext;

	/** Dockspace for Ui tabs. */
	std::shared_ptr<ImGuiWindowClass> MainWindowDockspace;
	ImGuiID MainDockspaceId;

	/** Main menu */
	std::shared_ptr<MainMenu> EditorMainMenu;

	/** Settings, font, and layout */
	std::shared_ptr<AppSettings> MainAppSettings;
	std::shared_ptr<FontManager> MainFontManager;

	/**
	 * Modal manager, this will display a blocking
	 * modal above the main UI in certain cases.
	 */
	std::shared_ptr<ModalManager> MainModalManager;

	/** Currently open tabs. */
	std::vector<std::shared_ptr<UiTab>> EditorTabs;

	/** The last tab to receive focus. */
	UiTab* LastFocusedTab;

	/** Timer to pause UI ticks for a few frames when opening a new tab. */
	int32_t PauseUiTickTimer = 0;
};
