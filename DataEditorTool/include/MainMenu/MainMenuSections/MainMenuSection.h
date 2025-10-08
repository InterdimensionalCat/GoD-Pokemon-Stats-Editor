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

	/** Construct a MainMenuSection with the supplied name and priority. */
	MainMenuSection(const std::string& InSectionName, const uint32_t InSectionPriority);

	/** Tick this MainMenuSection */
	virtual void Tick();

	/** Check for and handle any keyboard shortcuts for this section. */
	virtual void CheckShortcuts();

	/** Get the name of this section. */
	std::string GetSectionName() const;

	/** Get the priority of this section. Used to sort sections for displaying. */
	uint32_t GetSectionPriority() const;

	/** Is a valid project root path currently set? */
	bool IsProjectRootPathSet() const;

	/** Returns true if the specified key chord is currently pressed and not routed to a text input. */
	bool IsChordPressedAndNotRouted(const ImGuiKeyChord& KeyChord) const;

private:

	/** Name of this section, displayed in the main menu bar. */
	std::string SectionName;

	/** Used to sort sections for displaying. */
	uint32_t SectionPriority = 0;
};
