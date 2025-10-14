#include "include.h"
#include "Font/FontManager.h"
#include "Font/FontLoader.h"
#include "Font/FontSettings.h"

#include "Settings/AppSettings.h"
#include "MainEditor/DataEditorInstance.h"
#include "MainEditor/MainEditorWindow.h"

FontManager::FontManager()
{

}

void FontManager::Init()
{
	ICLogger::Debug("Initializing FontManager...");
	// Get a handle to the font settings since we will need to reference them every frame.
	MainFontSettings = DataEditorInstance::Get()->GetMainEditorWindow()->GetSettings()->GetFontSettings();

	// This will build the custom ranges needed for merged fonts.
	MainFontLoader = std::make_shared<FontLoader>();

	FindAvailableFonts();

	// Set font params based on the loaded font settings.
	SetCurrentENFont(MainFontSettings->GetENFont());
	SetCurrentJPFont(MainFontSettings->GetJPFont());
	SetCurrentFontSize(MainFontSettings->GetFontSize());
	SetCurrentJPFontSizeMultiplier(MainFontSettings->GetJPFontSizeMultiplier());
	SetCurrentFontColor(MainFontSettings->GetFontColor());

	ICLogger::Debug("FontManager initialized.");
}

void FontManager::FindAvailableFonts()
{
	ICLogger::Trace("Finding available fonts...");
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
				ICLogger::Trace("EN font found: {}", File.filename().string());
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
				ICLogger::Trace("JP font found: {}", File.filename().string());
				AvailableJPFonts.push_back(File.filename().string());
			}
		}
	}
}

void FontManager::CheckForFontChanged()
{
	if (bShouldReloadFont)
	{
		ICLogger::Debug("bShouldReloadFont set, attempting to load font: {}", CurrentlyLoadedFont.ToString());

		// TryLoadFont will supply CurrentlyLoadedFont with a new ImFont pointer to the
		// Newly created font.
		if (!MainFontLoader->TryLoadFont(CurrentlyLoadedFont))
		{
			ICLogger::Warn("Failed to load font: {}", CurrentlyLoadedFont.ToString());
		}

		MainEditorWindow::Get()->ForceRecalculateSizeConstraints();
		bShouldReloadFont = false;
	}
}

void FontManager::SetupFontForFrame()
{
	ImGui::PushStyleColor(ImGuiCol_Text, CurrentlyLoadedFont.FontColor.Value);
	ImGui::PushFont(CurrentlyLoadedFont.MergedFontData, CurrentlyLoadedFont.FontSize);
}

void FontManager::EndFontForFrame()
{
	ImGui::PopStyleColor(); // Font color
	ImGui::PopFont(); // Font style
}

void FontManager::SaveCurrentFontToFontSettings()
{
	ICLogger::Debug("Saving current font to FontSettings: {}", CurrentlyLoadedFont.ToString());
	MainFontSettings->SetENFont(CurrentlyLoadedFont.ENFontName);
	MainFontSettings->SetJPFont(CurrentlyLoadedFont.JPFontName);
	MainFontSettings->SetFontSize(CurrentlyLoadedFont.FontSize);
	MainFontSettings->SetJPFontSizeMultiplier(CurrentlyLoadedFont.JPFontSizeMultiplier);
	MainFontSettings->SetFontColor(CurrentlyLoadedFont.FontColor);
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

void FontManager::SetCurrentENFont(const std::string& NewFontName)
{
	CurrentlyLoadedFont.ENFontName = NewFontName;
	bShouldReloadFont = true;

	ICLogger::PushInfoNotification(
		"EN Font Changed",
		2000,
		"EN Font Changed to {}",
		NewFontName
	);
}

void FontManager::SetCurrentJPFont(const std::string& NewFontName)
{
	CurrentlyLoadedFont.JPFontName = NewFontName;
	bShouldReloadFont = true;

	ICLogger::PushInfoNotification(
		"JP Font Changed",
		2000,
		"JP Font Changed to {}",
		NewFontName
	);
}

void FontManager::SetCurrentFontSize(const int32_t NewFontSize)
{
	// Font size is dynamic so we don't need to reload the font.
	CurrentlyLoadedFont.FontSize = NewFontSize;

	ICLogger::PushInfoNotification(
		"Font Size Changed",
		2000,
		"Font Size Changed to {}",
		NewFontSize
	);

	MainEditorWindow::Get()->ForceRecalculateSizeConstraints();
}

void FontManager::SetCurrentJPFontSizeMultiplier(const float NewFontSizeMultiplier)
{
	CurrentlyLoadedFont.JPFontSizeMultiplier = NewFontSizeMultiplier;
	bShouldReloadFont = true;

	ICLogger::PushInfoNotification(
		"JP Font Size Multiplier Changed",
		2000,
		"JP Font Size Multiplier Changed to {}",
		NewFontSizeMultiplier
	);
}

void FontManager::SetCurrentFontColor(const ImColor& NewColor)
{
	CurrentlyLoadedFont.FontColor = NewColor;
}