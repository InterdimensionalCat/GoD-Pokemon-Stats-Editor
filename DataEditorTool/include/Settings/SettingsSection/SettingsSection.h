#pragma once

class SettingsSection
{
public:

	SettingsSection(const std::string& InName);

	virtual void InitFromJson(const nlohmann::ordered_json& LayoutSettings);

	virtual void InitFromDefaults();

	virtual void SaveToJson(nlohmann::ordered_json& LayoutSettings) const;
	
	std::string GetName() const;

private:

	std::string Name;
};