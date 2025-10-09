/*****************************************************************//**
 * \file   AppSetting.h
 * \brief  Named setting with a default value, can be loaded from a JSON object.
 *
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

 /**
  * \brief  Named setting with a default value, can be loaded from a JSON object.
  * If the setting is not found during loading, we will fall back to the default value.
  */
template<typename SettingType>
class AppSetting
{
public:

	/**
	 * Construct an AppSetting with the given name and default value.
	 *
	 * \param InName The name of the setting, used as the key in the JSON object.
	 * \param InDefaultValue The default value of the setting, used if loading fails.
	 */
	AppSetting(
		const std::string& InName,
		const SettingType& InDefaultValue
	) :
		Name(InName),
		LoadedValue(InDefaultValue),
		DefaultValue(InDefaultValue) 
	{

	}

	/** Load the default value into the loaded value. */
	void LoadDefaultValue()
	{
		LoadedValue = DefaultValue;
	}

	/**
	 * Attempt to load the setting from the given JSON object.
	 * If the setting is not found, we will fall back to the default value.
	 *
	 * \param SettingSectionJson The JSON object to load the setting from.
	 * \return True if the setting was found and loaded, false if we fell back to the default value.
	 */
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

	/**
	 * Save the setting to the given JSON object.
	 *
	 * \param SettingSectionJson The JSON object to save the setting to.
	 */
	virtual void SaveToJson(nlohmann::ordered_json& SettingSectionJson) const
	{
		SettingSectionJson[GetName()] = LoadedValue;
	}

	/**
	 * Get the name of the setting.
	 * 
	 * \return The name of the setting.
	 */
	std::string GetName() const
	{
		return Name;
	}

	/**
	 * Get the default value of the setting.
	 * 
	 * \return The default value of the setting.
	 */
	const SettingType& GetDefaultValue() const
	{
		return DefaultValue;
	}

	/**
	 * Get the currently loaded value of the setting.
	 * 
	 * \return The currently loaded value of the setting.
	 */
	const SettingType& GetValue() const
	{
		return LoadedValue;
	}

	/**
	 * Set the currently loaded value of the setting.
	 * 
	 * \param NewValue The new value to set the setting to.
	 */
	void SetValue(const SettingType& NewValue)
	{
		LoadedValue = NewValue;
	}

private:

	/** The name of the setting, used as the key in the JSON object. */
	const std::string Name;

	/** The default value of the setting, used if loading fails. */
	const SettingType DefaultValue;

	/** The currently loaded value of the setting. */
	SettingType LoadedValue;
};
