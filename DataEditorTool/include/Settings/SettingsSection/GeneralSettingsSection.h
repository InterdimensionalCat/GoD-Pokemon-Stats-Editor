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

	void InitFromJson(const nlohmann::ordered_json& LayoutSettings) override;

	void InitFromDefaults() override;

	void SaveToJson(nlohmann::ordered_json& LayoutSettings) const override;

	static std::string GetSectionName();

	std::string GetRootPath() const;

	bool GetOpenLastRootEnabled() const;

	void SetRootPath(const std::string& RootPath);

	void SetOpenLastRootEnabled(const bool OpenLastRootEnabled);

private:
	
	AppSetting<std::string> RootPath;

	AppSetting<bool> OpenLastRootEnabled;
	
};
