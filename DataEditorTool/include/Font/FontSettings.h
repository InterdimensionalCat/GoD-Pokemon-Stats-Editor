/*****************************************************************//**
 * \file   FontSettings.h
 * \brief  Settings section for font settings, including English and Japanese font names, sizes, and colors.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "Settings/SettingsSection/SettingsSection.h"
#include "Settings/AppSetting.h"
#include "Util/JsonHelpers.h"

/**
 * \brief Settings section for font settings, including English and Japanese font names, sizes, and colors.
 * 
 * These settings will be saved to/loaded from disk during each session so that
 * users' font settings will persist between sessions.
 */
class FontSettings : public SettingsSection
{
public:

	/**
	 * Construct a FontSettings section with default values.
	 * These values are expected to be overridden by InitFromJson 
	 * or InitFromDefaults, but we should ensure that these defaults
	 * match the defaults for each AppSetting.
	 */
	FontSettings();

	/**
	 * Initialize this settings section from the supplied JSON object.
	 * 
	 * \param FontSettings The JSON object to load the settings from.
	 */
	void InitFromJson(const nlohmann::ordered_json& FontSettings) override;

	/**
	 * Initialize this settings section from default values.
	 */
	void InitFromDefaults() override;

	/**
	 * Save this settings section to the supplied JSON object.
	 * 
	 * \param FontSettings The JSON object to save the settings to.
	 */
	void SaveToJson(nlohmann::ordered_json& FontSettings) const override;

	/**
	 * Get the name of this settings section.
	 * 
	 * \return The name of this settings section.
	 */
	static std::string GetSectionName();

	/**
	 * Get the current EN font name from settings.
	 * 
	 * \return The current EN font name from settings.
	 */
	std::string GetENFont() const;

	/**
	 * Get the current JP font name from settings.
	 * 
	 * \return The current JP font name from settings.
	 */
	std::string GetJPFont() const;

	/**
	 * Get the current font size from settings.
	 * 
	 * \return The current font size from settings.
	 */
	int32_t GetFontSize() const;

	/**
	 * Get the current JP font size multiplier from settings.
	 * 
	 * \return The current JP font size multiplier from settings.
	 */
	float GetJPFontSizeMultiplier() const;

	/**
	 * Get the current font color from settings.
	 * 
	 * \return The current font color from settings.
	 */
	ImColor GetFontColor() const;


	/**
	 * Set the current EN font name in settings.
	 * 
	 * \param NewCurrentFont The new EN font name to set in settings.
	 */
	void SetENFont(const std::string& NewCurrentFont);

	/**
	 * Set the current JP font name in settings.
	 * 
	 * \param NewCurrentFont The new JP font name to set in settings.
	 */
	void SetJPFont(const std::string& NewCurrentFont);

	/**
	 * Set the current font size in settings.
	 * 
	 * \param NewFontSize The new font size to set in settings.
	 */
	void SetFontSize(const int32_t NewFontSize);

	/**
	 * Set the current JP font size multiplier in settings.
	 * 
	 * \param NewFontSizeMultiplier The new JP font size multiplier to set in settings.
	 */
	void SetJPFontSizeMultiplier(const float NewFontSizeMultiplier);

	/**
	 * Set the current font color in settings.
	 * 
	 * \param NewFontColor The new font color to set in settings.
	 */
	void SetFontColor(const ImColor& NewFontColor);

private:

	/** The file name of the English font to use. */
	AppSetting<std::string> ENFont;

	/** The file name of the Japanese font to use. */
	AppSetting<std::string> JPFont;

	/** The base font size to use for English text. */
	AppSetting<int32_t>     FontSize;

	/** The multiplier to apply to the base font size for Japanese text. */
	AppSetting<float>       JPFontSizeMultiplier;

	/** The color to use for all text. */
	AppSetting<ImColor>     FontColor;
};
