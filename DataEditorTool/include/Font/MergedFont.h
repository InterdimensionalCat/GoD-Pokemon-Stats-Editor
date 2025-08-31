#pragma once

class MergedFont
{

public:

	MergedFont() = default;

	MergedFont(
		const std::string& InENFontName,
		const std::string& InJPFontName,
		const int32_t InFontSize,
		const float InJPFontSizeMultiplier,
		const ImColor& InFontColor,
		ImFont* InMergedFontData
	);

	std::string ToString() const;

	/**
	 * Name of the font file used for English characters
	 * in this merged font.
	 */
	std::string ENFontName = "";

	/**
	 * Name of the font file used for Japanese characters
	 * in this merged font.
	 */
	std::string JPFontName = "";

	/**
	 * This is the size for EN characters,
	 * JP fonts have a multiplier applied to their
	 * size specified below.
	 */
	int32_t FontSize = 0;

	/**
	 * Font size multiplier for Japanese characters, this is
	 * useful as oftentimes the heights between fonts are not
	 * consistent.
	 */
	float JPFontSizeMultiplier = 0;

	/** Color to use when drawing the Font. */
	ImColor FontColor = ImColor(217, 217, 217, 255);

	/** Pointer to the ImGui-generated merged font. */
	ImFont* MergedFontData = nullptr;
};

