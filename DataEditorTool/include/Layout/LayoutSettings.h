/*****************************************************************//**
 * \file   LayoutSettings.h
 * \brief  Per-tab layout settings, including the last loaded preset layout file
 * and whether or not to reload the preset on startup.
 * 
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "Settings/SettingsSection/SettingsSection.h"
#include "Settings/AppSetting.h"
#include "Util/JsonHelpers.h"


/**
 * \brief  Per-tab layout settings, including the last loaded preset layout file
 * and whether or not to reload the preset on startup.
 * 
 * Each time a UiTab is opened, we check the currently loaded settings
 * for a LayoutSettingsn object with a matching tab name. If none exist,
 * a new LayoutSettings is created for that tab with default settings.
 */
class LayoutSettings : public SettingsSection
{
public:

	/**
	 * Construct a LayoutSettings section with the supplied tab name.
	 * This tab name should match the name of the UiTab that this
	 * LayoutSettings object is intended to store settings for.
	 * 
	 * \param InTabName The name of the tab that this LayoutSettings object stores settings for.
	 */
	LayoutSettings(const std::string& InTabName);

	/**
	 * Initialize this settings section from the supplied JSON object.
	 * 
	 * \param LayoutSettings The JSON object to initialize this settings section from.
	 */
	void InitFromJson(const nlohmann::ordered_json& LayoutSettings) override;

	/**
	 * Initialize this settings section from default values.
	 */
	void InitFromDefaults() override;

	/**
	 * Save this settings section to the supplied JSON object.
	 * 
	 * \param LayoutSettings The JSON object to save this settings section to.
	 */
	void SaveToJson(nlohmann::ordered_json& LayoutSettings) const override;

	/**
	 * Attempt to load the layout from the specified file path.
	 * This will throw if loading fails due to the file/directory
	 * not existing.
	 * 
	 * \param LayoutFilePath The path to the layout file to load.
	 */
	void TryLoadLayout(const fs::path LayoutFilePath);

	/**
	 * Set the currently selected preset in the layout settings.
	 * 
	 * \param NewCurrentPreset The new currently selected preset.
	 */
	void SetCurrentPreset(const std::string& NewCurrentPreset);

	/**
	 * Set whether or not to reload the preset layout on startup in the layout settings.
	 * 
	 * \param NewReloadPresetOnStartup The new value for whether or not to reload the preset layout on startup.
	 */
	void SetReloadPresetOnStartup(const bool NewReloadPresetOnStartup);

	/**
	 * Get the currently selected preset in the layout settings.
	 * 
	 * \return The currently selected preset.
	 */
	std::string GetCurrentPreset() const;

	/**
	 * Get whether or not to reload the preset layout on startup in the layout settings.
	 * 
	 * \return True if we should reload the preset layout on startup, false otherwise.
	 */
	bool GetReloadPresetOnStartup() const;

	/**
	 * Generate a vector of LayoutSettings objects from the supplied JSON array.
	 * Each object in the array should represent a single tab's layout settings.
	 * 
	 * \param Settings The JSON array to generate the LayoutSettings objects from.
	 * \return A vector of LayoutSettings objects generated from the JSON array.
	 */
	static std::vector<std::shared_ptr<LayoutSettings>> GenerateTabLayoutSettingsFromJson(nlohmann::ordered_json& Settings);

private:

	/**
	 * The filename (minus "ini") of the most recently loaded preset layout 
	 * for this tab. Value may also be "Default" indicating that the last 
	 * loaded preset was the hard-coded default.
	 */
	AppSetting<std::string> CurrentPreset;

	/**
	 * Should we reload the preset layout on startup,
	 * or load the the layout used in the previous session?
	 */
	AppSetting<bool> ReloadPresetOnStartup;
};
