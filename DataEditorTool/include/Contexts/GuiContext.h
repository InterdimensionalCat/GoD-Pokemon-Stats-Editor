#pragma once

class WindowContext;

class GuiContext
{

public:

	GuiContext() = default;

	void Init(std::shared_ptr<WindowContext> MainWindowContext);

	void Exit();

	void BeginTick();

	void EndTick();

	void Render();

	void CreateDeviceObjects();

	void DestroyDeviceObjects();

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
	bool bImplGlfw_ForOpenGL_Initialized = false;
	bool bImpl_OpenGL3_Initialized = false;
};