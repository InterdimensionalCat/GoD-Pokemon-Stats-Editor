#include "include.h"
#include "Settings/SettingsSection/GeneralSettingsSection.h"

GeneralSettings::GeneralSettings() : 
	SettingsSection(GetSectionName()),
	RootPath("Root Path", ""),
	OpenLastRootEnabled("Open Last Root", false)
{

}

void GeneralSettings::InitFromJson(const nlohmann::ordered_json& GeneralSettings)
{
	RootPath.LoadFromJsonOrUseDefault(GeneralSettings);
	OpenLastRootEnabled.LoadFromJsonOrUseDefault(GeneralSettings);
}

void GeneralSettings::InitFromDefaults()
{
	RootPath.LoadDefaultValue();
	OpenLastRootEnabled.LoadDefaultValue();
}

void GeneralSettings::SaveToJson(nlohmann::ordered_json& GeneralSettings) const
{
	RootPath.SaveToJson(GeneralSettings);
	OpenLastRootEnabled.SaveToJson(GeneralSettings);
}

std::string GeneralSettings::GetSectionName()
{
	return "General Settings";
}

std::string GeneralSettings::GetRootPath() const
{
	return RootPath.GetValue();
}

bool GeneralSettings::GetOpenLastRootEnabled() const
{
	return OpenLastRootEnabled.GetValue();
}

void GeneralSettings::SetRootPath(const std::string& NewRootPath)
{
	RootPath.SetValue(NewRootPath);
}

void GeneralSettings::SetOpenLastRootEnabled(const bool NewState)
{
	OpenLastRootEnabled.SetValue(NewState);
}
