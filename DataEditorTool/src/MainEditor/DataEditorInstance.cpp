#include "include.h"
#include "MainEditor/DataEditorInstance.h"
#include "MainEditor/MainEditorWindow.h"
#include "MainEditor/ProjectRoot.h"
#include "CSV/CSVDatabase.h"

std::shared_ptr<DataEditorInstance> DataEditorInstance::Instance = nullptr;

void DataEditorInstance::CreateInstance()
{
	Instance = std::make_shared<DataEditorInstance>();
}

void DataEditorInstance::DestroyInstance()
{
	Instance.reset();
}

std::shared_ptr<DataEditorInstance> DataEditorInstance::Get()
{
	return Instance;
}

void DataEditorInstance::Init()
{
	// Start the tool.
	Running = true;
	ICLogger::Debug("Starting GoD Data Editor Tool...");

	// Create the ProjectRoot object
	CurrentProjectRoot = std::make_shared<ProjectRoot>();

	// Create the CSV database object
	EditorCSVDatabase = std::make_shared<GoDCSV::CSVDatabase>();

	// Initialize a new Editor Window.
	EditorWindow = std::make_shared<MainEditorWindow>();
	EditorWindow->Init();
	
}

void DataEditorInstance::Stop()
{
	ICLogger::Debug("Stopping GoD Data Editor Tool...");
	Running = false;
}

void DataEditorInstance::Exit()
{
	ICLogger::Debug("Exiting GoD Data Editor Tool...");
	EditorWindow->Exit();
}

bool DataEditorInstance::IsRunning() const
{
	return Running;
}

void DataEditorInstance::PollEvents()
{
	EditorWindow->PollEvents();
}

void DataEditorInstance::Tick()
{
	EditorWindow->Tick();
}

void DataEditorInstance::Render()
{
	EditorWindow->Render();
}

void DataEditorInstance::ApplicationLoop()
{

	if(IsRunning())
	{
		// Update input.
		PollEvents();

		// Update gui and state, modify CSV data files based on user input.
		Tick();

		// Draw gui.
		Render();

		if (!AttemptLastKnownRootLoaded)
		{
			AttemptLastKnownRootLoaded = true;
			EditorWindow->TryLoadLastKnownRoot();
		}
	}

	while (IsRunning())
	{
		// Update input.
		PollEvents();

		// Update gui and state, modify CSV data files based on user input.
		Tick();

		// Draw gui.
		Render();
	}

	Exit();
}

std::shared_ptr<MainEditorWindow> DataEditorInstance::GetMainEditorWindow()
{
	return EditorWindow;
}

std::shared_ptr<ProjectRoot> DataEditorInstance::GetProjectRoot()
{
	return CurrentProjectRoot;
}

std::shared_ptr<GoDCSV::CSVDatabase> DataEditorInstance::GetCSVDatabase()
{
	return EditorCSVDatabase;
}