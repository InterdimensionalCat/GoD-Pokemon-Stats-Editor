#pragma once
#include "Font/MergedFont.h"


class FontLoader;
class FontSettings;

class FontManager
{

public:

	FontManager();

	void Init();

	void FindAvailableFonts();

	void CheckForFontChanged();

	void SetupFontForFrame();

	void EndFontForFrame();

	void SaveCurrentFontToFontSettings();

	const MergedFont& GetCurrentlyLoadedFont() const;
	const std::vector<std::string>& GetAvailableENFonts() const;
	const std::vector<std::string>& GetAvailableJPFonts() const;
	int32_t GetMinFontSize() const;
	int32_t GetMaxFontSize() const;

	void SetCurrentENFont(const std::string& NewFontName);
	void SetCurrentJPFont(const std::string& NewFontName);
	void SetCurrentFontSize(const int32_t NewFontSize);
	void SetCurrentJPFontSizeMultiplier(const float NewFontSizeMultiplier);
	void SetCurrentFontColor(const ImColor& NewColor);

private:

	bool bShouldReloadFont = false;

	std::shared_ptr<FontSettings> MainFontSettings;

	std::shared_ptr<FontLoader> MainFontLoader;

	std::vector<std::string> AvailableENFonts;

	std::vector<std::string> AvailableJPFonts;

	/** Current font info */

	/** Contains the EN and JP font names, the current font size, and the JP font modifier. */
	MergedFont CurrentlyLoadedFont;

	/** Minimum allowed font size */
	const int32_t MinFontSize = 8;

	/** Maximum allowed font size */
	const int32_t MaxFontSize = 32;
};
