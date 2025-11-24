#include "include.h"
#include "MainMenu/MainMenuSections/MenuSettings.h"

#include "Settings/AppSettings.h"
#include "Settings/SettingsSection/GeneralSettingsSection.h"
#include "MainEditor/MainEditorWindow.h"

MenuSettings::MenuSettings() : MainMenuSection("Settings", 3)
{
	auto GeneralSettings = MainEditorWindow::Get()->GetSettings()->GetGeneralSettings();
}

void MenuSettings::Tick()
{
	auto GeneralSettings = MainEditorWindow::Get()->GetSettings()->GetGeneralSettings();
	auto AutoOpenLastRoot = GeneralSettings->GetAutoOpenLastRoot();
	
	if (ImGui::MenuItem("Load Previous Root on Startup", "", AutoOpenLastRoot, true))
	{
		GeneralSettings->SetAutoOpenLastRoot(!AutoOpenLastRoot);
	}
}

void MenuSettings::CheckShortcuts()
{

}