#include "include.h"
#include "Font/FontLoader.h"

#include "Font/MergedFont.h"
#include "MainEditor/MainEditorWindow.h"
#include "Contexts/GuiContext.h"

FontLoader::FontLoader() : CustomRanges()
{
	BuildCustomRanges();
}

ImFont* FontLoader::LoadDefaultFont()
{
	// Add default font and build it before returning a pointer to it.
	ImFontAtlas* FontAtlas = ImGui::GetIO().Fonts;
	ImFontConfig Config = ImFontConfig();

	// Disable font merging if we are just loading default.
	Config.MergeMode = false;
	return FontAtlas->AddFontDefault(&Config);
}

ImFont* FontLoader::LoadFontFromFileOrDefault(
	const std::string& FileNameOrDefault,
	const int32_t FontSize,
	ImFontConfig* Config,
	const bool bJPFile)
{
	// If the default font was passed in just load the default font.
	const bool bLoadDefault = FileNameOrDefault == "Default";
	if (bLoadDefault)
	{
		if (bJPFile)
		{
			ICLogger::Warn("Load default font called for JP font construction, this should never be the case as the default font does not contain JP characters");
		}
		return LoadDefaultFont();
	}

	ImFontAtlas* FontAtlas = ImGui::GetIO().Fonts;

	// Get the font from the correct directory depending on whether it is an
	// EN font or JP font
	fs::path FilePath;
	if (bJPFile)
	{
		FilePath = TryGetJPFontFile(FileNameOrDefault);
	}
	else
	{
		FilePath = TryGetENFontFile(FileNameOrDefault);
	}

	// Get the correct font file, if this fails null is returned
	return FontAtlas->AddFontFromFileTTF(
		FilePath.string().c_str(), 
		FontSize, 
		Config, 
		Config->GlyphRanges
	);
}

bool FontLoader::TryLoadFont(MergedFont& FontToLoad)
{
	bool bLoadingSuccessful = true;
	ImFontAtlas* FontAtlas = ImGui::GetIO().Fonts;
	ImFontConfig Config = ImFontConfig();
	Config.GlyphRanges = CustomRanges.Data;

	// First, we clear whatever font was previously loaded.
	FontAtlas->Clear();

	try
	{
		// There are 4 cases for TryLoadFont:
		// 1. Default font for both EN and JP
		// 2. Default font for EN, font file for JP
		// 3. Font file for EN, default font for JP
		// 4. Font file both EN and JP

		// Note that the the default font does not contain JP glyphs, so
		// JP characters will show up as "?"

		const bool bLoadENDefault = FontToLoad.ENFontName == "Default";
		const bool bLoadJPDefault = FontToLoad.JPFontName == "Default";

		if (bLoadENDefault && bLoadJPDefault)
		{
			// Case 1: if default was passed in for both EN and JP,
			// we simply load the default font and set both font sizes
			// to 13
			FontToLoad.MergedFontData = LoadDefaultFont();
			//FontToLoad.FontSize = 13;
		}
		else
		{
			if (bLoadENDefault)
			{
				// Case 2: Default font for EN, font file for JP
				// In this case we change the current FontSize to 13
				// So that the JP font file is properly loaded, then
				// Load both fonts as normal
				//FontToLoad.FontSize = 13;
			}

			// Try to load the supplied EN font. Will load the default font at size 13
			// if "Default" was passed in
			ImFont* TryLoadENFont = LoadFontFromFileOrDefault(
				FontToLoad.ENFontName,
				FontToLoad.FontSize,
				&Config,
				false
			);

			// If the previous function returned null, it means that loading the font from the TTF
			// failed even though the file and directory were valid. This likely means the file found
			// was not a valid TTF file.
			if (TryLoadENFont == nullptr)
			{
				std::string ErrorMsg = std::format("Error loading English font, check that a valid TTF file was used: {}", FontToLoad.ENFontName);
				throw std::exception(ErrorMsg.c_str());
			}
			else
			{
				FontToLoad.MergedFontData = TryLoadENFont;
			}

			if (bLoadJPDefault)
			{
				// Case 3: Font file for EN, Default font for JP
				// In this case there is no point in doing anything
				// else since the default font does not contain JP
				// characters anyway.
			}
			else
			{

				// Enable merging now that one font has been loaded.
				Config.MergeMode = true;

				// Try to load the supplied JP font at Size (FontSize * FontMultiplier). 
				// Will load the default font at size 13 if "Default" was passed in, though for
				// the JP font this should never happen.
				ImFont* TryLoadJPFont = LoadFontFromFileOrDefault(
					FontToLoad.JPFontName,
					FontToLoad.FontSize * FontToLoad.JPFontSizeMultiplier,
					&Config,
					true
				);

				if (TryLoadJPFont == nullptr)
				{
					std::string ErrorMsg = std::format("Error loading Japanese font, check that a valid TTF file was used: {}", FontToLoad.JPFontName);
					throw std::exception(ErrorMsg.c_str());
				}
				else
				{
					FontToLoad.MergedFontData = TryLoadJPFont;
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		ICLogger::PushErrorNotification("Failed to load merged font", 3000,"Falling back to default font: {}", e.what());
		
		// Fall back to default font for both EN and JP if anything fails.
		FontToLoad.MergedFontData = LoadDefaultFont();
		FontToLoad.ENFontName = "Default";
		FontToLoad.JPFontName = "Default";
		//FontToLoad.FontSize = 13;
		bLoadingSuccessful = false;
	}

	// Once fonts have all been loaded, rebuil the font atlas.
	FontAtlas->Build();

	// Not sure why but this is needed whenever we load fonts
	// after ImGui OpenGL initialization.
	MainEditorWindow::Get()->GetGuiContext()->DestroyDeviceObjects();
	MainEditorWindow::Get()->GetGuiContext()->CreateDeviceObjects();

	return bLoadingSuccessful;
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