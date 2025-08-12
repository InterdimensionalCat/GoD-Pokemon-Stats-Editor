#include "include.h"
#include "Font/FontManager.h"

#include "Settings/AppSettings.h"
#include "MainEditor/DataEditorInstance.h"
#include "MainEditor/MainEditorWindow.h"

FontManager::FontManager()
{

}

void FontManager::Init()
{
	// Get a handle to the font settings since we will need to reference them every frame.
	MainFontSettings = DataEditorInstance::Get()->GetMainEditorWindow()->GetSettings()->GetFontSettings();

	// This will build the custom ranges needed for merged fonts.
	MainFontLoader = std::make_shared<FontLoader>();

	FindAvailableFonts();
}

void FontManager::FindAvailableFonts()
{

	AvailableENFonts.clear();
	AvailableJPFonts.clear();

	std::filesystem::path FontDirectory = std::filesystem::current_path();
	FontDirectory /= "Resources";
	FontDirectory /= "Fonts";

	fs::path ENFontsDirectory = FontDirectory / "EN";
	fs::path JPFontsDirectory = FontDirectory / "JP";

	AvailableENFonts.push_back("Default");

	if (!std::filesystem::is_directory(ENFontsDirectory))
	{
		ICLogger::Warn("EN fonts directory not found: {}", ENFontsDirectory.string());
	}
	else
	{
		for (const fs::path& File : fs::directory_iterator(ENFontsDirectory))
		{
			if (File.extension() == ".ttf" || File.extension() == ".otf")
			{
				ICLogger::Info("EN font found: {}", File.filename().string());
				AvailableENFonts.push_back(File.filename().string());
			}
		}
	}

	AvailableJPFonts.push_back("Default");

	if (!std::filesystem::is_directory(JPFontsDirectory))
	{
		ICLogger::Warn("JP fonts directory not found: {}", JPFontsDirectory.string());
	}
	else
	{
		for (const fs::path& File : fs::directory_iterator(JPFontsDirectory))
		{
			if (File.extension() == ".ttf" || File.extension() == ".otf")
			{
				ICLogger::Info("JP font found: {}", File.filename().string());
				AvailableJPFonts.push_back(File.filename().string());
			}
		}
	}
}

void FontManager::CheckForFontChanged()
{
	// If either of the font names missmatch the current setting,
	// Or of the font size mismatches, we need to reload and rebuild
	// the merged font.
	const std::string ENFontName = MainFontSettings->GetCurrentENFont();
	const std::string JPFontName = MainFontSettings->GetCurrentJPFont();
	const int32_t FontSize = MainFontSettings->GetFontSize();

	if (
		ENFontName != CurrentlyLoadedFont.ENFontName ||
		JPFontName != CurrentlyLoadedFont.JPFontName ||
		FontSize != CurrentlyLoadedFont.FontSize
		)
	{
		CurrentlyLoadedFont = MainFontLoader->TryLoadFont(ENFontName, JPFontName, FontSize);

		// Ensure that fonts get built here
		//ImFontAtlas* FontAtlas = ImGui::GetIO().Fonts;
		//FontAtlas->Build();
		//if (FontAtlas->IsBuilt())
		//{
		//	ICLogger::Debug("Font Atlas built after changing fonts.");
		//}

	}

	// Update the current font color as well.
	CurrentFontColor = MainFontSettings->GetFontColor();
}

void FontManager::SetupFontForFrame()
{
	ImGui::PushStyleColor(ImGuiCol_Text, CurrentFontColor.Value);
	ImGui::PushFont(CurrentlyLoadedFont.MergedFontData);
	// ImGui::PushFontSize()
}

void FontManager::EndFontForFrame()
{
	ImGui::PopStyleColor(); // Font color
	ImGui::PopFont(); // Font style
}

const std::vector<std::string>& FontManager::GetAvailableENFonts() const
{
	return AvailableENFonts;
}

const std::vector<std::string>& FontManager::GetAvailableJPFonts() const
{
	return AvailableJPFonts;
}

const MergedFont& FontManager::GetCurrentlyLoadedFont() const
{
	return CurrentlyLoadedFont;
}

int32_t FontManager::GetMinFontSize() const
{
	return MinFontSize;
}

int32_t FontManager::GetMaxFontSize() const
{
	return MaxFontSize;
}

const ImColor& FontManager::GetCurrentFontColor() const
{
	return CurrentFontColor;
}