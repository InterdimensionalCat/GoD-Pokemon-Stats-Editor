#include "include.h"
#include "Settings/SettingsSection/GeneralSettingsSection.h"

GeneralSettings::GeneralSettings() : 
	SettingsSection(GetSectionName()),
	RootPath("Root Path", ""),
	AutoOpenLastRoot("Open Last Root", false)
{

}

void GeneralSettings::InitFromJson(const nlohmann::ordered_json& GeneralSettings)
{
	RootPath.LoadFromJsonOrUseDefault(GeneralSettings);
	AutoOpenLastRoot.LoadFromJsonOrUseDefault(GeneralSettings);
}

void GeneralSettings::InitFromDefaults()
{
	RootPath.LoadDefaultValue();
	AutoOpenLastRoot.LoadDefaultValue();
}

void GeneralSettings::SaveToJson(nlohmann::ordered_json& GeneralSettings) const
{
	RootPath.SaveToJson(GeneralSettings);
	AutoOpenLastRoot.SaveToJson(GeneralSettings);
}

std::string GeneralSettings::GetSectionName()
{
	return "General Settings";
}

std::string GeneralSettings::GetRootPath() const
{
	return RootPath.GetValue();
}

bool GeneralSettings::GetAutoOpenLastRoot() const
{
	return AutoOpenLastRoot.GetValue();
}

void GeneralSettings::SetRootPath(const std::string& NewRootPath)
{
	RootPath.SetValue(NewRootPath);
}

void GeneralSettings::SetAutoOpenLastRoot(const bool NewState)
{
	AutoOpenLastRoot.SetValue(NewState);
}
