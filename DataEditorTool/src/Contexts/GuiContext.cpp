#include "include.h"
#include "Contexts/GuiContext.h"
#include "Contexts/WindowContext.h"

// GLFW backend includes. Ideally these should not be included outside of
// Context cpp files.
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

void GuiContext::Init(std::shared_ptr<WindowContext> MainWindowContext)
{
    try
    {
        // Setup Dear ImGui context.
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        bImGuiContextInitialized = true;

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends for ImGui

        // Init the platform backend (Currently GLFW with OpenGL)
        // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
        bImplGlfw_ForOpenGL_Initialized = ImGui_ImplGlfw_InitForOpenGL(MainWindowContext->GetManagedWindow().get(), true);
        if (!bImplGlfw_ForOpenGL_Initialized)
        {
            // Throw
            throw std::exception("ImGui GLFW impl initiailzation failed.");
        }

        // Init the renderer backend (Currently OpenGL3)
        bImpl_OpenGL3_Initialized = ImGui_ImplOpenGL3_Init();
        if (!bImpl_OpenGL3_Initialized)
        {
            throw std::exception("ImGui OpenGL impl initialization failed.");
        }

		// Space between two elements inside a single item.
        // ImGui::GetStyle().ItemInnerSpacing.x = 100.f;
  
        // Space on either side of the inside content of an item and its border.
		//ImGui::GetStyle().FramePadding.x = 100.f;

        // Space between the window border and its content on either side.
        // ImGui::GetStyle().WindowPadding.x = 100.f;

        ICLogger::Debug(
            "Successfully loaded ImGui version {} with platform backend {} and renderer backend {}",
            IMGUI_VERSION, 
            "Impl Glfw For OpenGL",
            "Impl OpenGL3"
        );
    }
    catch (const std::exception& e)
    {
        Exit();
        throw e;
    }
}

void GuiContext::Exit()
{
    // Shutdown the ImGui renderer backend.
    if (bImpl_OpenGL3_Initialized)
    {
        ImGui_ImplOpenGL3_Shutdown();
        bImpl_OpenGL3_Initialized = false;
    }

    // Shutdown the ImGui platform backend
    if (bImplGlfw_ForOpenGL_Initialized)
    {
        ImGui_ImplGlfw_Shutdown();
        bImplGlfw_ForOpenGL_Initialized = false;
    }

    // Destory the ImGui context itself.
    if (bImGuiContextInitialized)
    {
        ImGui::DestroyContext();
        bImGuiContextInitialized = false;
    }
}

void GuiContext::BeginTick()
{
    // Prepare backends for a new ImGui frame.
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    // Start new ImGui frame.
    ImGui::NewFrame();

    static bool bShownImGuiDebugInfo = false;

    if (!bShownImGuiDebugInfo)
    {
        const auto& Style = ImGui::GetStyle();
        ICLogger::Debug("ImGui FramePadding:      (x: {}, y: {})", Style.FramePadding.x, Style.FramePadding.y);
        ICLogger::Debug("ImGui ItemSpacing:       (x: {}, y: {})", Style.ItemSpacing.x, Style.ItemSpacing.y);
        ICLogger::Debug("ImGui ItemInnerSpacing:  (x: {}, y: {})", Style.ItemInnerSpacing.x, Style.ItemInnerSpacing.y);
        bShownImGuiDebugInfo = true;
    }
}

void GuiContext::EndTick()
{
    // End the ImGui frame. Backends do not need to end their frames.
    ImGui::EndFrame();
}

void GuiContext::Render()
{
    // Imgui Rendering. Only the renderer backend needs to
    // render data.
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool GuiContext::IsContextInitialized() const
{
    // Context is only initialized if ImGui and
    // All of its backends have been initialized successfully
    return
        bImGuiContextInitialized &&
        bImplGlfw_ForOpenGL_Initialized &&
        bImpl_OpenGL3_Initialized;
}

void GuiContext::CreateDeviceObjects()
{
    ImGui_ImplOpenGL3_CreateDeviceObjects();
}

void GuiContext::DestroyDeviceObjects()
{
    ImGui_ImplOpenGL3_DestroyDeviceObjects();
}
