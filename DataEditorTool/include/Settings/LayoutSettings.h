#pragma once

//#include <vector>
//#include <string>
//#include <deque>
//#include <queue>
//#include <filesystem>
//#include "nlohmann/json.hpp"

class LayoutSettings
{
public:
	LayoutSettings();

	void Init(const nlohmann::json* LayoutSettings);

	void DisplayLayoutMenu();

	void SetActivePresetLayout(const std::string& LayoutName, const bool IsCustomLayout);

	void ReloadActivePresetLayout();

	std::string GetActivePresetLayout() const;

	bool IsActivePresetCustom();

	std::deque<std::string> GetPresetLayoutsAvailable();

	std::deque<std::string> GetCustomLayoutsAvailable();

	bool TryLoadLayout(const std::filesystem::path& Directory, const std::string& LayoutFileName);

	void ResetLayoutSettings(const bool ReloadElements);

	void SaveLayoutSettings(nlohmann::json& LayoutSettings);

	void PushLayoutSettingsErrorMsg(const std::string& ErrorTitle, const std::string& ErrorMsg);

	void SetLayoutChanged(const bool InChanged);

	bool GetLayoutChanged() const;

	bool GetDirectoryForLayout(std::filesystem::path& OutPath, const bool GetCustomDir) const;

	bool SaveNewPreset(const std::string& PresetName);

	void SetSaveModalActive(const bool ModalActive);

	bool GetSaveModalActive() const;

	void ShowSaveModal();

private:

	std::deque<std::string> AvailablePresetLayouts;

	std::deque<std::string> AvailableCustomLayouts;

	std::string CurrentPresetLayout;

	bool bLoadPresetOnStartup = false;

	bool bCurrentPresetCustom = false;

	bool bLayoutChanged = false;

	bool bSaveModalActive = false;

	bool bShouldOpenSaveModal = false;

	std::string SaveModalPromptText;
};
