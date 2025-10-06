#pragma once

class GLFWwindow;
class ImageAndPixelData;
struct GLFWimage;

class WindowContext
{

public:

	WindowContext() = default;

	void Init();

	void Exit();

	void PollEvents();

	void Tick();

	void BeginRender();

	void EndRender();

	void ShowWindow();

	void MaximizeWindow();

	void CenterWindow();

	void CloseWindow();

	bool IsWindowIconified() const;

	bool IsContextInitialized() const;

	std::shared_ptr<GLFWwindow> GetManagedWindow();

	bool IsWindowMaximized() const;

	static void WindowCloseCallback(GLFWwindow* Window);

private:

	void TrySetWindowIcon();

	std::shared_ptr<ImageAndPixelData> IconImage;

	/** Context init check. */
	bool bInitialized = false;

	/** Window Vars. */
	std::shared_ptr<GLFWwindow> ManagedWindow;
	const ImColor ClearColor = ImColor(38, 38, 38, 255);

	/**
	 * State used to delay showing the window for
	 * a configurable number of ticks on startup.
	 */
	const uint32_t ShowWindowDelayTicks = 2;
	uint32_t CurrentWindowDelay = 0;
	bool bWindowFirstShown = false;

	bool bWindowMaximized = false;

};