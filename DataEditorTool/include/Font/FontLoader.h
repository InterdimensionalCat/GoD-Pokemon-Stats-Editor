#pragma once

class MergedFont;

class FontLoader
{

public:

	FontLoader();

	MergedFont LoadDefaultFont();

	MergedFont TryLoadFont(
		const std::string& EnFontName,
		const std::string& JPFontName, 
		const int32_t FontSize
	);

private:

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
