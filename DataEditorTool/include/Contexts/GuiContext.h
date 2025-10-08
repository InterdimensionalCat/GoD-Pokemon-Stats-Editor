/*****************************************************************//**
 * \file   GuiContext.h
 * \brief  Class that encapsulates the ImGui context and its backends.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

class WindowContext;

/**
 * \brief  Class that encapsulates the ImGui context and its backends.
 */
class GuiContext
{

public:

	/**
	 * Construct a GuiContext.
	 * This does not initialize the ImGui context or its backends
	 * until Init() is called.
	 */
	GuiContext() = default;

	/**
	 * Initialize the ImGui context and its backends.
	 * This requires a valid WindowContext to be supplied
	 * so that the GLFW and OpenGL3 backends can be initialized.
	 * 
	 * This will throw if initialization fails.
	 */
	void Init(std::shared_ptr<WindowContext> MainWindowContext);

	/**
	 * Exit the ImGui context and its backends.
	 * This will destroy the ImGui context and its backends
	 * if they were initialized.
	 */
	void Exit();

	/**
	 * Start a new ImGui frame.
	 */
	void BeginTick();

	/**
	 * End the current ImGui frame.
	 */
	void EndTick();

	/**
	 * Render the current ImGui frame.
	 */
	void Render();

	/**
	 * Create all device objects needed for rendering.
	 * This must always be called after we DestroyDeviceObjects.
	 */
	void CreateDeviceObjects();

	/**
	 * Destroy all device objects created for rendering.
	 * This must be called whenever we change fonts.
	 */
	void DestroyDeviceObjects();

	/** Is the ImGui context and its backends fully initialized? */
	bool IsContextInitialized() const;

private:

	/**
	 * Context init checks. ImGui needs to load itself plus 2 backends:
	 * 
	 * 1) GLFW backend for OpenGL (platform backend)
	 * 2) OpenGL3 backend (renderer backend)
	 * 
	 * We need to track initialization for these separately
	 * Since loading for each can fail individually.
	 */
	bool bImGuiContextInitialized = false;

	/** Is the ImGui ImplGLFW for OpenGL backend initialized? */
	bool bImplGlfw_ForOpenGL_Initialized = false;

	/** Is the ImGui ImplOpenGL3 backend initialized? */
	bool bImpl_OpenGL3_Initialized = false;
};