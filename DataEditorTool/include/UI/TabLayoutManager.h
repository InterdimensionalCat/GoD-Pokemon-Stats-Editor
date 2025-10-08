/*****************************************************************//**
 * \file   TabLayoutManager.h
 * \brief  Manages per-tab layout settings and loading/saving layouts for a single UiTab.
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

class UiTab;
class LayoutSettings;


/**
 * \brief  Manages per-tab layout settings and loading/saving layouts for a single UiTab.
 */
class TabLayoutManager
{

public:

	/**
	 * Construct a TabLayoutManager for the supplied UiTab.
	 * 
	 * \param InParentTab Parent UiTab for this TabLayoutManager.
	 */
	TabLayoutManager(UiTab* InParentTab);

	/** Reload the current layout if a layout reload was requested. */
	void Tick();

	/**
	 * Load the layout settings for this tab, or create them if they don't exist,
	 * then reload the layout preset if the settings indicate to do so.
	 */
	void TabOpened();

	/**
	 * Load the layout settings for this tab, or create them if they don't exist.
	 */
	void LoadOrCreateLayoutSettings();

	/**
	 * Reload the current layout from the layout settings, or the
	 * default layout if the CurrentLayout setting is "Default".
	 */
	void LoadCurrentLayout();

	/**
	 * Load the hard-coded default layout for this tab.
	 * Each tab must implement its own default layout.
	 */
	void LoadDefaultLayout();

	/**
	 * Request that the layout be reloaded on the next tick.
	 */
	void ReloadLayoutNextTick();

	/**
	 * Get the parent UiTab for this TabLayoutManager.
	 * 
	 * \return Pointer to the parent UiTab for this TabLayoutManager.
	 */
	UiTab* GetParentTab();

	/**
	 * Get the parent UiTab for this TabLayoutManager.
	 * 
	 * \return Const pointer to the parent UiTab for this TabLayoutManager.
	 */
	const UiTab* GetParentTab() const;

	/**
	 * Get the directory where layout presets are stored.
	 * This is "Resources/Layouts/{TabName}/.
	 * 
	 * \return Path to the directory where layout presets are stored.
	 */
	fs::path GetLayoutDirectory() const;

	/**
	 * Get the layout settings for this tab.
	 * 
	 * \return Shared pointer to the LayoutSettings for this tab.
	 */
	std::shared_ptr<LayoutSettings> GetLayoutSettings() const;

	/**
	 * Get a vector of available layout preset names for this tab,
	 * including the "Default" layout, which is always available.
	 * 
	 * \return Vector of available layout preset names for this tab.
	 */
	std::vector<std::string> GetAvailableLayouts() const;

private:

	/** Should we reload the layout on the next tick? */
	bool bShouldReloadLayoutNextTick = false;

	/** The UiTab this TabLayoutManager manages. */
	UiTab* ParentTab;

	/** Layout settings for this tab. */
	std::shared_ptr<LayoutSettings> TabLayoutSettings;

};