#pragma once

#include <vector>
#include <string>
#include <queue>
#include <filesystem>
#include "nlohmann/json.hpp"

class ImFont;

using FontKey = std::pair<std::string, int32_t>;

class FontSettings 
{
public:
	FontSettings();

	void Init(const nlohmann::json* FontSettings);

	void DisplayFontMenu();

	void SetActiveFont(const FontKey& NewFont);

	FontKey GetActiveFontKey() const;

	ImFont* GetCurrentFont();

	std::vector<std::string> GetFontsAvailable();

	ImFont* TryLoadFont(const std::filesystem::path& Directory, const std::string& FontFileName, const int32_t FontSize);

	void ResetFontSettings(const bool ReloadElements);

	void SaveFontSettings(nlohmann::json& FontSettings);

	void PushFontSettingsErrorMsg(const std::string& ErrorTitle, const std::string& ErrorMsg);

	void SetFontChanged(const bool InChanged);

	bool GetFontChanged() const;

	const int32_t MinFontSize = 10;
	const int32_t MaxFontSize = 18;

private:

	// All available font names are the same as their file name except for the default font, which is called "Default"
	std::vector<std::string> AvailableFonts;

	std::map<FontKey, ImFont*> LoadedFonts;

	FontKey ActiveFont;

	bool bFontChanged = false;
};
