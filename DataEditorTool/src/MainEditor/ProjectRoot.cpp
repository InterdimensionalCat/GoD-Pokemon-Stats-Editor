#include "include.h"
#include "MainEditor/ProjectRoot.h"
#include "MainEditor/DataEditorInstance.h"
#include "CSV/NewCSVData.h"
#include "CSV/CSVDatabase.h"

void ProjectRoot::SetProjectRootPath()
{
	// Prevent setting a new project root
	// If we have currently unsaved progress

	//bool bUnsavedProgress = false;

	//for (auto& section : UiElements)
	//{
	//	if (section->GetUnsavedProgress())
	//	{
	//		bUnsavedProgress = true;
	//	}
	//}

	//if (bUnsavedProgress && !SwitchRootBlocker->GetBypassModal())
	//{
	//	SwitchRootBlocker->SetEnabled(true);
	//	return;
	//}
	//else
	//{
	//	SwitchRootBlocker->SetBypassModal(false);
	//}

	// Use NFD to open a folder selection dialogue box.
	NFD_Init();

	// Initialize NFD
	NFD::Guard NFDGuard;

	// auto-freeing memory
	NFD::UniquePath OutPath;

	// Show the dialog
	nfdresult_t Result = NFD::PickFolder(OutPath);
	if (Result == NFD_OKAY) {

		// If a valid result is output, set
		// the Root path equal to the selected folder
		std::string PathStr(OutPath.get());

		ProjectRootPath = PathStr;
		bProjectRootPathSet = true;
		OnProjectRootPathSet();
	}
	else if (Result == NFD_CANCEL) 
	{
		// Dialogue box was cancelled before a root folder was selected.
		ICLogger::Debug("Select root folder dialogue cancelled.");
	}
	else 
	{
		// Result was NFD_ERROR, some sort of error occured.
		ICLogger::Error("Select root folder failed: {}", NFD::GetError());
	}

	// NFD::Guard will automatically quit NFD.
}

void ProjectRoot::CloseCurrentRoot()
{
	// TODO: Clear the command queue once commands are up and running again
	//Command::ClearCommandQueue();
	//UiElements.clear();

	// Clear the CSV database
	GoDCSV::CSVDatabase::Get()->ClearDatabase();

	// Reset project root state variables
	ProjectRootPath = "";
	bProjectRootPathSet = false;
}

void ProjectRoot::OnProjectRootPathSet()
{
	// TODO: Copy implementation from GoD-UI-Windows.cpp

	// Test CSV loading/Saving
	//std::shared_ptr<GoDCSV::NewCSVData> PokemonStats = std::make_shared<GoDCSV::NewCSVData>("Pokemon Stats");

	//PokemonStats->Init();

	//if (PokemonStats->IsCSVFileLoaded())
	//{
	//	PokemonStats->SetField("Name ID", 0, "\"Blubbysaur,\" (0x3E9)");
	//}

	//PokemonStats->Save();

	auto CSVDatabase = GoDCSV::CSVDatabase::Get();

	CSVDatabase->OnProjectRootPathSet();

	CSVDatabase->LoadAllCSVFiles();

	for (auto& [Key, CSVFile] : CSVDatabase->GetDatabaseMap())
	{
		CSVFile->SetField("Entry Name", 0, "\"hehe\" - 69");
	}

	// CSVDatabase->SaveAllCSVFiles();

}

std::filesystem::path ProjectRoot::GetProjectRootPath()
{
	return ProjectRootPath;
}

bool ProjectRoot::IsProjectRootSet()
{
	return bProjectRootPathSet;
}

std::shared_ptr<ProjectRoot> ProjectRoot::Get()
{
	return DataEditorInstance::Get()->GetProjectRoot();
}