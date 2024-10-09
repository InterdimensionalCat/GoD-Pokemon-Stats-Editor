#include "FontSettings.h"
#include "GoD-UI-Windows.h"
#include <filesystem>
#include <tuple>

#include "imgui/backends/ImGuiNotify.hpp"

FontSettings::FontSettings()
{
	AvailableFonts.push_back("Default");
	ResetFontSettings(false);
}

void FontSettings::Init(const nlohmann::json* FontSettings)
{
	// Attempt to load font from font settings
	try
	{
		// Build glyph ranges for Male/Female symbol.
		ImGuiIO& io = ImGui::GetIO();
		ImFontGlyphRangesBuilder builder;
		builder.AddRanges(io.Fonts->GetGlyphRangesDefault());
		//builder.AddRanges(io.Fonts->GetGlyphRangesJapanese());

		static const ImWchar ranges[] =
		{
	    0x2640, 0x2642, // glyph range for male/female symbol
		0,
		};

		builder.AddRanges(ranges);

		// Female symbol.
		builder.AddChar(0xE2);
		builder.AddChar(0x99);
		builder.AddChar(0x80);
		//builder.AddChar((ImWchar)u8"\u2640");

		// Male symbol.
		builder.AddChar(0xE2);
		builder.AddChar(0x99);
		builder.AddChar(0x82);
		//builder.AddChar((ImWchar)u8"\u2642");

		builder.BuildRanges(&MaleFemaleRanges);

		std::filesystem::path FontDirectory = std::filesystem::current_path();
		FontDirectory /= "Resources";
		FontDirectory /= "Fonts";

		if (!std::filesystem::is_directory(FontDirectory))
		{
			std::string ErrorMsg = std::format("Fonts directory not found: {}", FontDirectory.string());
			throw std::exception(ErrorMsg.c_str());
		}

		// Add all fonts in the fonts directory to AvailableFonts
		for (const std::filesystem::path& File : std::filesystem::directory_iterator(FontDirectory))
		{
			if (File.extension() == ".ttf" || File.extension() == ".otf")
			{
				AvailableFonts.push_back(File.filename().string());
			}
		}

		for (auto& FontName : AvailableFonts)
		{
			for (int32_t i = MinFontSize; i <= MaxFontSize; i++)
			{
				auto LoadedFont = TryLoadFont(FontDirectory, FontName, i);
				if (LoadedFont != nullptr)
				{
					LoadedFonts.emplace(FontKey(FontName, i), LoadedFont);
				}
			}
		}

		// Load default settings if no font settings existed.
		if (FontSettings == nullptr)
		{
			ResetFontSettings(false);
			ImGuiIO& io = ImGui::GetIO();
			ImFontConfig Config = ImFontConfig();
			Config.GlyphRanges = MaleFemaleRanges.Data;
			LoadedFonts.emplace(FontKey("Default", 13), io.Fonts->AddFontDefault(&Config));
			return;
		}
		else
		{
			// Otherwise attempt to load the startup font from settings.
			const std::string StartupFont = (*FontSettings)["Startup Font"];
			int32_t StartupFontSize = (*FontSettings)["Startup Font Size"];

			StartupFontSize = std::clamp(StartupFontSize, MinFontSize, MaxFontSize);
			if (std::find(AvailableFonts.begin(), AvailableFonts.end(), StartupFont) == AvailableFonts.end())
			{
				throw std::exception("Startup font not found.");
			}

			SetActiveFont(FontKey(StartupFont, StartupFontSize));
		}
	}
	catch (const std::exception& e)
	{
		auto ErrorMsg = std::format("Failed to load font settings, falling back to defaults: {}", e.what());
		PushFontSettingsErrorMsg("Font loading failed", ErrorMsg);
		ResetFontSettings(false);

		ImGuiIO& io = ImGui::GetIO();
		LoadedFonts.emplace(FontKey("Default", 13), io.Fonts->AddFontDefault());
	}
}

