#include "include.h"
#include "Settings/AppSettings.h"

#include "Settings/SettingsSection/SettingsSection.h"
#include "Settings/SettingsSection/GeneralSettingsSection.h"
#include "Font/FontSettings.h"
#include "Layout/LayoutSettings.h"

AppSettings::AppSettings()
{
	//AddSection(LayoutSettings);
	AddSection(std::make_shared<GeneralSettings>());
	AddSection(std::make_shared<FontSettings>());
	
}

void AppSettings::Init()
{
	// Attempt to load each settings section from the settings file.
	// Otherwise load default settings.
	try
	{
		// Find the settings directory or create it if it doesn't exist
		std::filesystem::path SettingsDirectory = std::filesystem::current_path();
		SettingsDirectory /= "Settings";

		if (!std::filesystem::is_directory(SettingsDirectory))
		{
			ICLogger::Warn("Settings directory not found, creating one now...");
			if (!std::filesystem::create_directory(SettingsDirectory))
			{
				throw std::exception("Settings directory creation failed, is the folder read only?");
			}
		}

		// Find the Settings json if it exists, otherwise load default settings
		std::filesystem::path SettingsFilePath = SettingsDirectory / "Settings.json";

		if (!std::filesystem::exists(SettingsFilePath))
		{
			// Settings file not found, load default settings.
			ICLogger::PushWarnNotification("Settings not found", 5000, "Settings file not found, loaded default settings instead");
			InitSettingsFromDefaults();
		}
		else
		{
			// Attempt to load the Settings Json from an open file stream.
			std::ifstream SettingsStream(SettingsFilePath);

			if (!SettingsStream.is_open())
			{
				std::string ErrorMsg = "Settings file failed to open, check file permissions";
				throw std::exception(ErrorMsg.c_str());
			}

			SettingsStream >> SettingsJson;

			// Add layout sections settings based on the layout settings
			// found  in the settings json.
			auto LayoutSettingsArr = LayoutSettings::GenerateTabLayoutSettingsFromJson(SettingsJson);

			for(auto LayoutSection : LayoutSettingsArr)
			{
				AddSection(LayoutSection);
			}

			// Initialize each section from the loaded json.
			InitSettingsFromJson();
		}
	}
	catch (const std::exception& e)
	{
		// If anything fails we fall back to loading default settings.
		ICLogger::PushErrorNotification(
			"Failed to load settings",
			3000,
			"Failed to load settings, falling back to defaults: {}",
			e.what()
		);

		InitSettingsFromDefaults();
	}
}

void AppSettings::Exit()
{
	// Attempt to save all settings sections to the settings json, then write it to a file
	try
	{
		// Save each section to the settings json.
		SaveSettingsToJson();

		// Try to find the settings directory.
		std::filesystem::path SettingsDirectory = std::filesystem::current_path();
		SettingsDirectory /= "Settings";

		if (!std::filesystem::is_directory(SettingsDirectory))
		{
			std::string ErrorMsg = "Settings directory not found";
			throw std::exception(ErrorMsg.c_str());
		}

		// Try to open or create the settings file.
		// Opening an ofstream to a path will create the file if it doesn't exist.
		std::filesystem::path SettingsFilePath = SettingsDirectory / "Settings.json";
		std::ofstream SettingsStream(SettingsFilePath);

		if (!SettingsStream.is_open())
		{
			std::string ErrorMsg = "Settings file failed to open, check file permissions";
			throw std::exception(ErrorMsg.c_str());
		}

		// Dump the settings json to the opened file
		SettingsStream << SettingsJson.dump(4);
	}
	catch (const std::exception& e)
	{
		// If anything fails, just don't save the settings
		ICLogger::Error("Failed to save settings {}", e.what());

		// Dump the settings to the debug log so they can be recovered.
		ICLogger::Debug("Current settings file dump:\n{}", SettingsJson.dump(4));
	}
}

void AppSettings::InitSettingsFromJson()
{
	for (auto Section : SettingsSections)
	{
		Section.second->InitFromJson(SettingsJson[Section.second->GetName()]);
	}
}

void AppSettings::InitSettingsFromDefaults()
{
	for (auto Section : SettingsSections)
	{
		Section.second->InitFromDefaults();
	}
}

void AppSettings::SaveSettingsToJson()
{
	for (auto Section : SettingsSections)
	{
		Section.second->SaveToJson(SettingsJson[Section.second->GetName()]);
	}
}

std::shared_ptr<FontSettings> AppSettings::GetFontSettings()
{
	return std::dynamic_pointer_cast<FontSettings>(GetSectionByName("Font Settings"));
}

std::shared_ptr<LayoutSettings> AppSettings::GetLayoutSettingsForTab(const std::string& InTabName)
{
	auto Section = GetSectionByName(std::format("{}-Layout Settings", InTabName));

	if(Section != nullptr)
	{
		return std::dynamic_pointer_cast<LayoutSettings>(Section);
	}
	else
	{
		return nullptr;
	}
}

void AppSettings::AddSection(const std::shared_ptr<SettingsSection> NewSection)
{
	SettingsSections.emplace(NewSection->GetName(), NewSection);
}

std::shared_ptr<SettingsSection> AppSettings::GetSectionByName(const std::string& SectionName)
{
	if(SettingsSections.find(SectionName) == SettingsSections.end())
	{
		return nullptr;
	}

	return SettingsSections.at(SectionName);
}
