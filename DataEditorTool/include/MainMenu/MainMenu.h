/*****************************************************************//**
 * \file   MainMenu.h
 * \brief  Main menu bar at the top of the application window.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

class MainMenuSection;

/**
 * \brief  Main menu bar at the top of the application window.
 * 
 * This class manages the main menu bar at the top of the application window.
 * It contains multiple MainMenuSections, each of which can contain multiple
 * menu items. The MainMenu class is responsible for rendering the menu bar
 * and its sections.
 */
class MainMenu
{
public:

	/**
	 * Construct a MainMenu with three sections:
	 * MenuFile: File operations (set project root, saving changes).
	 * MenuEdit: Edit operations (undo/redo).
	 * MenuView: View options (per-tab layout settings, global font settings).
	 */
	MainMenu();

	/**
	 * Tick the main menu, this will check for any pressed
	 * shortcuts, then this will render the menu bar
	 * and all its sections.
	 */
	void Tick();

	/**
	 * Add a new section to the main menu.
	 * Sections will be sorted by their priority.
	 * 
	 * \param InMenuSection The section to add to the main menu.
	 */
	void AddSection(const std::shared_ptr<MainMenuSection>& InMenuSection);

private:

	/** All sections in this main menu, sorted by priority. */
	std::vector<std::shared_ptr<MainMenuSection>> MenuSections;

	// TODO: Add/remove/disable sections based on
	// Currently opened tabs and the currently
	// selected tab
};