void FontSettings::DisplayFontMenu()
{
	ImGui::SeparatorText("Font Settings");
	if (ImGui::BeginMenu("Current Font"))
	{
		for (auto& AvailableFont : AvailableFonts)
		{
			const bool bSelected = AvailableFont == ActiveFont.first;
			if (ImGui::MenuItem(AvailableFont.c_str(), nullptr, bSelected, !bSelected))
			{
				if (AvailableFont == "Default")
				{
					ResetFontSettings(true);
				}
				else
				{
					SetActiveFont(FontKey(AvailableFont, ActiveFont.second));
				}
			}
		}
		ImGui::EndMenu();
	}

	bool bIncreaseEnabled = (ActiveFont.second < MaxFontSize) && ActiveFont.first != "Default";
	if (ImGui::MenuItem("Increase Font Size", "Ctrl+=", nullptr, bIncreaseEnabled))
	{
		SetActiveFont(FontKey(ActiveFont.first, ActiveFont.second + 1));
	}

	bool bDecreaseEnabled = (ActiveFont.second > MinFontSize) && ActiveFont.first != "Default";
	if (ImGui::MenuItem("Decrease Font Size", "Ctrl+-", nullptr, bDecreaseEnabled))
	{
		SetActiveFont(FontKey(ActiveFont.first, ActiveFont.second - 1));
	}

	if (ImGui::BeginMenu("Change Font Color"))
	{
		ImGuiColorEditFlags Flags = (ImGuiColorEditFlags)0;
		Flags |= ImGuiColorEditFlags_DisplayRGB;
		Flags |= ImGuiColorEditFlags_InputRGB;

		float RGB[3] = { FontColor.Value.x, FontColor.Value.y, FontColor.Value.z };

		if (ImGui::ColorEdit3("Font Color", RGB, Flags))
		{
			FontColor = ImColor(RGB[0], RGB[1], RGB[2]);
		}
		ImGui::EndMenu();
	}
}

void FontSettings::SetActiveFont(const FontKey& NewFont)
{

	bool bFontChanged = ActiveFont.first != NewFont.first;

	ActiveFont = NewFont;
	SetFontChanged(true);

	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Info, 2000);
	std::string Msg;
	if (bFontChanged)
	{
		toast->setTitle("Font changed");
		Msg = std::format("Font set to {}.", NewFont.first);
	}
	else
	{
		toast->setTitle("Font size changed");
		Msg = std::format("Font size set to {}.", NewFont.second);
	}

	std::cout << Msg << "\n";
	toast->setContent("%s", Msg.c_str());
	ImGui::InsertNotification(*toast);
}

FontKey FontSettings::GetActiveFontKey() const
{
	return ActiveFont;
}

ImFont* FontSettings::GetCurrentFont()
{
	return LoadedFonts.at(ActiveFont);
}

std::vector<std::string> FontSettings::GetFontsAvailable()
{
	return AvailableFonts;
}

ImFont* FontSettings::TryLoadFont(const std::filesystem::path& Directory, const std::string& FontFileName, const int32_t FontSize)
{
	try
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig Config = ImFontConfig();
		Config.GlyphRanges = MaleFemaleRanges.Data;

		if (FontFileName == "Default")
		{
			auto RetVal = io.Fonts->AddFontDefault(&Config);
			io.Fonts->Build();
			return RetVal;
		}
		else
		{
			std::filesystem::path FontFilePath = Directory / FontFileName;

			if (!std::filesystem::exists(FontFilePath))
			{
				std::string ErrorMsg = std::format("Font not found: {}", FontFilePath.string());
				throw std::exception(ErrorMsg.c_str());
			}

			ImFont* TryLoadFont = io.Fonts->AddFontFromFileTTF(FontFilePath.string().c_str(), FontSize, NULL, Config.GlyphRanges);

			if (TryLoadFont == nullptr)
			{
				std::string ErrorMsg = std::format("Error loading font: {}", FontFilePath.string());
				throw std::exception(ErrorMsg.c_str());
			}

			return TryLoadFont;
		}
	}
	catch (const std::exception& e)
	{
		auto ErrorMsg = std::format("Failed to load font {}: {}", FontFileName, e.what());
		PushFontSettingsErrorMsg("Font loading failed", ErrorMsg);
		return nullptr;
	}
}

void FontSettings::ResetFontSettings(const bool ReloadElements)
{
	ActiveFont = FontKey("Default", 13);

	if (ReloadElements)
	{
		SetFontChanged(true);

		std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
		std::string Msg;
		toast->setTitle("Font changed");
		Msg = "Font set to Default.";

		std::cout << Msg << "\n";
		toast->setContent("%s", Msg.c_str());
		ImGui::InsertNotification(*toast);
	}
}

void FontSettings::SaveFontSettings(nlohmann::json& FontSettings)
{
	FontSettings["Startup Font"] = ActiveFont.first;
	FontSettings["Startup Font Size"] = ActiveFont.second;
}

void FontSettings::PushFontSettingsErrorMsg(const std::string& ErrorTitle, const std::string& ErrorMsg)
{
	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
	toast->setTitle(ErrorTitle.c_str());
	std::cout << ErrorMsg << "\n";
	toast->setContent("%s", ErrorMsg.c_str());
	ImGui::InsertNotification(*toast);
}

void FontSettings::SetFontChanged(const bool InChanged)
{
	bFontChanged = InChanged;
}

bool FontSettings::GetFontChanged() const
{
	return bFontChanged;
}

ImColor FontSettings::GetFontColor() const
{
	return FontColor;
}
