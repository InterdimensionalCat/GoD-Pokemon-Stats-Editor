#include "include.h"
#include "Contexts/WindowContext.h"

#include "MainEditor/MainEditorWindow.h"
#include "Util/TextureLoader.h"

// GLFW backend includes. Ideally these should not be included outside of
// Context cpp files.
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// ImGui backend includes. Ideally these should not be included outside of
// Context cpp files.
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void WindowContext::Init()
{
    try
    {
        if (!glfwInit())
        {
            // Initialization failed, throw error.
            throw std::exception("GLFW Initialization failed!");
        }
        else
        {
            bInitialized = true;
        }
        int MajorVersion;
        int MinorVersion;
        int Revision;
        glfwGetVersion(&MajorVersion, &MinorVersion, &Revision);
        ICLogger::Debug("Successfully loaded GLFW version {}.{}.{}", MajorVersion, MinorVersion, Revision);

        // Start with a hidden window so we can draw over it and spawn the window without a white flash
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        // Create the Main window
        ManagedWindow.reset(glfwCreateWindow(1600, 900, "GoD Data Editor Tool", NULL, NULL), &glfwDestroyWindow);
        if (ManagedWindow == nullptr)
        {
            throw std::exception("Main window creation failed.");
        }

        // Maximize the window
        // This now happens when we set a project root
        // glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_TRUE);

        // Set the window icon if it can be found
        // This is still needed because the cmake
        // code that sets the executables icon
        // does not cause it to show up in
        // the banner/toolbar
        TrySetWindowIcon();

        // Make window context current
        glfwMakeContextCurrent(ManagedWindow.get());

        // Load GLAD
        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
        {
            throw std::exception("GLAD loading failed.");
        }

        auto GLVersion = glGetString(GL_VERSION);
        std::string GLVersionString = std::string((const char*)GLVersion);

        // TODO: show openGL and glad version here (if possible) (glad version = 0.1.36)
        ICLogger::Debug("Successfully loaded OpenGL version {} using GLAD version {}", GLVersionString, "0.1.36");

        // Set the window close callback to the Main Editor's attempt window close function.
        // This will allow us to block the user from closing a window if there is unsaved progress.
        glfwSetWindowCloseCallback(ManagedWindow.get(), WindowCloseCallback);
    }
    catch (const std::exception& e)
    {
        // Undo initalization if anything above failed.
        Exit();
        throw e;
    }

    // Render 2 clear frames before showing the window to prevent a white flash when the program starts.
    // 2 frames are needed to clear both buffers.
    // May no longer be needed due to the window delay code below

    for (uint32_t i = 0; i < 2; i++)
    {
        BeginRender();
        EndRender();
    }

    // Center the window before we show it.
    CenterWindow();

	ICLogger::Debug("Window context successfully initialized.");
}

void WindowContext::Exit()
{
    // Terminate GLFW and close the GLFW window
    if (IsContextInitialized())
    {
        ManagedWindow.reset();
        glfwTerminate();
        bInitialized = false;
    }
}

void WindowContext::PollEvents()
{
    // Poll GLFW events.
    glfwPollEvents();
}

void WindowContext::Tick()
{
    // We hide the window for a few ticks on startup before showing to avoid
    // The white flash that happens if we don't render anything to it first.
    if (!glfwGetWindowAttrib(ManagedWindow.get(), GLFW_VISIBLE) && !bWindowFirstShown)
    {
        CurrentWindowDelay++;
        if (CurrentWindowDelay >= ShowWindowDelayTicks)
        {
            CurrentWindowDelay = ShowWindowDelayTicks;
            ShowWindow();
            bWindowFirstShown = true;
        }
    }
}

void WindowContext::BeginRender()
{
    // Clear framebuffer
    glClearColor(
        ClearColor.Value.x,
        ClearColor.Value.y,
        ClearColor.Value.z,
        ClearColor.Value.w
    );
}

void WindowContext::EndRender()
{
    // Swap buffers
    glfwSwapBuffers(ManagedWindow.get());
}

void WindowContext::ShowWindow()
{
    glfwShowWindow(ManagedWindow.get());
}

