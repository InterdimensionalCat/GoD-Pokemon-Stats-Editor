/*****************************************************************//**
 * \file   MenuEdit.h
 * \brief  Main Menu "Edit" section, containing undo/redo functionality.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

#include "MainMenu/MainMenuSections/MainMenuSection.h"

/**
 * \brief  Main Menu "Edit" section, containing undo/redo functionality.
 * 
 * This class implements the "Edit" section of the main menu bar,
 * which contains undo and redo functionality for commands executed
 * in the tool.
 */
class MenuEdit : public MainMenuSection
{
public:

	/** Construct the Main Menu "Edit" section. */
	MenuEdit();

	/** Tick this section, displaying the Undo and Redo actions. */
	virtual void Tick() override;

	/** Check for and handle undo/redo keyboard shortcuts. */
	virtual void CheckShortcuts() override;

private:

	/**
	 * Keyboard shortcut for undoing the last command.
	 * Defaults to Ctrl+Z.
	 */
	ImGuiKeyChord UndoShortcut = ImGuiMod_Ctrl | ImGuiKey_Z;

	/**
	 * Keyboard shortcut for redoing the last undone command.
	 * Defaults to Ctrl+Y.
	 */
	ImGuiKeyChord RedoShortcut = ImGuiMod_Ctrl | ImGuiKey_Y;

	/**
	 * Is the undo command enabled?
	 * This will be true if there is at least one command
	 * that can be undone.
	 * 
	 * \return True if there is at least one command that can be undone, false otherwise.
	 */
	bool CanUndoLastCommand();

	/**
	 * Is the redo command enabled?
	 * This will be true if there is at least one command
	 * that can be redone.
	 * 
	 * \return True if there is at least one command that can be redone, false otherwise.
	 */
	bool CanRedoLastCommand();

	/** Execute the undo action for the last command. */
	void UndoLastCommand();

	/** Execute the redo action for the last undone command. */
	void RedoLastCommand();
};