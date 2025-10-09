/*****************************************************************//**
 * \file   MenuView.h
 * \brief  Main menu "View" section, containing font size and layout settings.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once
#include "MainMenu/MainMenuSections/MainMenuSection.h"

class FontManager;
class FontSettings;

/**
 * \brief  Main menu "View" section, containing font size and layout settings.
 */
class MenuView : public MainMenuSection
{
public:

	/** Construct the Main Menu "View" section. */
	MenuView();

	/** Tick this section, displaying font and layout settings. */
	virtual void Tick() override;

	/** Check for and handle keyboard shortcuts for this section. */
	virtual void CheckShortcuts() override;

private:

	/** Update layout settings, called by Tick(). */
	void TickLayoutSettings();

	/** Increase font size shortcut (Ctrl+=) */
	ImGuiKeyChord IncreaseFontShortcut = ImGuiMod_Ctrl | ImGuiKey_Equal;

	/** Decrease font size shortcut (Ctrl+-) */
	ImGuiKeyChord DecreaseFontShortcut = ImGuiMod_Ctrl | ImGuiKey_Minus;

	/** Pointer to the Font Manager on the MainEditorWindow. */
	std::shared_ptr<FontManager> MainFontManager;
};