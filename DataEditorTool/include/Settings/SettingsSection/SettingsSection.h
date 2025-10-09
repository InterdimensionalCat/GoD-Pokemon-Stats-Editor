/*****************************************************************//**
 * \file   SettingsSection.h
 * \brief  Section of settings in the AppSettings class.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

/**
 * \brief  Section of settings in the AppSettings class.
 */
class SettingsSection
{
public:

	/**
	 * Construct a SettingsSection with the specified name.
	 * This name is used to identify the section in the AppSettings
	 * JSON file, and should be unique among all sections.
	 * 
	 * \param InName The name of this SettingsSection.
	 */
	SettingsSection(const std::string& InName);

	/**
	 * Initialize this SettingsSection from the supplied JSON object.
	 * This will be a sub-object of the main AppSettings JSON object,
	 * corresponding to this section's name.
	 * 
	 * This should be overridden by subclasses to load their specific settings.
	 * 
	 * \param LayoutSettings The JSON object to load settings from.
	 */
	virtual void InitFromJson(const nlohmann::ordered_json& LayoutSettings);

	/**
	 * Initialize this SettingsSection from default values.
	 * This should be overridden by subclasses to set their specific settings to defaults.
	 */
	virtual void InitFromDefaults();

	/**
	 * Save this SettingsSection to the supplied JSON object.
	 * This will be a sub-object of the main AppSettings JSON object,
	 * corresponding to this section's name.
	 * 
	 * This should be overridden by subclasses to save their specific settings.
	 * 
	 * \param LayoutSettings The JSON object to save settings to.
	 */
	virtual void SaveToJson(nlohmann::ordered_json& LayoutSettings) const;
	
	/**
	 * Get the name of this SettingsSection.
	 * 
	 * \return The name of this SettingsSection.
	 */
	std::string GetName() const;

private:

	/** The name of this SettingsSection. */
	std::string Name;
};