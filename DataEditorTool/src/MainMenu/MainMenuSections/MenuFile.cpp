#include "include.h"
#include "MainMenu/MainMenuSections/MenuFile.h"

MenuFile::MenuFile() : MainMenuSection("File", 0)
{

}

void MenuFile::Tick()
{
	if (ImGui::MenuItem("Set Root Folder", "Ctrl+O"))
	{
		SetProjectRootPath();
	}
	if (ImGui::MenuItem("Save Stats.CSV", "Ctrl+S", nullptr, IsProjectRootPathSet()))
	{
		Save();
	}
	if (ImGui::MenuItem("Close Current Root", "", nullptr, IsProjectRootPathSet()))
	{
		CloseCurrentRoot();
	}
}

void MenuFile::CheckShortcuts()
{
	// Set Project Root shortcut (Ctrl+O)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_O, false) && 
		(ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || 
			ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{
		SetProjectRootPath();
	}

	// Save shortcut (Ctrl+S)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_S, false) && 
		(ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || 
			ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{
		if (IsProjectRootPathSet())
		{
			Save();
		}
	}
}

void MenuFile::SetProjectRootPath()
{

}

void MenuFile::Save()
{

}

void MenuFile::CloseCurrentRoot()
{

}