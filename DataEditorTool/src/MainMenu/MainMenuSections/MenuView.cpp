#include "include.h"
#include "MainMenu/MainMenuSections/MenuView.h"

#include "MainEditor/MainEditorWindow.h"
#include "Font/FontManager.h"
#include "Settings/AppSettings.h"
#include "Settings/SettingsSection/FontSettings.h"

MenuView::MenuView() : MainMenuSection("View", 2)
{
	MainFontManager = DataEditorInstance::Get()->GetMainEditorWindow()->GetFontManager();
	MainFontSettings = DataEditorInstance::Get()->GetMainEditorWindow()->GetSettings()->GetFontSettings();
}

void MenuView::Tick()
{
	//CurrentSettings->GetLayoutSettings()->DisplayLayoutMenu();

	// English font settings menu
	ImGui::SeparatorText("English Font Settings");
	
	// First option is a selector for the current EN font
	if (ImGui::BeginMenu("Current Font##EN"))
	{
		for (const std::string& AvailableFont : MainFontManager->GetAvailableENFonts())
		{
			const bool bSelected = AvailableFont == MainFontManager->GetCurrentlyLoadedFont().ENFontName;
			if (ImGui::MenuItem(AvailableFont.c_str(), nullptr, bSelected, !bSelected))
			{
				MainFontSettings->SetCurrentENFont(AvailableFont);
			}
		}

		ImGui::EndMenu();
	}

	// Next we need a font selector for the current JP font.
	if (ImGui::BeginMenu("Current Font (日本語)"))
	{
		for (const std::string& AvailableFont : MainFontManager->GetAvailableJPFonts())
		{
			const bool bSelected = AvailableFont == MainFontManager->GetCurrentlyLoadedFont().JPFontName;
			if (ImGui::MenuItem(AvailableFont.c_str(), nullptr, bSelected, !bSelected))
			{
				MainFontSettings->SetCurrentJPFont(AvailableFont);
			}
		}

		ImGui::EndMenu();
	}

	// After that, render the font size increase/decrease options.
	const MergedFont& CurrentFont = MainFontManager->GetCurrentlyLoadedFont();
	const int32_t MaxFontSize = MainFontManager->GetMaxFontSize();
	const int32_t MinFontSize = MainFontManager->GetMinFontSize();

	// Font sizing is not allowed if we are using the default font, otherwise
	// Allow it only if we are not at the max/min font size, respectively.
	const bool bFontIncreaseEnabled = (CurrentFont.FontSize < MaxFontSize) &&
		CurrentFont.ENFontName != "Default";

	if (ImGui::MenuItem("Increase Font Size", "Ctrl+=", nullptr, bFontIncreaseEnabled))
	{
		MainFontSettings->SetFontSize(CurrentFont.FontSize + 1);
	}

	const bool bFontDecreaseEnabled = (CurrentFont.FontSize > MinFontSize) &&
		CurrentFont.ENFontName != "Default";

	if (ImGui::MenuItem("Decrease Font Size", "Ctrl+-", nullptr, bFontDecreaseEnabled))
	{
		MainFontSettings->SetFontSize(CurrentFont.FontSize - 1);
	}

	const ImColor FontColor = MainFontManager->GetCurrentFontColor();

	// Finally, we have the font color selector.
	if (ImGui::BeginMenu("Change Font Color"))
	{
		ImGuiColorEditFlags Flags = (ImGuiColorEditFlags)0;
		Flags |= ImGuiColorEditFlags_DisplayRGB;
		Flags |= ImGuiColorEditFlags_InputRGB;

		float RGB[3] = { FontColor.Value.x, FontColor.Value.y, FontColor.Value.z };

		if (ImGui::ColorEdit3("Font Color", RGB, Flags))
		{
			MainFontSettings->SetFontColor(ImColor(RGB[0], RGB[1], RGB[2]));
		}
		ImGui::EndMenu();
	}
}

void MenuView::CheckShortcuts()
{

	const MergedFont& CurrentFont = MainFontManager->GetCurrentlyLoadedFont();
	const int32_t MaxFontSize = MainFontManager->GetMaxFontSize();
	const int32_t MinFontSize = MainFontManager->GetMinFontSize();

	// Increase Font Size (Ctrl+=)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Equal, false) && 
		(ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || 
			ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{

		// Font sizing is not allowed if we are using the default font, otherwise
		// Allow it only if we are not at the max/min font size, respectively.
		const bool bFontIncreaseEnabled = (CurrentFont.FontSize < MaxFontSize) &&
			CurrentFont.ENFontName != "Default";

		if (bFontIncreaseEnabled)
		{
			MainFontSettings->SetFontSize(CurrentFont.FontSize + 1);
		}
	}

	// Decrease Font Size (Ctrl+-)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Minus, false) && 
		(ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || 
			ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{

		// Font sizing is not allowed if we are using the default font, otherwise
		// Allow it only if we are not at the max/min font size, respectively.
		const bool bFontDecreaseEnabled = (CurrentFont.FontSize > MinFontSize) &&
			CurrentFont.ENFontName != "Default";

		if (bFontDecreaseEnabled)
		{
			MainFontSettings->SetFontSize(CurrentFont.FontSize - 1);
		}
	}
}
