#pragma once

#include "Settings/SettingsSection/SettingsSection.h"
#include "Settings/AppSetting.h"
#include "Util/JsonHelpers.h"

class LayoutSettings : public SettingsSection
{
public:

	LayoutSettings(const std::string& InTabName);

	void InitFromJson(const nlohmann::ordered_json& LayoutSettings) override;

	void InitFromDefaults() override;

	void SaveToJson(nlohmann::ordered_json& LayoutSettings) const override;

	void TryLoadLayout(const fs::path LayoutFilePath);

	void SetCurrentPreset(const std::string& NewCurrentPreset);
	void SetReloadPresetOnStartup(const bool NewReloadPresetOnStartup);

	std::string GetCurrentPreset() const;
	bool GetReloadPresetOnStartup() const;

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
