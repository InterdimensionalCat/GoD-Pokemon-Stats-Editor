#include "include.h"
#include "MainMenu/MainMenuSections/MenuView.h"

#include "MainEditor/MainEditorWindow.h"
#include "Font/FontManager.h"
#include "Settings/AppSettings.h"
#include "Font/FontSettings.h"

#include "UI/UiTab.h"
#include "UI/TabLayoutManager.h"
#include "Layout/LayoutSettings.h"

MenuView::MenuView() : MainMenuSection("View", 2)
{
	MainFontManager = DataEditorInstance::Get()->GetMainEditorWindow()->GetFontManager();
}

void MenuView::Tick()
{
	const MergedFont& CurrentFont = MainFontManager->GetCurrentlyLoadedFont();
	const int32_t MaxFontSize = MainFontManager->GetMaxFontSize();
	const int32_t MinFontSize = MainFontManager->GetMinFontSize();
	const int32_t CurrentFontSize = CurrentFont.FontSize;
	const ImColor FontColor = CurrentFont.FontColor;

	// English font settings menu
	ImGui::SeparatorText("Font Settings");

	// First option is a selector for the current EN font
	if (ImGui::BeginMenu("Current EN Font"))
	{
		for (const std::string& AvailableFont : MainFontManager->GetAvailableENFonts())
		{
			const bool bSelected = AvailableFont == MainFontManager->GetCurrentlyLoadedFont().ENFontName;
			if (ImGui::MenuItem(AvailableFont.c_str(), nullptr, bSelected, !bSelected))
			{
				MainFontManager->SetCurrentENFont(AvailableFont);
			}
		}

		ImGui::EndMenu();
	}

	// Next we need a font selector for the current JP font.
	if (ImGui::BeginMenu("Current JP Font (日本語) (♂/♀)"))
	{
		for (const std::string& AvailableFont : MainFontManager->GetAvailableJPFonts())
		{
			const bool bSelected = AvailableFont == MainFontManager->GetCurrentlyLoadedFont().JPFontName;
			if (ImGui::MenuItem(AvailableFont.c_str(), nullptr, bSelected, !bSelected))
			{
				MainFontManager->SetCurrentJPFont(AvailableFont);
			}
		}

		ImGui::EndMenu();
	}

	// After that, render the font size increase/decrease options.

	// Allow font increase/decrease if we are not at the max/min font size, respectively.
	const bool bFontIncreaseEnabled = CurrentFontSize < MaxFontSize;

	if (ImGui::MenuItem("Increase Font Size", "Ctrl+=", nullptr, bFontIncreaseEnabled))
	{
		MainFontManager->SetCurrentFontSize(CurrentFontSize + 1);
	}

	// Allow font increase/decrease if we are not at the max/min font size, respectively.
	const bool bFontDecreaseEnabled = CurrentFontSize > MinFontSize;

	if (ImGui::MenuItem("Decrease Font Size", "Ctrl+-", nullptr, bFontDecreaseEnabled))
	{
		MainFontManager->SetCurrentFontSize(CurrentFontSize - 1);
	}

	// After that, render the float entry for the JP font size multiplier.
	if (ImGui::BeginMenu("Change JP Font Size Multiplier"))
	{
		float NewJPFontSizeMultiplier = CurrentFont.JPFontSizeMultiplier;
		if (ImGui::InputFloat("JP Font Size Multiplier", &NewJPFontSizeMultiplier, 0.f, 0.f, "%.1f"))
		{
			// We only want to update the settings when we commit the text, so do nothing here
		}

		if (ImGui::IsItemDeactivatedAfterEdit())
		{
			MainFontManager->SetCurrentJPFontSizeMultiplier(NewJPFontSizeMultiplier);
		}

		ImGui::EndMenu();
	}

	// Finally, we have the font color selector.
	if (ImGui::BeginMenu("Change Font Color"))
	{
		ImGuiColorEditFlags Flags = (ImGuiColorEditFlags)0;
		Flags |= ImGuiColorEditFlags_DisplayRGB;
		Flags |= ImGuiColorEditFlags_InputRGB;

		float RGB[3] = { FontColor.Value.x, FontColor.Value.y, FontColor.Value.z };

		if (ImGui::ColorEdit3("Font Color", RGB, Flags))
		{
			MainFontManager->SetCurrentFontColor(ImColor(RGB[0], RGB[1], RGB[2]));
		}
		ImGui::EndMenu();
	}

	TickLayoutSettings();
}

void MenuView::TickLayoutSettings()
{
	auto FocusedTab = MainEditorWindow::Get()->GetLastFocusedTab();

	if (FocusedTab != nullptr)
	{
		auto TabName = FocusedTab->GetName();

		ImGui::SeparatorText(std::format("{} Layout Settings", TabName).c_str());

		auto LayoutSettings = FocusedTab->GetLayoutManager()->GetLayoutSettings();
		auto ReloadPresetOnStartup = LayoutSettings->GetReloadPresetOnStartup();
		auto AvailablePresetLayouts = FocusedTab->GetLayoutManager()->GetAvailableLayouts();
		auto CurrentPresetLayout = LayoutSettings->GetCurrentPreset();

		if (ImGui::BeginMenu("Current Preset"))
		{
			for (auto& AvailableLayout : AvailablePresetLayouts)
			{
				const bool bSelected = AvailableLayout == CurrentPresetLayout;
				if (ImGui::MenuItem(AvailableLayout.c_str(), nullptr, bSelected, !bSelected))
				{
					LayoutSettings->SetCurrentPreset(AvailableLayout);
					FocusedTab->GetLayoutManager()->ReloadLayoutNextTick();
				}
			}

			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Reload Layout On Startup", "", ReloadPresetOnStartup, true))
		{
			LayoutSettings->SetReloadPresetOnStartup(!ReloadPresetOnStartup);
		}
	}
}

void MenuView::CheckShortcuts()
{

	const MergedFont& CurrentFont = MainFontManager->GetCurrentlyLoadedFont();
	const int32_t MaxFontSize = MainFontManager->GetMaxFontSize();
	const int32_t MinFontSize = MainFontManager->GetMinFontSize();
	const int32_t CurrentFontSize = CurrentFont.FontSize;

	// Increase Font Size (Ctrl+=)
	if (IsChordPressedAndNotRouted(IncreaseFontShortcut))
	{

		// Allow font increase/decrease if we are not at the max/min font size, respectively.
		const bool bFontIncreaseEnabled = CurrentFontSize < MaxFontSize;

		if (bFontIncreaseEnabled)
		{
			MainFontManager->SetCurrentFontSize(CurrentFontSize + 1);
		}
	}

	// Decrease Font Size (Ctrl+-)
	if (IsChordPressedAndNotRouted(DecreaseFontShortcut))
	{
		// Allow font increase/decrease if we are not at the max/min font size, respectively.
		const bool bFontDecreaseEnabled = CurrentFontSize > MinFontSize;

		if (bFontDecreaseEnabled)
		{
			MainFontManager->SetCurrentFontSize(CurrentFontSize - 1);
		}
	}
}
