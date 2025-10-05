#pragma once

#include "MainMenu/MainMenuSections/MainMenuSection.h"

class MenuFile : public MainMenuSection
{
public:

	MenuFile();

	virtual void Tick() override;

	virtual void CheckShortcuts() override;

private:

	ImGuiKeyChord SetRootShortcut = ImGuiMod_Ctrl | ImGuiKey_O;

	ImGuiKeyChord SaveShortcut = ImGuiMod_Ctrl | ImGuiKey_S;

	void SetProjectRootPath();

	void SaveAll();

	void SaveSelected();

	void CloseCurrentRoot();

};