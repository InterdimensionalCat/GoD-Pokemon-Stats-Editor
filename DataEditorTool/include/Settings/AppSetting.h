/*****************************************************************//**
 * \file   AppSetting.h
 * \brief  Named setting with a default value, can be loaded from a JSON object.
 * If the setting is not found during loading, we will fall back to the default value.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

template<typename SettingType>
class AppSetting
{
public:

	AppSetting(
		const std::string& InName,
		const SettingType& InDefaultValue) :
		Name(InName),
		LoadedValue(InDefaultValue),
		DefaultValue(InDefaultValue) {}

	void LoadDefaultValue()
	{
		LoadedValue = DefaultValue;
	}

	virtual bool LoadFromJsonOrUseDefault(const nlohmann::ordered_json& SettingSectionJson)
	{
		const auto FoundSetting = SettingSectionJson.find(Name);
		if (FoundSetting == SettingSectionJson.end())
		{
			ICLogger::Warn("Setting {} not found, falling back on default value.", GetName());
			LoadedValue = DefaultValue;
			return false;
		}
		else
		{
			LoadedValue = FoundSetting->get<SettingType>();
			return true;
		}
	}

	virtual void SaveToJson(nlohmann::ordered_json& SettingSectionJson) const
	{
		SettingSectionJson[GetName()] = LoadedValue;
	}

	std::string GetName() const
	{
		return Name;
	}

	const SettingType& GetDefaultValue() const
	{
		return DefaultValue;
	}

	const SettingType& GetValue() const
	{
		return LoadedValue;
	}

	void SetValue(const SettingType& NewValue)
	{
		LoadedValue = NewValue;
	}

private:

	const std::string Name;

	const SettingType DefaultValue;

	SettingType LoadedValue;
};
