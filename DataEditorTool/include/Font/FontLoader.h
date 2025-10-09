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
	 * 
	 * \param FontToLoad The MergedFont to load.
	 * \return True if loading succeeded, false otherwise.
	 */
	bool TryLoadFont(MergedFont& FontToLoad);

private:

	/**
	 * Loads the ImGui default font file after disabling merging.
	 * NOTE: does not build the font atlas or Create/Destroy OpenGL device objects,
	 * so this must be done before returning the font.
	 * 
	 * \return Pointer to the loaded default font.
	 */
	ImFont* LoadDefaultFont();

	/**
	 * Loads the font from the given filename if a filename is given, or "Default" if default is given.
	 * 
	 * \param FileNameOrDefault The font file name to load, or "Default" to load the default font.
	 * \param FontSize The size of the font to load.
	 * \param Config The ImFontConfig to use when loading the font.
	 * \param bJPFile Whether or not this is a JP font file, which will apply custom ranges.
	 * \return Pointer to the loaded font, or nullptr if loading failed.
	 */
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
	 * 
	 * \param FontFileName The name of the font file to find.
	 * \return The path to the font file.
	 */
	fs::path TryGetENFontFile(const std::string& FontFileName);

	/**
	 * Attempt to find the JP font file with the given name.
	 * This will search the "Fonts/JP" directory and will throw
	 * if the font file could not be found or if the directory
	 * does not exist.
	 * 
	 * \param FontFileName The name of the font file to find.
	 * \return The path to the font file.
	 */
	fs::path TryGetJPFontFile(const std::string& FontFileName);

	/**
	 * Attempt to find the font file with the given name
	 * in the directory for the given language code.
	 * This will search the "Fonts/{Lang}" directory and will throw
	 * if the font file could not be found or if the directory
	 * does not exist.
	 * 
	 * \param FontFileName The name of the font file to find.
	 * \param Lang The language code to search in, e.g. "EN" or "JP".
	 * \return The path to the font file.
	 */
	fs::path TryGetLangFontFile(const std::string& FontFileName, const std::string& Lang);

	/**
	 * Custom ranges are needed because of the 
	 * male/female symbol, and Japanese characters.
	 */
	ImVector<ImWchar> CustomRanges;
};
