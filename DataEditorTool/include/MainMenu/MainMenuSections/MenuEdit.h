#pragma once

#include "MainMenu/MainMenuSections/MainMenuSection.h"

class MenuEdit : public MainMenuSection
{
public:

	MenuEdit();

	virtual void Tick() override;

	virtual void CheckShortcuts() override;

private:

	ImGuiKeyChord UndoShortcut = ImGuiMod_Ctrl | ImGuiKey_Z;

	ImGuiKeyChord RedoShortcut = ImGuiMod_Ctrl | ImGuiKey_Y;

	bool CanUndoLastCommand();

	bool CanRedoLastCommand();

	void UndoLastCommand();

	void RedoLastCommand();
};