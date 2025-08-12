#pragma once

class MergedFont
{

public:

	MergedFont() = default;

	MergedFont(
		const std::string& InENFontName,
		const std::string& InJPFontName,
		const int32_t InFontSize,
		ImFont* InMergedFontData
	);

	std::string ENFontName = "";

	std::string JPFontName = "";

	int32_t FontSize = 0;

	ImFont* MergedFontData = nullptr;
};

