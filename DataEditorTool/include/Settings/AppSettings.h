/*****************************************************************//**
 * \file   Settings.h
 * \brief  Global application settings manager. Contains pointers to all settings sections.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

class FontSettings;
class LayoutSettings;
class SettingsSection;

/**
 * \brief  Global application settings manager. Contains pointers to all settings sections.
 * 
 * This class is in charge of initializing and exiting all settings sections,
 * as well as loading and saving settings to a JSON file.
 * 
 * Individual settings sections are responsible for loading and saving
 * their own settings to/from a JSON object passed to them by this class.
 */
class AppSettings 
{
public:

	/**
	 * Construct an AppSettings manager.
	 * This will not be valid for use until Init() is called.
	 */
	AppSettings();

	/**
	 * Initialize all settings sections and load settings from the JSON file.
	 * If the JSON file does not exist or is malformed, settings will be
	 * initialized from default values instead.
	 */
	void Init();

	/**
	 * Exit all settings sections and save settings to the JSON file.
	 * 
	 * If settings saving fails we will attempt to dump the settings
	 * json to the log, which will allow users to recover their settings
	 */
	void Exit();

	/**
	 * Load settings from the JSON file into each settings section.
	 */
	void InitSettingsFromJson();

	/**
	 * Initialize settings from default values in each settings section.
	 */
	void InitSettingsFromDefaults();

	/**
	 * Save settings from each settings section to the JSON file.
	 */
	void SaveSettingsToJson();

	/**
	 * Add a new settings section to the manager.
	 * 
	 * \param NewSection The new settings section to add.
	 */
	void AddSection(const std::shared_ptr<SettingsSection> NewSection);

	/**
	 * Get the FontSettings section.
	 * This will throw if the FontSettings section has not been added.
	 * 
	 * \return A shared pointer to the FontSettings section.
	 */
	std::shared_ptr<FontSettings> GetFontSettings();

	/**
	 * Get the LayoutSettings section for the specified tab name.
	 * This will return a nullptr if a LayoutSettings section with the specified
	 * tab name has not been added.
	 * 
	 * \param InTabName The name of the tab to get the LayoutSettings for.
	 * \return A shared pointer to the LayoutSettings section for the specified tab name, or nullptr if it does not exist.
	 */
	std::shared_ptr<LayoutSettings> GetLayoutSettingsForTab(const std::string& InTabName);

private:

	/**
	 * Get the settings section with the specified name.
	 * This will return a nullptr if a section with the specified
	 * name has not been added.
	 * 
	 * \param SectionName The name of the section to get.
	 * \return A shared pointer to the settings section with the specified name, or nullptr if it does not exist.
	 */
	std::shared_ptr<SettingsSection> GetSectionByName(const std::string& SectionName);

	/**
	 * Contains the saved values for all settings sections.
	 * Individual JSON objects are passed into each section for saving/loading.
	 */
	nlohmann::ordered_json SettingsJson;

	/** Map of settings section name to settings section pointer. */
	std::map<std::string, std::shared_ptr<SettingsSection>> SettingsSections;
};
