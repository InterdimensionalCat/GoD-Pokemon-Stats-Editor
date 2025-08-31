// GoD-UI-Windows.h : Include file for standard system include files,
// or project specific include files.
#pragma once

#include "CSVData/PokemonStats.h"
#include "CSVData/Types.h"
#include "CSVData/Abilities.h"
#include "CSVData/Items.h"
#include "CSVData/Moves.h"
#include "Command/Command.h"
#include "Settings/AppSettings.h"
#include "Util/UnsavedProgressModal.h"

class PokemonList;
class GLFWwindow;

class GoDUIWindowsInstance
{
public:

	static GoDUIWindowsInstance instance;

	void ApplicationLoop();

	void Tick();

	void Render();

	void SetProjectRootPath();

	void CloseCurrentRoot();

	void Init();

	void Exit();

	bool Save();

	void OnCurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave);

	static void WindowCloseCallback(GLFWwindow* window);

	std::shared_ptr<PokemonList> CurrentPokemonList;

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

	void OnFontChanged();

private:

	void CSVLoadFail(const std::string& FailedCSV);

	void GeneralLoadFail(std::exception e);

	bool bProjectRootPathSet = false;

	void OnProjectRootPathSet();

	std::filesystem::path ProjectRootPath;

	std::shared_ptr<AppSettings> CurrentSettings;
};
