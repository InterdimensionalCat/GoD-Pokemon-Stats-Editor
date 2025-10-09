/*****************************************************************//**
 * \file   FontManager.h
 * \brief  Manager for font loading, changing and settings.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "Font/MergedFont.h"


class FontLoader;
class FontSettings;

/**
 * \brief  Manager for font loading, changing and settings.
 * 
 * Will find all available fonts on initialization, but
 * will only load the fonts required for the active
 * MergedFont. Looks for fonts in the "Fonts/EN" and "Fonts/JP"
 * directories.
 */
class FontManager
{

public:

	/**
	 * Construct a FontManager. Fonts will not be 
	 * found or loaded until Init() is called.
	 */
	FontManager();

	/**
	 * Initialize the FontManager, this will find
	 * all available fonts and load the currently
	 * selected font from FontSettings.
	 */
	void Init();

	/**
	 * Find all font files present in
	 * Fonts/EN and Fonts/JP directories.
	 */
	void FindAvailableFonts();

	/**
	 * Reload the current font if bShouldReloadFont
	 * has been set.
	 * 
	 * This should be called once per frame before
	 * SetupFontForFrame is called.
	 */
	void CheckForFontChanged();

	/**
	 * Setup the currently loaded font for use
	 * in the current ImGui frame.
	 * 
	 * This should be called once per frame after
	 * CheckForFontChanged is called, and before
	 * any ImGui calls are made.
	 */
	void SetupFontForFrame();

	/**
	 * End the use of the currently loaded font
	 * for the current ImGui frame.
	 * 
	 * This should be called once per frame after
	 * all ImGui calls are made.
	 */
	void EndFontForFrame();

	/**
	 * Save the currently loaded font info
	 * to font settings.
	 */
	void SaveCurrentFontToFontSettings();

	/**
	 * Get the currently loaded merged font info.
	 * 
	 * \return The currently loaded merged font info.
	 */
	const MergedFont& GetCurrentlyLoadedFont() const;

	/**
	 * Get a list of all available EN font filenames.
	 * 
	 * \return A list of all available EN font filenames.
	 */
	const std::vector<std::string>& GetAvailableENFonts() const;

	/**
	 * Get a list of all available JP font filenames.
	 * 
	 * \return A list of all available JP font filenames.
	 */
	const std::vector<std::string>& GetAvailableJPFonts() const;

	/**
	 * Get the minimum allowed font size.
	 * 
	 * \return The minimum allowed font size.
	 */
	int32_t GetMinFontSize() const;

	/**
	 * Get the maximum allowed font size.
	 * 
	 * \return The maximum allowed font size.
	 */
	int32_t GetMaxFontSize() const;

	/**
	 * Set the current EN font filename. This will
	 * cause the current font to be reloaded next frame.
	 * 
	 * \param NewFontName The new EN font filename to set.
	 */
	void SetCurrentENFont(const std::string& NewFontName);

	/**
	 * Set the current JP font filename. This will
	 * cause the current font to be reloaded next frame.
	 * 
	 * \param NewFontName The new JP font filename to set.
	 */
	void SetCurrentJPFont(const std::string& NewFontName);

	/**
	 * Set the current font size. This does not require
	 * a font reload as font sizes can be dynamically
	 * changed in ImGui now.
	 * 
	 * \param NewFontSize The new font size to set.
	 */
	void SetCurrentFontSize(const int32_t NewFontSize);

	/**
	 * Set the current JP font size multiplier. This does not require
	 * a font reload as font sizes can be dynamically
	 * changed in ImGui now.
	 * 
	 * \param NewFontSizeMultiplier The new JP font size multiplier to set.
	 */
	void SetCurrentJPFontSizeMultiplier(const float NewFontSizeMultiplier);

	/**
	 * Set the current font color in font settings. This
	 * does not require a font reload.
	 * 
	 * \param NewColor The new font color to set.
	 */
	void SetCurrentFontColor(const ImColor& NewColor);

private:

	/** Should we reload the current MergedFont next frame? */
	bool bShouldReloadFont = false;

	/** Font settings for the tool. */
	std::shared_ptr<FontSettings> MainFontSettings;

	/** Font loader for loading fonts from disk. */
	std::shared_ptr<FontLoader> MainFontLoader;

	/** List of available English fonts */
	std::vector<std::string> AvailableENFonts;

	/** List of available Japanese fonts */
	std::vector<std::string> AvailableJPFonts;

	/** Current font info */

	/** Contains the EN and JP font names, the current font size, and the JP font modifier. */
	MergedFont CurrentlyLoadedFont;

	/** Minimum allowed font size */
	const int32_t MinFontSize = 8;

	/** Maximum allowed font size */
	const int32_t MaxFontSize = 32;
};
