#include "include.h"
#include "UI/TabLayoutManager.h"

#include "UI/UiTab.h"
#include "MainEditor/MainEditorWindow.h"
#include "Settings/AppSettings.h"
#include "Layout/LayoutSettings.h"

// TODO: allow users to save/load custom layouts.
// This is non-trivial to implement because ImGui
// does not let you save/load layout settings for
// individual windows, only the entire dockspace.
// so we will need to parse the ini file manually
// and only save the relevant settings for a window.
TabLayoutManager::TabLayoutManager(UiTab* InParentTab)
	: ParentTab(InParentTab)
{

}

void TabLayoutManager::Tick()
{
	if (bShouldReloadLayoutNextTick)
	{
		LoadCurrentLayout();

		auto MainEditor = DataEditorInstance::Get()->GetMainEditorWindow();
		MainEditor->RefreshTabDocksace();

		bShouldReloadLayoutNextTick = false;
	}
}

void TabLayoutManager::TabOpened()
{
	LoadOrCreateLayoutSettings();

	// TODO: get from layout settings.
	ICLogger::Info("Current layout for tab {} set to {}", ParentTab->GetName(), TabLayoutSettings->GetCurrentPreset());

	if (TabLayoutSettings->GetReloadPresetOnStartup())
	{
		ICLogger::Info("Reloading preset layout {} for tab {} on startup", TabLayoutSettings->GetCurrentPreset(), ParentTab->GetName());
		bShouldReloadLayoutNextTick = true;
	}
}

void TabLayoutManager::LoadOrCreateLayoutSettings()
{
	ICLogger::Info("Getting or creating layout settings for tab {}", ParentTab->GetName());
	auto Settings = MainEditorWindow::Get()->GetSettings();
	TabLayoutSettings = Settings->GetLayoutSettingsForTab(GetParentTab()->GetName());

	if (TabLayoutSettings == nullptr)
	{
		ICLogger::Warn("Layout settings not found for tab {}, creating new layout settings.", ParentTab->GetName());
		TabLayoutSettings = std::make_shared<LayoutSettings>(GetParentTab()->GetName());
		Settings->AddSection(TabLayoutSettings);

		// Always reload layout if we just created new layout settings.	
		bShouldReloadLayoutNextTick = true;
	}
	else
	{
		ICLogger::Info("Existing layout settings found for tab {}", ParentTab->GetName());
	}
}

void TabLayoutManager::LoadCurrentLayout()
{
	const std::string CurrentLayout = TabLayoutSettings->GetCurrentPreset();
	ICLogger::Info("Loading layout {} for tab {}", CurrentLayout, ParentTab->GetName());
	if (CurrentLayout == "Default")
	{
		LoadDefaultLayout();
	}
	else
	{
		// TODO: load named preset layout.

		auto LayoutDir = GetLayoutDirectory();

		if (!fs::exists(LayoutDir) ||
			!fs::is_directory(LayoutDir))
		{
			ICLogger::Warn("Layout directory {} does not exist, cannot load layout {}", LayoutDir.string(), CurrentLayout);
			LoadDefaultLayout();
			return;
		}

		LayoutDir /= CurrentLayout + ".ini";

		try
		{
			TabLayoutSettings->TryLoadLayout(LayoutDir);
		}
		catch (const std::exception& e)
		{
			ICLogger::Warn("Failed to load layout {}: {}, loading default layout instead", LayoutDir.string(), e.what());
			LoadDefaultLayout();
			return;
		}

		ICLogger::Info("Successfully loaded layout {} for tab {}", CurrentLayout, ParentTab->GetName());

		if (TabLayoutSettings->GetCurrentPreset() != CurrentLayout)
		{
			TabLayoutSettings->SetCurrentPreset(CurrentLayout);
		}
	}
}

void TabLayoutManager::LoadDefaultLayout()
{
	ParentTab->LoadDefaultLayout();
}

void TabLayoutManager::ReloadLayoutNextTick()
{
	bShouldReloadLayoutNextTick = true;
}

UiTab* TabLayoutManager::GetParentTab()
{
	return ParentTab;
}

const UiTab* TabLayoutManager::GetParentTab() const
{
	return ParentTab;
}

fs::path TabLayoutManager::GetLayoutDirectory() const
{
	fs::path LayoutDir = std::filesystem::current_path();
	LayoutDir /= "Resources";
	LayoutDir /= "Layouts";
	LayoutDir /= GetParentTab()->GetName();

	return LayoutDir;
}

std::shared_ptr<LayoutSettings> TabLayoutManager::GetLayoutSettings() const
{
	return TabLayoutSettings;
}

std::vector<std::string> TabLayoutManager::GetAvailableLayouts() const
{
	std::vector<std::string> OutLayouts;
	fs::path LayoutDir = GetLayoutDirectory();
	if (!fs::exists(LayoutDir) ||
		!fs::is_directory(LayoutDir))
	{
		ICLogger::Warn("Layout directory {} does not exist, cannot get available layouts", LayoutDir.string());
		return OutLayouts;
	}

	OutLayouts.push_back("Default");

	for (const auto& Entry : fs::directory_iterator(LayoutDir))
	{
		if (Entry.is_regular_file() &&
			Entry.path().extension() == ".ini")
		{
			OutLayouts.push_back(Entry.path().stem().string());
		}
	}
	return OutLayouts;
}