// GoD-UI-Windows.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <nfd.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include <memory>

#include "CSV Data/Pokemon Stats.h"
#include "CSV Data/Types.h"
#include "CSV Data/Abilities.h"
#include "CSV Data/Items.h"
#include "CSV Data/Moves.h"

#include "Settings/Settings.h"

#include "Command/Command.h"

#include "Util/UnsavedProgressModal.h"

class PokemonList;

#include "nlohmann/json.hpp"

using json = nlohmann::json;

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
