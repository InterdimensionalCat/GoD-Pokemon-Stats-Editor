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
			// Try to load each setting, but if any fail keep reading in case other settings are intact
			std::string StartupFont = "Default";
			int32_t StartupFontSize = 13;
			ImColor StartupFontColor = ImColor(220, 220, 220, 255);
			try
			{

				if (FontSettings->find("Startup Font") == FontSettings->end()) {
					throw std::exception("Startup Font json object does not exist");
				}

				StartupFont = (*FontSettings)["Startup Font"];
			}
			catch (const std::exception& e)
			{
				auto ErrorMsg = std::format("Failed to find Setting: Startup Font, falling back to default: {}", e.what());
				PushFontSettingsErrorMsg("Font setting not found", ErrorMsg);
			}

			try
			{
				if (FontSettings->find("Startup Font Size") == FontSettings->end()) {
					throw std::exception("Startup Font Size json object does not exist");
				}

				StartupFontSize = (*FontSettings)["Startup Font Size"];
			}
			catch (const std::exception& e)
			{
				auto ErrorMsg = std::format("Failed to find Setting: Startup Font Size, falling back to default: {}", e.what());
				PushFontSettingsErrorMsg("Font setting not found", ErrorMsg);
			}

			try
			{
				if (FontSettings->find("Startup Font Color") == FontSettings->end()) {
					throw std::exception("Startup Font Color json object does not exist");
				}

				if ((*FontSettings)["Startup Font Color"].find("R") == (*FontSettings)["Startup Font Color"].end() ||
					(*FontSettings)["Startup Font Color"].find("G") == (*FontSettings)["Startup Font Color"].end() ||
					(*FontSettings)["Startup Font Color"].find("B") == (*FontSettings)["Startup Font Color"].end())
				{
					throw std::exception("Startup Font Color json object not formatted correctly");
				}

				const float FontR = (*FontSettings)["Startup Font Color"]["R"];
				const float FontG = (*FontSettings)["Startup Font Color"]["G"];
				const float FontB = (*FontSettings)["Startup Font Color"]["B"];
				const float FontA = (*FontSettings)["Startup Font Color"]["A"];
				StartupFontColor = ImColor(FontR, FontG, FontB, FontA);
			}
			catch (const std::exception& e)
			{
				auto ErrorMsg = std::format("Failed to find Setting: Startup Font Color, falling back to default: {}", e.what());
				PushFontSettingsErrorMsg("Font setting not found", ErrorMsg);
			}

			StartupFontSize = std::clamp(StartupFontSize, MinFontSize, MaxFontSize);
			if (std::find(AvailableFonts.begin(), AvailableFonts.end(), StartupFont) == AvailableFonts.end())
			{
				throw std::exception("Startup font not found.");
			}

			SetActiveFont(FontKey(StartupFont, StartupFontSize));
			FontColor = StartupFontColor;
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
	ImColor StartupFontColor = ImColor(220, 220, 220, 255);

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

	FontSettings["Startup Font Color"]["R"] = FontColor.Value.x;
	FontSettings["Startup Font Color"]["G"] = FontColor.Value.y;
	FontSettings["Startup Font Color"]["B"] = FontColor.Value.z;
	FontSettings["Startup Font Color"]["A"] = FontColor.Value.w;
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
	// TODO: add current font color as a saved setting
	// Allow settings to be loaded from an imcomplete list (IE if some settings present but not others load the present settings)
	return FontColor;
}
