#pragma once

class SettingsSection
{
public:

	SettingsSection(const std::string& InName);

	virtual void InitFromJson(const nlohmann::json& LayoutSettings);

	virtual void InitFromDefaults();

	virtual void SaveToJson(nlohmann::json& LayoutSettings) const;
	
	std::string GetName() const;

private:

	std::string Name;
};