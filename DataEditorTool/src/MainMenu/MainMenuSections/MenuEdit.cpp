#include "include.h"
#include "MainMenu/MainMenuSections/MenuEdit.h"
#include "MainEditor/MainEditorWindow.h"
#include "UI/UiTab.h"
#include "UI/TabCSVState.h"

MenuEdit::MenuEdit() : MainMenuSection("Edit", 1)
{

}

void MenuEdit::Tick()
{
	if (ImGui::MenuItem("Undo", ImGui::GetKeyChordName(UndoShortcut), nullptr, CanUndoLastCommand() && IsProjectRootPathSet()))
	{
		UndoLastCommand();
	}

	if (ImGui::MenuItem("Redo", ImGui::GetKeyChordName(RedoShortcut), nullptr, CanRedoLastCommand() && IsProjectRootPathSet()))
	{
		RedoLastCommand();
	}
}

void MenuEdit::CheckShortcuts()
{
	// Undo shortcut (Ctrl+Z)
	if (IsChordPressedAndNotRouted(UndoShortcut))
	{
		if (CanUndoLastCommand() && IsProjectRootPathSet())
		{
			UndoLastCommand();
		}
	}

	// Redo shortcut (Ctrl+Y)
	if (IsChordPressedAndNotRouted(RedoShortcut))
	{
		if (CanRedoLastCommand() && IsProjectRootPathSet())
		{
			RedoLastCommand();
		}
	}
}

bool MenuEdit::CanUndoLastCommand()
{
	auto FocusedTab = MainEditorWindow::Get()->GetLastFocusedTab();

	if (FocusedTab == nullptr)
	{
		return false;
	}

	return FocusedTab->GetTabCSVState()->CanUndo();
}

bool MenuEdit::CanRedoLastCommand()
{
	auto FocusedTab = MainEditorWindow::Get()->GetLastFocusedTab();

	if (FocusedTab == nullptr)
	{
		return false;
	}
	
	return FocusedTab->GetTabCSVState()->CanRedo();
}

void MenuEdit::UndoLastCommand()
{
	auto FocusedTab = MainEditorWindow::Get()->GetLastFocusedTab();

	if (FocusedTab == nullptr)
	{
		ICLogger::Warn("MenuEdit::UndoLastCommand called with no focused tab.");
		return;
	}

	FocusedTab->GetTabCSVState()->Undo();
}

void MenuEdit::RedoLastCommand()
{
	auto FocusedTab = MainEditorWindow::Get()->GetLastFocusedTab();

	if (FocusedTab == nullptr)
	{
		ICLogger::Warn("MenuEdit::RedoLastCommand called with no focused tab.");
		return;
	}

	FocusedTab->GetTabCSVState()->Redo();
}