#include "include.h"
#include "MainMenu/MainMenuSections/MenuFile.h"

#include "MainEditor/MainEditorWindow.h"
#include "MainEditor/ProjectRoot.h"
#include "Modal/ModalManager.h"
#include "Modal/Modal.h"
#include "Modal/BlockUnsavedProgress.h"
#include "CSV/CSVDatabase.h"
#include "Settings/AppSettings.h"
#include "Settings/SettingsSection/GeneralSettingsSection.h"

MenuFile::MenuFile() : MainMenuSection("File", 0)
{

}

void MenuFile::Tick()
{

	const bool AreCSVFilesModified = GoDCSV::CSVDatabase::Get()->AreAnyCSVFilesModified();

	if (ImGui::MenuItem("Set Root Folder", ImGui::GetKeyChordName(SetRootShortcut)))
	{
		SetProjectRootPath();
	}

	auto GeneralSettings = MainEditorWindow::Get()->GetSettings()->GetGeneralSettings();
	auto AutoOpenLastRoot = GeneralSettings->GetAutoOpenLastRoot();
	if (ImGui::MenuItem("Load Previous Root on Startup", "", AutoOpenLastRoot, true))
	{
		GeneralSettings->SetAutoOpenLastRoot(!AutoOpenLastRoot);
	}

	if (ImGui::MenuItem("Save All", ImGui::GetKeyChordName(SaveShortcut), nullptr, IsProjectRootPathSet() && AreCSVFilesModified))
	{
		SaveAll();
	}
	if (ImGui::MenuItem("Save Selected", "", nullptr, IsProjectRootPathSet() && AreCSVFilesModified))
	{
		SaveSelected();
	}
	if (ImGui::MenuItem("Close Current Root", "", nullptr, IsProjectRootPathSet()))
	{
		CloseCurrentRoot();
	}
}

void MenuFile::CheckShortcuts()
{
	const bool AreCSVFilesModified = GoDCSV::CSVDatabase::Get()->AreAnyCSVFilesModified();

	// Set Project Root shortcut (Ctrl+O)
	if (IsChordPressedAndNotRouted(SetRootShortcut))
	{
		SetProjectRootPath();
	}

	// Save shortcut (Ctrl+S)
	if (IsChordPressedAndNotRouted(SaveShortcut))
	{
		if (IsProjectRootPathSet() && AreCSVFilesModified)
		{
			SaveAll();
		}
	}
}

void MenuFile::SetProjectRootPath()
{
	// If CSV files have been modified, block setting a new root and show
	// the unsaved progress modal, otherwise allow user to set a new root.
	if (GoDCSV::CSVDatabase::Get()->AreAnyCSVFilesModified())
	{
		auto ModalManager = MainEditorWindow::Get()->GetModalManager();

		std::shared_ptr<BlockUnsavedProgress> Modal =
			std::make_shared<BlockUnsavedProgress>("Save progress before switching projects?", std::bind(&ProjectRoot::SetProjectRootPath, ProjectRoot::Get()));

		ModalManager->SetCurrentlyActiveModal(Modal);
	}
	else
	{
		ProjectRoot::Get()->SetProjectRootPath();
	}
}

void MenuFile::SaveAll()
{
	auto CSVDatabase = GoDCSV::CSVDatabase::Get();

	if (CSVDatabase->AreAnyCSVFilesModified())
	{
		CSVDatabase->SaveAllModifiedCSVFiles();
	}
}

void MenuFile::CloseCurrentRoot()
{
	ProjectRoot::Get()->CloseCurrentRoot();
}

void MenuFile::SaveSelected()
{
	if (GoDCSV::CSVDatabase::Get()->AreAnyCSVFilesModified())
	{
		auto ModalManager = MainEditorWindow::Get()->GetModalManager();

		std::shared_ptr<BlockUnsavedProgress> Modal =
			std::make_shared<BlockUnsavedProgress>("Select CSV files to save", nullptr);

		ModalManager->SetCurrentlyActiveModal(Modal);
	}
}