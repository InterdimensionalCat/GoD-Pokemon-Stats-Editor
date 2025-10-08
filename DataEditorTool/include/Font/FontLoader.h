/*****************************************************************//**
 * \file   FontLoader.h
 * \brief  Helper class for loading and merging fonts for ImGui
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

class MergedFont;

/**
 * \brief  Helper class for loading and merging fonts for ImGui.
 */
class FontLoader
{

public:

	/**
	 * Construct a FontLoader.
	 * This will automatically build new custom ranges
	 * for Japanese characters and the Male/Female symbol,
	 * both of which are needed to display some CSV values.
	 */
	FontLoader();

	/**
	 * Attempt to load the supplied merged font.
	 * This will load the EN/JP font files contained
	 * In the MergedFont parameter, or the default font
	 * if "Default" is supplied.
	 * 
	 * Returns true if loading succeeded, false otherwise.
	 * If any part of loading failed, we fall back on loading
	 * the default font.
	 * 
	 * If font loading does fail, then the MergedFont parameter
	 * will have its values modified to match the fallback font
	 * (Default font at size 13)
	 */
	bool TryLoadFont(MergedFont& FontToLoad);

private:

	/**
	 * Loads the ImGui default font file after disabling merging.
	 * NOTE: does not build the font atlas or Create/Destroy OpenGL device objects,
	 * so this must be done before returning the font.
	 */
	ImFont* LoadDefaultFont();

	/** Loads the font from the given filename if a filename is given, or "Default" if default is given */
	ImFont* LoadFontFromFileOrDefault(
		const std::string& FileNameOrDefault, 
		const int32_t FontSize, 
		ImFontConfig* Config, 
		const bool bJPFile);

	/**
	 * Build the custom ranges needed for Japanese characters
	 * and the Male/Female symbol.
	 */
	void BuildCustomRanges();

	/**
	 * Attempt to find the EN font file with the given name.
	 * This will search the "Fonts/EN" directory and will throw
	 * if the font file could not be found or if the directory
	 * does not exist.
	 */
	fs::path TryGetENFontFile(const std::string& FontFileName);

	/**
	 * Attempt to find the JP font file with the given name.
	 * This will search the "Fonts/JP" directory and will throw
	 * if the font file could not be found or if the directory
	 * does not exist.
	 */
	fs::path TryGetJPFontFile(const std::string& FontFileName);

	/**
	 * Attempt to find the font file with the given name
	 * in the directory for the given language code.
	 * This will search the "Fonts/{Lang}" directory and will throw
	 * if the font file could not be found or if the directory
	 * does not exist.
	 */
	fs::path TryGetLangFontFile(const std::string& FontFileName, const std::string& Lang);

	/**
	 * Custom ranges are needed because of the 
	 * male/female symbol, and Japanese characters.
	 */
	ImVector<ImWchar> CustomRanges;
};
