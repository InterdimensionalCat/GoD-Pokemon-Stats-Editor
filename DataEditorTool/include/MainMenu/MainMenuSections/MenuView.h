#pragma once
#include "MainMenu/MainMenuSections/MainMenuSection.h"

class FontManager;
class FontSettings;

class MenuView : public MainMenuSection
{
public:

	MenuView();

	virtual void Tick() override;

	virtual void CheckShortcuts() override;

private:

	ImGuiKeyChord IncreaseFontShortcut = ImGuiMod_Ctrl | ImGuiKey_Equal;

	ImGuiKeyChord DecreaseFontShortcut = ImGuiMod_Ctrl | ImGuiKey_Minus;

	std::shared_ptr<FontManager> MainFontManager;
};