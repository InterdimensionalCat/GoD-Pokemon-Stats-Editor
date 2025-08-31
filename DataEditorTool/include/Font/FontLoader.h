#pragma once

class MergedFont;

class FontLoader
{

public:

	FontLoader();

	/**
	 * Attempt to load the supplied merged font.
	 * This will load the EN/JP font files contained
	 * In the MergedFont paramater, or the default font
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

	void BuildCustomRanges();

	fs::path TryGetENFontFile(const std::string& FontFileName);

	fs::path TryGetJPFontFile(const std::string& FontFileName);

	fs::path TryGetLangFontFile(const std::string& FontFileName, const std::string& Lang);

	/**
	 * Custom ranges are needed because of the 
	 * male/female symbol, and Japanese characters.
	 */
	ImVector<ImWchar> CustomRanges;
};
