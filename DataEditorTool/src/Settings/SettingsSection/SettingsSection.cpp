#include "include.h"
#include "Settings/SettingsSection/SettingsSection.h"

SettingsSection::SettingsSection(const std::string& InName) : Name(InName)
{

}

void SettingsSection::InitFromJson(const nlohmann::ordered_json& LayoutSettings)
{

}

void SettingsSection::InitFromDefaults()
{

}

void SettingsSection::SaveToJson(nlohmann::ordered_json& LayoutSettings) const
{

}

std::string SettingsSection::GetName() const
{
	return Name;
}
