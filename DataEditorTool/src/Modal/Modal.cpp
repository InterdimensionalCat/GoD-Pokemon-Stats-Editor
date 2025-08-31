#include "include.h"
#include "Modal/Modal.h"

Modal::Modal(
    const std::string& InModalName, 
    const std::function<void()>& InBypassModalCallback) : 
    ModalName(InModalName), BypassModalCallback(InBypassModalCallback)
{

}

void Modal::Tick()
{
    // First update the popup status no matter what
    switch (PopupStatus)
    {
    case OpenPopupStatus::ShouldOpen:
        ImGui::OpenPopup(GetModalName().c_str());
        OnModalMadeActive();
        PopupStatus = OpenPopupStatus::Active;
        break;
    case OpenPopupStatus::ShouldBypass:
        ImGui::CloseCurrentPopup();

        if (BypassModalCallback)
        {
            BypassModalCallback();
        }

        PopupStatus = OpenPopupStatus::Inactive;
        break;
    case OpenPopupStatus::ShouldClose:
        ImGui::CloseCurrentPopup();
        PopupStatus = OpenPopupStatus::Inactive;
        break;
    default:
        // Do nothing if the status is Active or Inactive
        break;
    }

    if (IsModalActive())
    {
        // Always center modals as they appear
        ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(Center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal(GetModalName().c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            DisplayModal();
            ImGui::EndPopup();
        }
    }
}

void Modal::OnModalMadeActive()
{

}

void Modal::DisplayModal()
{

}

bool Modal::IsModalActive() const
{
    return PopupStatus != OpenPopupStatus::Inactive;
}

std::string Modal::GetModalName() const
{
    return ModalName;
}

void Modal::SetModalStatus(const OpenPopupStatus InStatus)
{
    PopupStatus = InStatus;
}
