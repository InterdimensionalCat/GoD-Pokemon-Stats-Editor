/*****************************************************************//**
 * \file   MergedFont.h
 * \brief  Class that represents a merged font for use in ImGui.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

/**
 * \brief  Class that represents a merged font for use in ImGui.
 * 
 * This is organizationally useful as the DataEditorTool needs
 * five different data points to display a font correctly:
 * English font, Japanese font, font size, JP font size multiplier,
 * and font color.
 * 
 * It is also necessasary to keep an ImFont* pointer alive
 * throughout the entire time the font is in use.
 */
class MergedFont
{

public:

	/**
	 * Construct a default MergedFont with no font data.
	 */
	MergedFont() = default;

	/**
	 * Construct a MergedFont with the supplied parameters,
	 * including a pointer to the ImGui-generated font data.
	 */
	MergedFont(
		const std::string& InENFontName,
		const std::string& InJPFontName,
		const int32_t InFontSize,
		const float InJPFontSizeMultiplier,
		const ImColor& InFontColor,
		ImFont* InMergedFontData
	);

	/**
	 * Get a string representation of this MergedFont.
	 */
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

