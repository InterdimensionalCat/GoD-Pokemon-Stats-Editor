#include "include.h"
#include "Font/FontLoader.h"

#include "Font/MergedFont.h"

FontLoader::FontLoader() : CustomRanges()
{
	BuildCustomRanges();
}

MergedFont FontLoader::LoadDefaultFont()
{
	// Add default font and build it before returning a pointer to it.
	ImFontAtlas* FontAtlas = ImGui::GetIO().Fonts;
	ImFontConfig Config = ImFontConfig();

	// Disable font merging if we are just loading default.
	Config.MergeMode = false;

	// Clear the currently loaded fonts before adding the default font.
	// FontAtlas->Clear();

	// Set the currently loaded font to
	auto FontData = FontAtlas->AddFontDefault(&Config);
	FontAtlas->Build();

	// Not sure why but this is needed whenever we load fonts
	// after ImGui OpenGL initialization.
	ImGui_ImplOpenGL3_DestroyDeviceObjects();
	ImGui_ImplOpenGL3_CreateDeviceObjects();

	return MergedFont("Default", "Default", 13, FontData);
}

MergedFont FontLoader::TryLoadFont(
	const std::string& EnFontName,
	const std::string& JpFontName,
	const int32_t FontSize
)
{
	if (EnFontName == "Default" && JpFontName == "Default")
	{
		return LoadDefaultFont();
	}

	try
	{
		ImFontAtlas* FontAtlas = ImGui::GetIO().Fonts;
		ImFontConfig Config = ImFontConfig();
		//Config.OversampleH = 1;
		//Config.OversampleV = 1;
		Config.GlyphRanges = CustomRanges.Data;

		// Ensure that paths are valid before we clear the font atlas, as
		// This is what is most likely to fail.
		fs::path EnPath = TryGetENFontFile(EnFontName);
		fs::path JpPath = TryGetJPFontFile(JpFontName);

		// FontAtlas->Clear();

		ImFont* TryLoadENFont = FontAtlas->AddFontFromFileTTF(
			EnPath.string().c_str(), 
			FontSize, 
			&Config, 
			Config.GlyphRanges
		);

		if (TryLoadENFont == nullptr)
		{
			std::string ErrorMsg = std::format("Error loading English font, check that a valid TTF file was used: {}", EnPath.string());
			throw std::exception(ErrorMsg.c_str());
		}

		// Needed to merge fonts correctly.
		Config.MergeMode = true;

		ImFont* TryLoadJPFont = FontAtlas->AddFontFromFileTTF(
			JpPath.string().c_str(), 
			FontSize * 1.5, 
			&Config, 
			Config.GlyphRanges
		);
		
		if (TryLoadJPFont == nullptr)
		{
			std::string ErrorMsg = std::format("Error loading Japanese font, check that a valid TTF file was used: {}", EnPath.string());
			throw std::exception(ErrorMsg.c_str());
		}

		FontAtlas->Build();

		// Not sure why but this is needed whenever we load fonts
		// after ImGui OpenGL initialization.
		ImGui_ImplOpenGL3_DestroyDeviceObjects();
		ImGui_ImplOpenGL3_CreateDeviceObjects();

		return MergedFont(EnFontName, JpFontName, FontSize, TryLoadJPFont);
	}
	catch (const std::exception& e)
	{
		ICLogger::PushErrorNotification("Failed to load merged font", 3000,"Falling back to default font: {}", e.what());
		return LoadDefaultFont();
	}
}

void FontLoader::BuildCustomRanges()
{
	// Build glyph ranges for Male/Female symbol and JP characters.
	ImGuiIO& io = ImGui::GetIO();
	ImFontGlyphRangesBuilder Builder;
	Builder.AddRanges(io.Fonts->GetGlyphRangesDefault());
	Builder.AddRanges(io.Fonts->GetGlyphRangesJapanese());

	static const ImWchar Ranges[] =
	{
	0x2640, 0x2642, // glyph range for male/female symbol
	0,
	};

	Builder.AddRanges(Ranges);
	Builder.BuildRanges(&CustomRanges);
}

fs::path FontLoader::TryGetENFontFile(const std::string& FontFileName)
{
	return TryGetLangFontFile(FontFileName, "EN");
}

fs::path FontLoader::TryGetJPFontFile(const std::string& FontFileName)
{
	return TryGetLangFontFile(FontFileName, "JP");
}

fs::path FontLoader::TryGetLangFontFile(const std::string& FontFileName, const std::string& Lang)
{
	// Attempt to get the font directory for this Language.
	// Each language's fonts should be located in {ProjectDir}/Resources/Fonts/{Lang}/
	// EX: {ProjectDir}/Resources/Fonts/EN/
	std::filesystem::path FontDirectory = std::filesystem::current_path();
	FontDirectory /= "Resources";
	FontDirectory /= "Fonts";
	FontDirectory /= Lang;

	// Throw error if the directory is not found
	if (!std::filesystem::is_directory(FontDirectory))
	{
		std::string ErrorMsg = std::format("{} fonts directory not found: {}", Lang, FontDirectory.string());
		throw std::exception(ErrorMsg.c_str());
	}

	// Attempt to get the font file within this Lang's font directory
	std::filesystem::path FontFilePath = FontDirectory / FontFileName;

	// Throw error if the file doesn't exist
	if (!std::filesystem::exists(FontFilePath))
	{
		std::string ErrorMsg = std::format("{} Language font file not found: {}", Lang, FontFilePath.string());
		throw std::exception(ErrorMsg.c_str());
	}

	// Return font if its found.
	return FontFilePath;
}