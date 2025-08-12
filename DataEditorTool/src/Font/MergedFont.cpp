#include "include.h"
#include "Font/MergedFont.h"

MergedFont::MergedFont(
	const std::string& InENFontName,
	const std::string& InJPFontName,
	const int32_t InFontSize, 
	ImFont* InMergedFontData) :
	ENFontName(InENFontName), 
	JPFontName(InJPFontName),
	FontSize(InFontSize),
	MergedFontData(InMergedFontData)
{

}