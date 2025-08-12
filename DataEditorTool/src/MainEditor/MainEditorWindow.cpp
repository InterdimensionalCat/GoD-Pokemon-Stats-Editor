#include "include.h"
#include "MainEditor/MainEditorWindow.h"

#include "MainMenu/MainMenu.h"
#include "Settings/AppSettings.h"
#include "Font/FontManager.h"

void MainEditorWindow::Init()
{
    // Try init GLFW.
    try
    {
        if (!glfwInit())
        {
            // Initialization failed, throw error.
            throw std::exception("GLFW Initialization failed!");
        }
        else
        {
            GLFWInitialized = true;
        }

        // Start with a hidden window so we can draw over it and spawn the window without a white flash
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        // Create the Main window
        Window.reset(glfwCreateWindow(1600, 900, "GoD Data Editor Tool", NULL, NULL), &glfwDestroyWindow);
        if (Window == nullptr)
        {
            throw std::exception("Main window creation failed.");
        }

        // Maximize the window
        // glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_TRUE);

        // Make window context current
        glfwMakeContextCurrent(Window.get());

        // Load GLAD
        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
        {
            throw std::exception("GLAD loading failed.");
        }
        else

        glfwSetWindowCloseCallback(Window.get(), MainEditorWindow::OnAttemptWindowClose);

        // Setup Dear ImGui context.
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends for ImGUI
        // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
        if (!ImGui_ImplGlfw_InitForOpenGL(Window.get(), true))
        {
            throw std::exception("ImGui GLFW impl initiailzation failed.");
        }
        else
        {
            ImGuiGLFWInitialized = true;
        }

        if (!ImGui_ImplOpenGL3_Init())
        {
            throw std::exception("ImGui OpenGL impl initialization failed.");
        }
        else
        {
            ImGuiOpenGLInitialized = true;
        }

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

    // Init main menu.
    EditorMainMenu = std::make_shared<MainMenu>();

    // Create top level dockspace for the tool.
    // UiTabs will be docked as tabs in this dockspace
    MainWindowDockspace = std::make_shared<ImGuiWindowClass>();
    MainWindowDockspace->ClassId = ImHashStr("IC_MainWindowDockspace");
    MainWindowDockspace->DockingAllowUnclassed = false;

    // Add initial tabs?
    // TilesetEditorWindowElement = std::make_shared<TilesetEditorTab>(EditorTabsDockspace);

    // EditorTabs.push_back(TilesetEditorWindowElement);

    // Render 2 clear frames before showing the window to prevent a white flash when the program starts.
    // 2 frames are needed to clear both buffers.

    for (uint32_t i = 0; i < 2; i++)
    {
        // Set the screen color to the Clear Color
        glClearColor(
            ClearColor.Value.x,
            ClearColor.Value.y,
            ClearColor.Value.z,
            ClearColor.Value.w
        );

        // Swap buffers
        glfwSwapBuffers(Window.get());
    }

    // Center the window before we show it.
    CenterWindow();

    // Show the window.
    glfwShowWindow(Window.get());
}

void MainEditorWindow::Exit()
{
    // Shutdown settings, this will save our current settings to a file.
    MainAppSettings->Exit();

    // Shutdown ImGui and its backend/platform
    if (ImGuiOpenGLInitialized)
    {
        ImGui_ImplOpenGL3_Shutdown();
    }

    if (ImGuiGLFWInitialized)
    {
        ImGui_ImplGlfw_Shutdown();
    }

    // Destory ImGUI context
    if (ImGuiGLFWInitialized)
    {
        ImGui::DestroyContext();
    }

    // Destroy GLFW window
    Window.reset();

    // Exit GLFW
    if (GLFWInitialized)
    {
        glfwTerminate();
    }
}

void MainEditorWindow::PollEvents()
{
    // Poll GLFW events.
    glfwPollEvents();
}

void MainEditorWindow::Tick()
{
    // Pause ticks for 10 ms if the window is minimized.
    if (glfwGetWindowAttrib(Window.get(), GLFW_ICONIFIED))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        return;
    }

    // Check if the font settings have changed since last frame, and if they have
    // load the new current font into memory. This must happen before we begin the
    // new ImGui frame.
    MainFontManager->CheckForFontChanged();

    // Start new ImGui frame.
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Set font
    MainFontManager->SetupFontForFrame();

    // TODO: tick blocking modals...

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

    // Tick all UiWindows directly after this code to ensure they are all in the top level dockspace.
    ImGui::DockSpaceOverViewport(0U, NULL, ImGuiDockNodeFlags_None, MainWindowDockspace.get());

    //for (std::shared_ptr<UiTab> EditorTab : EditorTabs)
    //{
    //    EditorTab->Tick();
    //}

    MainFontManager->EndFontForFrame();
    ImGui::EndFrame();
}

void MainEditorWindow::Render()
{

    // Clear framebuffer
    glClearColor(
        ClearColor.Value.x,
        ClearColor.Value.y,
        ClearColor.Value.z,
        ClearColor.Value.w
    );

    // Imgui Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    // Tabs do not handle their own rendering, all the logic for rendering them
    // is set up during the tick function.

    // Swap buffers
    glfwSwapBuffers(Window.get());
}

std::shared_ptr<GLFWwindow> MainEditorWindow::GetWindow()
{
    return Window;
}

std::shared_ptr<AppSettings> MainEditorWindow::GetSettings()
{
    return MainAppSettings;
}

std::shared_ptr<FontManager> MainEditorWindow::GetFontManager()
{
    return MainFontManager;
}

void MainEditorWindow::CenterWindow()
{
    int WindowWidth = 0;
    int WindowHeight = 0;
    glfwGetWindowSize(Window.get(), &WindowWidth, &WindowHeight);

    GLFWmonitor* CurrentMonitor = glfwGetWindowMonitor(Window.get());

    if (CurrentMonitor == nullptr) {
        CurrentMonitor = glfwGetPrimaryMonitor();
    }

    int MonitorPosX = 0;
    int MonitorPosY = 0;
    int MonitorWidth = 0;
    int MonitorHeight = 0;

    glfwGetMonitorWorkarea(CurrentMonitor, &MonitorPosX, &MonitorPosY, &MonitorWidth, &MonitorHeight);

    int CenterX = MonitorPosX + (MonitorWidth  -  WindowWidth) / 2;
    int CenterY = MonitorPosY + (MonitorHeight - WindowHeight) / 2;

    glfwSetWindowPos(Window.get(), CenterX, CenterY);
}

void MainEditorWindow::OnAttemptWindowClose(GLFWwindow* window)
{
    // Right now, just close the window, later an unsaved progress modal will block
    // Window close unless we hit don't save
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    DataEditorInstance::Get()->Stop();


    //auto& instance = GoDUIWindowsInstance::instance;

    //bool bUnsavedProgress = false;

    //for (auto& section : instance.UiElements)
    //{
    //    if (section->GetUnsavedProgress())
    //    {
    //        bUnsavedProgress = true;
    //    }
    //}

    //if (bUnsavedProgress && !instance.UnsavedProgressBlocker->GetBypassModal())
    //{
    //    instance.UnsavedProgressBlocker->SetEnabled(true);
    //    glfwSetWindowShouldClose(window, GLFW_FALSE);
    //}
    //else
    //{
    //    instance.UnsavedProgressBlocker->SetBypassModal(false);
    //}
}
