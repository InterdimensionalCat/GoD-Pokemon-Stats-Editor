/*****************************************************************//**
 * \file   WindowContext.h
 * \brief  Class that encapsulates the GLFW window and OpenGL context for the application.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

class GLFWwindow;
class ImageAndPixelData;
struct GLFWimage;

/**
 * \brief  Class that encapsulates the GLFW window and OpenGL context for the application.
 */
class WindowContext
{

public:

	/**
	 * Construct a WindowContext.
	 * This will not be valid for use until Init() is called.
	 */
	WindowContext() = default;

	/**
	 * Initialize the WindowContext and create the GLFW window and OpenGL context.
	 * This must be called before any other functions on this class, and must be
	 * initialized and valid in order for the Gui Context to be initialized.
	 */
	void Init();

	/**
	 * Exit the WindowContext, this will destroy the GLFW window and OpenGL context.
	 * This will destroy the window context and the window itself.
	 */
	void Exit();

	/** Poll events from the GLFW window. */
	void PollEvents();

	/**
	 * Tick this WindowContext. This is needed in case we want to.
	 * Delay showing the window for a few ticks on startup.
	 */
	void Tick();

	/** Clear the screen and prepare for rendering. */
	void BeginRender();

	/** Render the ImGui frame and swap buffers. */
	void EndRender();

	/** Show the window if it is not already shown. */
	void ShowWindow();

	/** Maximize the window. */
	void MaximizeWindow();

	/** Center the window on the primary monitor. */
	void CenterWindow();

	/** Close the window. */
	void CloseWindow();

	/**
	 * Is the window currently iconified (minimized)?
	 * 
	 * \return True if the window is iconified, false otherwise.
	 */
	bool IsWindowIconified() const;

	/**
	 * Is the OpenGL and GLFW context initialized and valid?
	 * 
	 * \return True if the context is initialized, false otherwise.
	 */
	bool IsContextInitialized() const;

	/**
	 * Get a shared pointer to the managed GLFW window.
	 * Ideally this should only be called inside MainEditorWindow
	 * to encapsulate backend specific classes.
	 * 
	 * \return Shared pointer to the managed GLFW window.
	 */
	std::shared_ptr<GLFWwindow> GetManagedWindow();

	/**
	 * Is the window currently maximized?
	 * 
	 * \return True if the window is maximized, false otherwise.
	 */
	bool IsWindowMaximized() const;

	/**
	 * GLFW callback for when the window is closed.
	 * 
	 * \param Window The GLFW window that was closed.
	 */
	static void WindowCloseCallback(GLFWwindow* Window);

private:

	/** Attempt to load and set the window icon from resources. */
	void TrySetWindowIcon();

	/** Window icon data. */
	std::shared_ptr<ImageAndPixelData> IconImage;

	/** Context init check. */
	bool bInitialized = false;

	/** Managed GLFW window. */
	std::shared_ptr<GLFWwindow> ManagedWindow;

	/** Clear color for the window. */
	const ImColor ClearColor = ImColor(38, 38, 38, 255);

	/**
	 * State used to delay showing the window for
	 * a configurable number of ticks on startup.
	 */
	const uint32_t ShowWindowDelayTicks = 2;

	/** Current delay for showing the window. */
	uint32_t CurrentWindowDelay = 0;

	/** Has the window been shown yet? */
	bool bWindowFirstShown = false;

	/** Is the window currently maximized? */
	bool bWindowMaximized = false;

};