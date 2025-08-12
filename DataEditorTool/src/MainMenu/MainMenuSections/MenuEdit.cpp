#include "include.h"
#include "MainMenu/MainMenuSections/MenuEdit.h"

MenuEdit::MenuEdit() : MainMenuSection("Edit", 1)
{

}

void MenuEdit::Tick()
{
	if (ImGui::MenuItem("Undo", "Ctrl+Z", nullptr, CanUndoLastCommand() && IsProjectRootPathSet()))
	{
		UndoLastCommand();
	}

	if (ImGui::MenuItem("Redo", "Ctrl+Y", nullptr, CanRedoLastCommand() && IsProjectRootPathSet()))
	{
		RedoLastCommand();
	}
}

void MenuEdit::CheckShortcuts()
{
	// Undo shortcut (Ctrl+Z)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Z, false) && 
		(ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || 
			ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{
		if (CanUndoLastCommand() && IsProjectRootPathSet())
		{
			UndoLastCommand();
		}
	}

	// Redo shortcut (Ctrl+Y)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Y, false) && 
		(ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || 
			ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{
		if (CanRedoLastCommand() && IsProjectRootPathSet())
		{
			RedoLastCommand();
		}
	}
}

bool MenuEdit::CanUndoLastCommand()
{
	return false;
}

bool MenuEdit::CanRedoLastCommand()
{
	return false;
}

void MenuEdit::UndoLastCommand()
{

}

void MenuEdit::RedoLastCommand()
{

}