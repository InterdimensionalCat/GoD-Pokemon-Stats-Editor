/*****************************************************************//**
 * \file   GenralSettingsSection.h
 * \brief  
 * 
 * \author Joe DeLuca
 * \date   November 2025
 *********************************************************************/
#pragma once

#include "Settings/SettingsSection/SettingsSection.h"
#include "Settings/AppSetting.h"
#include "Util/JsonHelpers.h"

class GeneralSettings : public SettingsSection {
public:
	/**
	 * Construct a GeneralSettings section with default values.
	 * These values are expected to be overridden by InitFromJson
	 * or InitFromDefaults, but we should ensure that these defaults
	 * match the defaults for each AppSetting.
	 */
	GeneralSettings();

	/**
	 * Initialize this settings section from the supplied JSON object.
	 *
	 * \param FontSettings The JSON object to load the settings from.
	 */
	void InitFromJson(const nlohmann::ordered_json& LayoutSettings) override;

	/**
	 * Initialize this settings section from default values.
	 */
	void InitFromDefaults() override;

	/**
	 * Save this settings section to the supplied JSON object.
	 *
	 * \param FontSettings The JSON object to save the settings to.
	 */
	void SaveToJson(nlohmann::ordered_json& LayoutSettings) const override;

	/**
	 * Get the name of this settings section.
	 *
	 * \return The name of this settings section.
	*/
	static std::string GetSectionName();

	/**
	 * Get the current root directory file path from settings.
	 *
	 * \return The current root directory file path from settings.
	 */
	std::string GetRootPath() const;

	/**
	 * Get the current state of auto-open last root bool from settings.
	 *
	 * \return The current bool state from settings.
	 */
	bool GetAutoOpenLastRoot() const;

	/**
	 * Set the current root directory file path in settings.
	 *
	 * \param NewCurrentFont The new root directory file path to set in settings.
	 */
	void SetRootPath(const std::string& RootPath);

	/**
	 * Set the current state of auto-open last root bool settings.
	 *
	 * \param NewCurrentFont The new bool state to set in settings.
	 */
	void SetAutoOpenLastRoot(const bool AutoOpenLastRoot);

private:
	
	/** The file path of the last known root directory */
	AppSetting<std::string> RootPath;

	/** The bool controlling the automatic opening of the last known root on launch */
	AppSetting<bool> AutoOpenLastRoot;
	
};
