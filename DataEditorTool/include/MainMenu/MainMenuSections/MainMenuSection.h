/*****************************************************************//**
 * \file   MainMenuSection.h
 * \brief  Base class for sections of the main menu bar.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

/**
 * \brief  Base class for sections of the main menu bar.
 */
class MainMenuSection
{
public:

	/**
	 * Construct a MainMenuSection with the supplied name and priority.
	 * 
	 * \param InSectionName The name of this section, displayed in the main menu bar.
	 * \param InSectionPriority Used to sort sections for displaying. Lower numbers are displayed first.
	 */
	MainMenuSection(const std::string& InSectionName, const uint32_t InSectionPriority);

	/** Tick this MainMenuSection */
	virtual void Tick();

	/** Check for and handle any keyboard shortcuts for this section. */
	virtual void CheckShortcuts();

	/**
	 * Get the name of this section.
	 * 
	 * \return The name of this section, displayed in the main menu bar.
	 */
	std::string GetSectionName() const;

	/**
	 * Get the priority of this section. Used to sort sections for displaying.
	 * 
	 * \return The priority of this section. Lower numbers are displayed first.
	 */
	uint32_t GetSectionPriority() const;

	/**
	 * Is a valid project root path currently set?
	 * 
	 * \return True if a valid project root path is currently set, false otherwise.
	 */
	bool IsProjectRootPathSet() const;

	/**
	 * Returns true if the specified key chord is currently pressed and not routed to a text input.
	 * 
	 * \param KeyChord The key chord to check for.
	 * \return True if the specified key chord is currently pressed and not routed to a text input, false otherwise.
	 */
	bool IsChordPressedAndNotRouted(const ImGuiKeyChord& KeyChord) const;

private:

	/** Name of this section, displayed in the main menu bar. */
	std::string SectionName;

	/** Used to sort sections for displaying. */
	uint32_t SectionPriority = 0;
};
