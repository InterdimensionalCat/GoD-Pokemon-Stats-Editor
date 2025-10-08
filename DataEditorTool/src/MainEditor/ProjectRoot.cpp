#include "include.h"
#include "MainEditor/ProjectRoot.h"
#include "MainEditor/DataEditorInstance.h"
#include "MainEditor/MainEditorWindow.h"
#include "CSV/CSVData.h"
#include "CSV/CSVDatabase.h"

void ProjectRoot::SetProjectRootPath()
{
	// TODO: attempt to automatically set the project root
	// to the last used project root path from settings.

	// Use NFD to open a folder selection dialogue box.
	NFD_Init();

	// Initialize NFD
	NFD::Guard NFDGuard;

	// auto-freeing memory
	NFD::UniquePath OutPath;

	// Show the dialog
	nfdresult_t Result = NFD::PickFolder(OutPath);
	if (Result == NFD_OKAY)
	{
		// If a valid result is output, set
		// the Root path equal to the selected folder
		std::string PathStr(OutPath.get());
		ICLogger::Info("Setting new project root: {}", PathStr);

		if (bProjectRootPathSet)
		{
			// If a project root was already set, close it first.
			ICLogger::Info("Previous project root still open, closing it: {}", ProjectRootPath.string());
			CloseCurrentRoot();
		}

		ProjectRootPath = PathStr;
		bProjectRootPathSet = true;
		OnProjectRootPathSet();
	}
	else if (Result == NFD_CANCEL)
	{
		// Dialogue box was canceled before a root folder was selected.
		ICLogger::Debug("Select root folder dialog canceled.");
	}
	else
	{
		// Result was NFD_ERROR, some sort of error occurred.
		ICLogger::Error("Select root folder failed: {}", NFD::GetError());
	}

	// NFD::Guard will automatically quit NFD.
}

void ProjectRoot::CloseCurrentRoot()
{
	// Clear the CSV database
	ICLogger::Info("Closing current project root: {}", ProjectRootPath.string());
	GoDCSV::CSVDatabase::Get()->ClearDatabase();
	auto EditorWindow = MainEditorWindow::Get();
	EditorWindow->OnProjectRootPathClosed();

	// Reset project root state variables
	ProjectRootPath = "";
	bProjectRootPathSet = false;
}

void ProjectRoot::OnProjectRootPathSet()
{
	auto CSVDatabase = GoDCSV::CSVDatabase::Get();

	try
	{
		CSVDatabase->OnProjectRootPathSet();
		auto EditorWindow = MainEditorWindow::Get();
		EditorWindow->OnProjectRootPathSet();
	}
	catch (const std::exception& e)
	{
		ICLogger::PushWarnNotification("Set project root failed", 8000, "Set project root failed, was a valid project root selected? \n\n{}", e.what());
		CloseCurrentRoot();
	}
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