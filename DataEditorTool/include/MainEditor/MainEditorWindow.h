/*****************************************************************//**
 * \file   MainEditorWindow.h
 * \brief  
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

class MainEditorWindow
{
public:

	MainEditorWindow() = default;

	void Init();

	void Exit();

	void PollEvents();

	void Tick();

	void Render();

	void OnProjectRootPathSet();

	void OpenNewEditorTab(std::shared_ptr<UiTab> NewTab);

	/** We should try to avoid exposing raw backend structures outside their context objects. */
	// std::shared_ptr<GLFWwindow> GetWindow();

	std::shared_ptr<GuiContext> GetGuiContext();

	std::shared_ptr<AppSettings> GetSettings();

	std::shared_ptr<FontManager> GetFontManager();

	std::shared_ptr<ModalManager> GetModalManager();

	static std::shared_ptr<MainEditorWindow> Get();

	static void OnAttemptWindowClose();

private:

	/** Backend Contexts. */
	std::shared_ptr<WindowContext> MainWindowContext;
	std::shared_ptr<GuiContext> MainGuiContext;

	/** Dockspace for Ui tabs. */
	std::shared_ptr<ImGuiWindowClass> MainWindowDockspace;

	/** Main menu */
	std::shared_ptr<MainMenu> EditorMainMenu;

	/** Settings, font, and layout */
	std::shared_ptr<AppSettings> MainAppSettings;
	std::shared_ptr<FontManager> MainFontManager;

	std::shared_ptr<ModalManager> MainModalManager;

	/** Backend Init checks. */
	bool GLFWInitialized = false;
	bool ImGuiGLFWInitialized = false;
	bool ImGuiOpenGLInitialized = false;

	/** Currently open tabs. */
	std::vector<std::shared_ptr<UiTab>> EditorTabs;

	//IcColor ClearColor;

	//std::shared_ptr<SDL_Window> Window;

	//std::shared_ptr<SDL_Renderer> Renderer;

	//std::vector<std::shared_ptr<UiTab>> EditorTabs;

	//std::shared_ptr<TilesetEditorTab> TilesetEditorWindowElement;

	//std::shared_ptr<ImGuiWindowClass> EditorTabsDockspace;
};
