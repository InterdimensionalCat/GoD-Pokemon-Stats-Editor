#include "UnsavedProgressModal.h"
#include "GoD-UI-Windows.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

UnsavedProgressModal::UnsavedProgressModal(const bool InCloseWindow, const std::string& InPopupMsg) : bCloseWindow(InCloseWindow), PopupMsg(InPopupMsg)
{

}

void UnsavedProgressModal::Tick()
{
    std::string popupText = bCloseWindow ? "Warning: Unsaved Progress##0" : "Warning: Unsaved Progress##1";
    if (bEnabled)
    {
        ImGui::OpenPopup(popupText.c_str());
        bEnabled = false;
    }

    //ImGui::TextWrapped("Modal windows are like popups but the user cannot close them by clicking outside.");

    //if (ImGui::Button("Delete.."))
    //    ImGui::OpenPopup("Delete?");

    // Always center this window when appearing
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal(popupText.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text(PopupMsg.c_str());
        float BothButtonSize = ImGui::GetItemRectSize().x;
        ImGui::Separator();

        std::string SaveText = bCloseWindow ? "Save##0" : "Save##1";

        if (ImGui::Button(SaveText.c_str(), ImVec2(BothButtonSize / 2.f, 0))) {
            bool bSaveSuccessful = GoDUIWindowsInstance::instance.Save();
            if (bSaveSuccessful)
            {
                SetBypassModal(true);
                if (bCloseWindow)
                {
                    glfwSetWindowShouldClose(GoDUIWindowsInstance::instance.window, GLFW_TRUE);
                }
                else 
                {
                    GoDUIWindowsInstance::instance.SetProjectRootPath();
                }

                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::SameLine();
        std::string DontSaveText = bCloseWindow ? "Don't Save##0" : "Don't Save##1";
        if (ImGui::Button(DontSaveText.c_str(), ImVec2(BothButtonSize / 2.f, 0))) {
            SetBypassModal(true);
            if (bCloseWindow)
            {
                glfwSetWindowShouldClose(GoDUIWindowsInstance::instance.window, GLFW_TRUE);
            }
            else
            {
                GoDUIWindowsInstance::instance.SetProjectRootPath();
            }
            ImGui::CloseCurrentPopup();
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        std::string CancelText = bCloseWindow ? "Cancel##0" : "Cancel##1";
        if (ImGui::Button(CancelText.c_str(), ImVec2(BothButtonSize / 2.f, 0))) {
            ImGui::CloseCurrentPopup(); 
        }
        ImGui::EndPopup();
    }
}

bool UnsavedProgressModal::GetEnabled() const
{
	return bEnabled;
}

void UnsavedProgressModal::SetEnabled(const bool InEnabled)
{
	bEnabled = InEnabled;
}

bool UnsavedProgressModal::GetBypassModal() const
{
    return bBypassModal;
}

void UnsavedProgressModal::SetBypassModal(const bool InBypassModal)
{
    bBypassModal = InBypassModal;
}