void WindowContext::MaximizeWindow()
{
    // Maximize the window
    glfwMaximizeWindow(ManagedWindow.get());
	bWindowMaximized = true;
    //glfwSetWindowAttrib(ManagedWindow.get(), GLFW_MAXIMIZED, GLFW_TRUE);
}

void WindowContext::CenterWindow()
{
    int WindowWidth = 0;
    int WindowHeight = 0;
    glfwGetWindowSize(ManagedWindow.get(), &WindowWidth, &WindowHeight);

    GLFWmonitor* CurrentMonitor = glfwGetWindowMonitor(ManagedWindow.get());

    if (CurrentMonitor == nullptr) {
        CurrentMonitor = glfwGetPrimaryMonitor();
    }

    int MonitorPosX = 0;
    int MonitorPosY = 0;
    int MonitorWidth = 0;
    int MonitorHeight = 0;

    glfwGetMonitorWorkarea(CurrentMonitor, &MonitorPosX, &MonitorPosY, &MonitorWidth, &MonitorHeight);

    int CenterX = MonitorPosX + (MonitorWidth - WindowWidth) / 2;
    int CenterY = MonitorPosY + (MonitorHeight - WindowHeight) / 2;

    glfwSetWindowPos(ManagedWindow.get(), CenterX, CenterY);
}

void WindowContext::CloseWindow()
{
    // glfwSetWindowShouldClose does not actually close the window,
    // it only sets a hint that other parts of the program might read.
    // Stopping the DataEditorInstance will actually close the window,
    // as it will destroy the ManagedWindow pointer when this context
    // exits.
    glfwSetWindowShouldClose(ManagedWindow.get(), GLFW_TRUE);
    DataEditorInstance::Get()->Stop();
}

bool WindowContext::IsWindowIconified() const
{
    return glfwGetWindowAttrib(ManagedWindow.get(), GLFW_ICONIFIED);
}

bool WindowContext::IsContextInitialized() const
{
    return bInitialized;
}

std::shared_ptr<GLFWwindow> WindowContext::GetManagedWindow()
{
    return ManagedWindow;
}

bool WindowContext::IsWindowMaximized() const
{
    return bWindowMaximized;
}

void WindowContext::WindowCloseCallback(GLFWwindow* Window)
{
    MainEditorWindow::Get()->OnAttemptWindowClose();
}

void WindowContext::TrySetWindowIcon()
{
    // TODO: set the exe's from the .ico file
    // built into the executable.
    try
    {
        ICLogger::Debug("Attempting to load window icon.");
        // Attempt to find the Pokeface resource dir, which should be at
        // "{ToolPath}/Resources/PokeFace/"
        std::filesystem::path BasePath = std::filesystem::current_path();
        BasePath /= "Resources";

        if (!std::filesystem::is_directory(BasePath))
        {
            // If the Pokeface directory is not found throw an error
            std::string ErrorMessage = std::format("{} is not a directory", BasePath.string());
            throw std::exception(ErrorMessage.c_str());
            return;
        }

        // Icon file name.
        const std::string IconName = "Icon.png";


        std::filesystem::path PathToIcon = BasePath / IconName;
        if (!std::filesystem::exists(PathToIcon))
        {
            // If the Icon file doesn't exist, throw an error and stop loading
            std::string ErrorMessage = std::format("Icon file {} not found", IconName);
            throw std::exception(ErrorMessage.c_str());
            return;
        }

        // Attempt to load the icon image file, its Width/Height will be stored in the supplied
        // Width and height variables.
        IconImage = LoadImageFromFile(PathToIcon.string().c_str());
        if (IconImage != nullptr)
        {
            ICLogger::Debug("Successfully loaded Icon {}", IconName);
        }
        else
        {
            std::string ErrorMessage = std::format("Error loading icon image {}, is this a valid image file?", IconName);
            throw std::exception(ErrorMessage.c_str());
            return;
        }

        glfwSetWindowIcon(ManagedWindow.get(), 1, IconImage.get()->ImageData.get());
        ICLogger::Debug("Successfully loaded window icon!");
    }
    catch (const std::exception& e)
    {
        IconImage.reset();
        ICLogger::Error("Window icon loading failed: {}", e.what());
    }
}
