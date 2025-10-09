/*****************************************************************//**
 * \file   MenuFile.h
 * \brief  Main Menu "File" section, containing options for setting/closing the project root path,
 * and saving CSV files.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

#include "MainMenu/MainMenuSections/MainMenuSection.h"

/**
 * \brief  Main Menu "File" section, containing options for setting/closing the project root path,
 * and saving CSV files.
 */
class MenuFile : public MainMenuSection
{
public:

	/** Construct the Main Menu "File" section. */
	MenuFile();

	/** Tick this section, displaying project root and save actions. */
	virtual void Tick() override;

	/** Check for and handle keyboard shortcuts for this section. */
	virtual void CheckShortcuts() override;

private:

	/** Shortcut to set the project root path (Ctrl+O) */
	ImGuiKeyChord SetRootShortcut = ImGuiMod_Ctrl | ImGuiKey_O;

	/** Shortcut to save all modified CSV files (Ctrl+S) */
	ImGuiKeyChord SaveShortcut = ImGuiMod_Ctrl | ImGuiKey_S;

	/** Open the SetProjectRootPath dialog through the ProjectRoot manager. */
	void SetProjectRootPath();

	/** Save all modified CSV files through the CSVDatabase. */
	void SaveAll();

	/** Open a modal that allows the user to select specific CSV files to save. */
	void SaveSelected();

	/** Close the current project root through the ProjectRoot manager. */
	void CloseCurrentRoot();
};