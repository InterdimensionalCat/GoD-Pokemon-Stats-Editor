#include "include.h"
#include "Font/MergedFont.h"

MergedFont::MergedFont(
	const std::string& InENFontName,
	const std::string& InJPFontName,
	const int32_t InFontSize, 
	const float InJPFontSizeMultiplier,
	const ImColor& InFontColor,
	ImFont* InMergedFontData) :
	ENFontName(InENFontName), 
	JPFontName(InJPFontName),
	FontSize(InFontSize),
	FontColor(InFontColor),
	JPFontSizeMultiplier(InJPFontSizeMultiplier),
	MergedFontData(InMergedFontData)
{

}

std::string MergedFont::ToString() const
{
	return std::format(
		"EN Font Name: {}, JP Font Name: {}, Font Size: {}, JP Font Size Multiplier: {}, Font Color (RGBA): ({}, {}, {}, {})",
		ENFontName,
		JPFontName,
		FontSize,
		JPFontSizeMultiplier,
		FontColor.Value.x,
		FontColor.Value.y,
		FontColor.Value.z,
		FontColor.Value.w
	);
}