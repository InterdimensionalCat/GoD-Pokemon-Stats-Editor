/*****************************************************************//**
 * \file   ProjectRoot.h
 * \brief  Manager for the current project root path. This must be
 * set to a valid GoD tool files path for the tool to function properly.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

/**
 * \brief  Manager for the current project root path. This must be
 * set to a valid GoD tool files path for the tool to function properly.
 */
class ProjectRoot
{

public:

	/**
	 * Construct a ProjectRootPath.
	 */
	ProjectRoot() = default;

	/**
	 * Open a file dialog that allows the user
	 * to select a project root path folder.
	 * 
	 * If a valid project root path is set, this
	 * will open a new PokemonStatsEditor tab and
	 * maximize the window.
	 */
	void SetProjectRootPath();

	/**
	 * Close the current project root path.
	 * 
	 * This will clear all currently open tabs.
	 */
	void CloseCurrentRoot();

	/**
	 * Called when a project root path is set.
	 * 
	 * This will open a new PokemonStatsEditor tab
	 * and maximize the window if it is not already maximized.
	 */
	void OnProjectRootPathSet();

	/** Get the currently open project root path. */
	std::filesystem::path GetProjectRootPath();

	/** Is a valid project root path currently set? */
	bool IsProjectRootSet();

	/**
	 * Get the global instance of this ProjectRoot
	 * located on the global DataEditorInstance.
	 */
	static std::shared_ptr<ProjectRoot> Get();

private:

	/** Is a valid project root path currently set? */
	bool bProjectRootPathSet = false;

	/** The currently open project root path. */
	std::filesystem::path ProjectRootPath;

};
