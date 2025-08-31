/*****************************************************************//**
 * \file   Settings.h
 * \brief  
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

// AppSettings contains pointers to all the settings sections, and is in charge of init/exiting all of them.
// Load default settings will load each section with pre-determined default values.

class FontSettings;
class LayoutSettings;
class SettingsSection;

class AppSettings 
{
public:

	AppSettings();

	void Init();

	void Exit();

	void InitSettingsFromJson();

	void InitSettingsFromDefaults();

	void SaveSettingsToJson();

	std::shared_ptr<FontSettings> GetFontSettings();

	std::shared_ptr<LayoutSettings> GetLayoutSettings();

private:

	void AddSection(const std::shared_ptr<SettingsSection> NewSection);

	std::shared_ptr<SettingsSection> GetSectionByName(const std::string& SectionName);

	/**
	 * Contains the saved values for all settings sections.
	 * Individual JSON objects are passed into each section for saving/loading.
	 */
	nlohmann::ordered_json SettingsJson;

	std::map<std::string, std::shared_ptr<SettingsSection>> SettingsSections;
};
