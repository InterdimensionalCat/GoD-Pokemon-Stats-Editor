/*******************************************************************
 * \file   DataEditorInstance.h
 * \brief  Global context for the entire data editor tool. Initializes and destroys needed contexts. Contains the main application loop logic.
 * Contains an instance of MainEditorWindow which handles the window functionality and UI containers. (this is the view)
 * Also contains an instance of the loaded CSV data map, which can be used to get or modify csv data values (this is the model and controller)
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once
#include "include.h"

//#include "CSVData/PokemonStats.h"
//#include "CSVData/Types.h"
//#include "CSVData/Abilities.h"
//#include "CSVData/Items.h"
//#include "CSVData/Moves.h"
//#include "Command/Command.h"
//#include "Settings/Settings.h"
//#include "Util/UnsavedProgressModal.h"

//class PokemonList;

class MainEditorWindow;

class DataEditorInstance
{

public:

	static void CreateInstance();

	static void DestroyInstance();

	static std::shared_ptr<DataEditorInstance> Get();

	void Init();

	void Stop();

	void Exit();

	bool IsRunning() const;

	void PollEvents();

	void Tick();

	void Render();

	void ApplicationLoop();

	std::shared_ptr<MainEditorWindow> GetMainEditorWindow();

private:

	std::shared_ptr<MainEditorWindow> EditorWindow;

	static std::shared_ptr<DataEditorInstance> Instance;

	bool Running = true;

public:

	// void SetProjectRootPath();

	// void CloseCurrentRoot();

	// bool Save();

	// void OnCurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave);

	// static void WindowCloseCallback(GLFWwindow* window);

	/*std::shared_ptr<PokemonList> CurrentPokemonList;

	std::vector<std::shared_ptr<UiSection>> UiElements;

	std::filesystem::path GetProjectRootPath();

	std::shared_ptr<PokemonStatsCSV> StatsCSV;

	std::shared_ptr<PokemonTypesCSV> TypesCSV;

	std::shared_ptr<PokemonAbilitiesCSV> AbilitiesCSV;

	std::shared_ptr<PokemonItemsCSV> ItemsCSV;

	std::shared_ptr<PokemonMovesCSV> MovesCSV;

	std::shared_ptr<UnsavedProgressModal> UnsavedProgressBlocker;
	std::shared_ptr<UnsavedProgressModal> SwitchRootBlocker;

	GLFWwindow* window;

	std::shared_ptr<ImFont> FontTitle;
	std::shared_ptr<ImFont> FontBody;

	void OnFontChanged();*/

private:

	//void CSVLoadFail(const std::string& FailedCSV);

	//void GeneralLoadFail(std::exception e);

	//bool bProjectRootPathSet = false;

	//void OnProjectRootPathSet();

	//std::filesystem::path ProjectRootPath;

	//std::shared_ptr<AppSettings> CurrentSettings;
};
