#include "include.h"

#include "Settings/Settings.h"
#include "Settings/FontSettings.h"
#include "Settings/LayoutSettings.h"
#include "GoD-UI-Windows.h"

AppSettings::AppSettings() : CurrentFontSettings(std::make_shared<FontSettings>()), CurrentLayoutSettings(std::make_shared<LayoutSettings>())
{

}

void AppSettings::Init()
{
	// Attempt to load font from font settings
	try
	{
		std::filesystem::path SettingsDirectory = std::filesystem::current_path();
		SettingsDirectory /= "Settings";

		if (!std::filesystem::is_directory(SettingsDirectory))
		{
			std::string ErrorMsg = "Settings directory not found, creating one now...";
			std::cout << ErrorMsg << "\n";
			if (!std::filesystem::create_directory(SettingsDirectory))
			{
				throw std::exception("Settings directory creation failed, is the folder read only?");
			}
		}

		std::filesystem::path SettingsFilePath = SettingsDirectory / "Settings.json";

		if (!std::filesystem::exists(SettingsFilePath))
		{
			std::string ErrorMsg = "Settings file not found";
			throw std::exception(ErrorMsg.c_str());
		}

		std::ifstream SettingsStream(SettingsFilePath);

		if (!SettingsStream.is_open())
		{
			std::string ErrorMsg = "Settings file failed to open, check permissions";
			throw std::exception(ErrorMsg.c_str());
		}

		SettingsStream >> SettingsJson;

		CurrentFontSettings->Init(&SettingsJson["Font Settings"]);
		CurrentLayoutSettings->Init(&SettingsJson["Layout Settings"]);

	}
	catch (const std::exception& e)
	{
		auto ErrorMsg = std::format("Failed to load settings, falling back to defaults: {}", e.what());
		PushSettingsErrorMsg("Settings loading failed", ErrorMsg);
		LoadDefaultSettings();
	}
}

void AppSettings::Exit()
{
	try
	{
		CurrentFontSettings->SaveFontSettings(SettingsJson["Font Settings"]);
		CurrentLayoutSettings->SaveLayoutSettings(SettingsJson["Layout Settings"]);

		std::filesystem::path SettingsDirectory = std::filesystem::current_path();
		SettingsDirectory /= "Settings";

		if (!std::filesystem::is_directory(SettingsDirectory))
		{
			std::string ErrorMsg = "Settings directory not found";
			throw std::exception(ErrorMsg.c_str());
		}

		std::filesystem::path SettingsFilePath = SettingsDirectory / "Settings.json";

		std::ofstream SettingsStream(SettingsFilePath);

		if (!SettingsStream.is_open())
		{
			std::string ErrorMsg = "Settings file failed to open, check permissions";
			throw std::exception(ErrorMsg.c_str());
		}

		SettingsStream << SettingsJson.dump(4);
	}
	catch (const std::exception& e)
	{
		auto ErrorMsg = std::format("Failed to save settings {}", e.what());
		std::cout << ErrorMsg << "\n";
	}
}

void AppSettings::LoadDefaultSettings()
{
	CurrentFontSettings->Init(nullptr);
	CurrentLayoutSettings->Init(nullptr);
}

std::shared_ptr<FontSettings> AppSettings::GetFontSettings()
{
	return CurrentFontSettings;
}

std::shared_ptr<LayoutSettings> AppSettings::GetLayoutSettings()
{
	return CurrentLayoutSettings;
}

void AppSettings::PushSettingsErrorMsg(const std::string& ErrorTitle, const std::string& ErrorMsg)
{
	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
	toast->setTitle(ErrorTitle.c_str());
	std::cout << ErrorMsg << "\n";
	toast->setContent("%s", ErrorMsg.c_str());
	ImGui::InsertNotification(*toast);
}
