/*****************************************************************//**
 * \file   DataEditorInstance.h
 * \brief  Global application instance and application loop.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once
#include "include.h"

class MainEditorWindow;
class ProjectRoot;

namespace GoDCSV
{
	class CSVDatabase;
}

/**
 * \brief Global application instance and application loop.
 */
class DataEditorInstance
{

public:

	/**
	 * Construct a DataEditorInstance. This will
	 * not be valid for use until Init() is called.
	 * 
	 * This is publice because std::make_shared requires
	 * a public constructor, but this should only ever
	 * be called by CreateInstance().
	 */
	DataEditorInstance() = default;

	/**
	 * Create a new global instance of the DataEditorInstance.
	 */
	static void CreateInstance();

	/**
	 * Destroy the global instance of the DataEditorInstance.
	 */
	static void DestroyInstance();

	/**
	 * Get the global instance of the DataEditorInstance.
	 * 
	 * \return The global instance of the DataEditorInstance.
	 */
	static std::shared_ptr<DataEditorInstance> Get();

	/**
	 * Initialize the DataEditorInstance and its
	 * MainEditorWindow, ProjectRootManager,
	 * and CSVDatabase.
	 */
	void Init();

	/**
	 * Stop the application loop, this
	 * will cause Exit() to be called
	 * next loop.
	 */
	void Stop();

	/**
	 * Exit the application,this will Exit the 
	 * MainEditorWindow and destroy its window context.
	 */
	void Exit();

	/**
	 * Is the application loop currently running?
	 */
	bool IsRunning() const;

	/**
	 * Poll events from the MainEditorWindow.
	 */
	void PollEvents();

	/**
	 * Tick the MainEditorWindow.
	 */
	void Tick();

	/**
	 * Render the MainEditorWindow.
	 */
	void Render();

	/**
	 * The main application loop. This will 
	 * update input, then tick, then render.
	 */
	void ApplicationLoop();

	/**
	 * Get the MainEditorWindow instance.
	 * 
	 * \return The MainEditorWindow instance.
	 */
	std::shared_ptr<MainEditorWindow> GetMainEditorWindow();

	/**
	 * Get the ProjectRoot manager instance.
	 * 
	 * \return The ProjectRoot manager instance.
	 */
	std::shared_ptr<ProjectRoot> GetProjectRoot();

	/**
	 * Get the CSVDatabase instance.
	 * 
	 * \return The CSVDatabase instance.
	 */
	std::shared_ptr<GoDCSV::CSVDatabase> GetCSVDatabase();

private:

	/**
	 * Main editor window for this DataEditorInstance.
	 */
	std::shared_ptr<MainEditorWindow> EditorWindow;

	/**
	 * Project root manager for this DataEditorInstance.
	 */
	std::shared_ptr<ProjectRoot> CurrentProjectRoot;

	/**
	 * CSV database for this DataEditorInstance.
	 */
	std::shared_ptr<GoDCSV::CSVDatabase> EditorCSVDatabase;

	/**
	 * Global application instance for the tool.
	 */
	static std::shared_ptr<DataEditorInstance> Instance;

	/**
	 * Is the application loop currently running?
	 */
	bool Running = true;
	
	/**
	 * Indicates whether the last known project root was attempted to load.
	 */
	bool AttemptLastKnownRootLoaded = false;
};
