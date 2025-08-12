#pragma once
#include "Font/MergedFont.h"
#include "Font/FontLoader.h"
#include "Settings/SettingsSection/FontSettings.h"

//class FontLoader;
//class MergedFont;

class FontManager
{

public:

	FontManager();

	void Init();

	void FindAvailableFonts();

	void CheckForFontChanged();

	void SetupFontForFrame();

	void EndFontForFrame();

	const std::vector<std::string>& GetAvailableENFonts() const;

	const std::vector<std::string>& GetAvailableJPFonts() const;

	const MergedFont& GetCurrentlyLoadedFont() const;

	int32_t GetMinFontSize() const;

	int32_t GetMaxFontSize() const;

	const ImColor& GetCurrentFontColor() const;

private:

	std::shared_ptr<FontSettings> MainFontSettings;

	std::shared_ptr<FontLoader> MainFontLoader;

	MergedFont CurrentlyLoadedFont;

	ImColor CurrentFontColor = ImColor(217, 217, 217, 255);

	std::vector<std::string> AvailableENFonts;

	std::vector<std::string> AvailableJPFonts;

	const int32_t MinFontSize = 10;

	const int32_t MaxFontSize = 18;
};
