#include "include.h"
#include "Layout/LayoutSettings.h"

#include "UI/UiTab.h"

LayoutSettings::LayoutSettings(const std::string& InTabName) :
	SettingsSection(std::format("{}-Layout Settings", InTabName)),
	CurrentPreset("Current Preset", "Default"),
	ReloadPresetOnStartup("Reload Preset On Startup", false)
{

}

void LayoutSettings::InitFromJson(const nlohmann::ordered_json& InLayoutSettings)
{
	CurrentPreset.LoadFromJsonOrUseDefault(InLayoutSettings);
	ReloadPresetOnStartup.LoadFromJsonOrUseDefault(InLayoutSettings);
}

void LayoutSettings::InitFromDefaults()
{
	CurrentPreset.LoadDefaultValue();
	ReloadPresetOnStartup.LoadDefaultValue();
}

void LayoutSettings::SaveToJson(nlohmann::ordered_json& OutLayoutSettings) const
{
	CurrentPreset.SaveToJson(OutLayoutSettings);
	ReloadPresetOnStartup.SaveToJson(OutLayoutSettings);
}

void LayoutSettings::TryLoadLayout(const fs::path LayoutFilePath)
{
	if (!std::filesystem::exists(LayoutFilePath))
	{
		std::string ErrorMsg = std::format("Layout file not found: {}", LayoutFilePath.string());
		throw std::exception(ErrorMsg.c_str());
	}

	ImGui::LoadIniSettingsFromDisk(LayoutFilePath.string().c_str());
}

void LayoutSettings::SetCurrentPreset(const std::string& NewCurrentPreset)
{
	CurrentPreset.SetValue(NewCurrentPreset);
}

void LayoutSettings::SetReloadPresetOnStartup(const bool NewReloadPresetOnStartup)
{
	ReloadPresetOnStartup.SetValue(NewReloadPresetOnStartup);
}

std::string LayoutSettings::GetCurrentPreset() const
{
	return CurrentPreset.GetValue();
}

bool LayoutSettings::GetReloadPresetOnStartup() const
{
	return ReloadPresetOnStartup.GetValue();
}

std::vector<std::shared_ptr<LayoutSettings>> LayoutSettings::GenerateTabLayoutSettingsFromJson(nlohmann::ordered_json& Settings)
{
	ICLogger::Debug("Finding existing Tab Layout Settings from settings json");
	std::vector<std::shared_ptr<LayoutSettings>> TabLayoutSettings;
	for (auto& [SectionName, SectionJson] : Settings.items())
	{
		auto SuffixFoundIndex = SectionName.find("-Layout Settings");
		if (SuffixFoundIndex != std::string::npos)
		{
			auto TabName = SectionName.substr(0, SuffixFoundIndex);
			auto TabLayoutSetting = std::make_shared<LayoutSettings>(TabName);
			ICLogger::Debug("Found Layout Settings: {}", TabLayoutSetting->GetName());
			TabLayoutSettings.push_back(TabLayoutSetting);
		}
	}
	return TabLayoutSettings;
}