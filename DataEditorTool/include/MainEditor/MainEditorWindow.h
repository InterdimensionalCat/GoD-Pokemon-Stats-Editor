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

class MainEditorWindow
{
public:

	MainEditorWindow() = default;

	void Init();

	void Exit();

	void PollEvents();

	void Tick();

	void Render();

	std::shared_ptr<GLFWwindow> GetWindow();

	std::shared_ptr<AppSettings> GetSettings();

	std::shared_ptr<FontManager> GetFontManager();

private:

	void CenterWindow();

	static void OnAttemptWindowClose(GLFWwindow* window);

	ImColor ClearColor = ImColor(38, 38, 38, 255);

	/** Window classes */
	std::shared_ptr<GLFWwindow> Window;
	std::shared_ptr<ImGuiWindowClass> MainWindowDockspace;

	/** Main menu */
	std::shared_ptr<MainMenu> EditorMainMenu;

	/** Settings, font, and layout */
	std::shared_ptr<AppSettings> MainAppSettings;
	std::shared_ptr<FontManager> MainFontManager;

	/** Backend Init checks. */
	bool GLFWInitialized = false;
	bool ImGuiGLFWInitialized = false;
	bool ImGuiOpenGLInitialized = false;

	//IcColor ClearColor;

	//std::shared_ptr<SDL_Window> Window;

	//std::shared_ptr<SDL_Renderer> Renderer;

	//std::vector<std::shared_ptr<UiTab>> EditorTabs;

	//std::shared_ptr<TilesetEditorTab> TilesetEditorWindowElement;

	//std::shared_ptr<ImGuiWindowClass> EditorTabsDockspace;
};
