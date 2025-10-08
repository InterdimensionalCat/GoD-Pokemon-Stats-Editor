/*****************************************************************//**
 * \file   UiTab.h
 * \brief  Top level tab window. Contains Ui Sections but no UiElements. 
 * UiSections can be moved around in it, but not out of it.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once
#include "UI/UiObject.h"

class UiSection;
class TabCSVState;
class TabLayoutManager;

/**
 * \brief  Top level tab window. Contains Ui Sections but no UiElements. 
 * UiSections can be moved around in it, but not out of it.
 * 
 * Each UiTab has its own TabCSVState and TabLayoutManager.
 * 
 * Each UiTab also has its own SectionDockspace, which is where
 * the UiSections contained in this tab are docked.
 * 
 * Each UiTab is contained in the Main Editor's TabDockspace,
 * which is passed in at construction time.
 */
class UiTab : public UiObject
{
public:

	/**
	 * Construct a UiTab with the supplied name and tab dockspace.
	 * The tab dockspace should be the Main Editor's dockspace,
	 * as this is where the tab will be docked.
	 * 
	 * \param InName Name of this UiTab.
	 * \param InTabDockspace Dockspace where this tab will be docked.
	 */
	UiTab(const std::string& InName, std::shared_ptr<ImGuiWindowClass> InTabDockspace);

	/**
	 * Unlike other UiObjects, UiTabs have an init function.
	 * At construction time, the CSV files a UiTab requires
	 * are not guaranteed to be loaded, as LoadRequiredCSVFiles
	 * has not been called yet. However, Init is only called
	 * once LoadRequiredCSVFiles is called, so all needed CSV
	 * files are guaranteed to be loaded.
	 */
	virtual void Init();

	/** Refresh references to the underlying data this UiTab manages  */
	virtual void Refresh() override;

	/** Update GUI state */
	virtual void Tick() override;

	/**
	 * Add a UiSection to this tab. The section will be
	 * docked in this tab's SectionDockspace.
	 * 
	 * \param NewSection Section to add to this tab.
	 */
	void AddSection(const std::shared_ptr<UiSection> NewSection);

	/**
	 * Mark this tab as active. Active tabs are docked
	 * somewhere in the main editor's tab dockspace and
	 * are ticked every frame.
	 * 
	 * \param InTabActive True if this tab should be made active.
	 */
	void SetTabActive(const bool InTabActive);

	/**
	 * Mark this tab as focused. Focused tabs are the
	 * tab that is currently visible in the main editor's
	 * tab dockspace.
	 * 
	 * \param InTabFocused True if this tab should be focused.
	 */
	void SetTabFocused(const bool InTabFocused);

	/**
	 * Attempt to load all CSV files required by this tab.
	 * 
	 * This will return false if any required CSV files
	 * are not present in the CSV database, or if any
	 * required CSV files fail to load.
	 * 
	 * \return True if all required CSV files were loaded successfully.
	 */
	bool LoadRequiredCSVFiles();

	/**
	 * Load a default layout for this tab. Must be
	 * implemented by subclasses.
	 */
	virtual void LoadDefaultLayout() = 0;

	/**
	 * Get the CSV state object for this tab.
	 * 
	 * \return Shared pointer to the TabCSVState for this tab.
	 */
	std::shared_ptr<TabCSVState> GetTabCSVState();

	/**
	 * Get the layout manager for this tab. This controls the
	 * per-tab layout settings for this tab.
	 * 
	 * \return Shared pointer to the TabLayoutManager for this tab.
	 */
	std::shared_ptr<TabLayoutManager> GetLayoutManager();

	/**
	 * Get all CSV files this tab must be able to edit.
	 * 
	 * \return Vector of CSV file names this tab must be able to edit.
	 */
	const std::vector<std::string>& GetRequiredForEditCSVFiles() const;

	/**
	 * Get all CSV files this tab must be able to view.
	 * 
	 * \return Vector of CSV file names this tab must be able to view.
	 */
	const std::vector<std::string>& GetRequiredForViewingCSVFiles() const;

	/**
	 * Get the WindowClass dockspace this UiTab uses for its UiSections.
	 * 
	 * \return Shared pointer to the SectionDockspace for this tab.
	 */
	std::shared_ptr<ImGuiWindowClass> GetSectionDockspace() const;

	/**
	 * Is this tab currently active? Active tabs are docked
	 * somewhere in the main editor's tab dockspace and
	 * are ticked every frame.
	 * 
	 * \return True if this tab is active.
	 */
	bool IsTabActive();

	/**
	 * Is this tab currently focused? Focused tabs are the
	 * tab that is currently visible in the main editor's
	 * tab dockspace.
	 * 
	 * \return True if this tab is focused.
	 */
	bool IsTabFocused();

protected:

	/** UiSections contained in this Tab and its dockspace. */
	std::vector<std::shared_ptr<UiSection>> UiSections;

	/**
	 * All CSV files this Tab might edit, each of these must be loaded for this tab
	 * to function properly.
	 */
	std::vector<std::string> RequiredForEditCSVFileNames;

	/**
	 * All CSV files this Tab must view to function, each of these must be loaded
	 * for this tab to function properly.
	 */
	std::vector<std::string> RequiredForViewingCSVFileNames;

	/**
	 * Dockspace for individual UiSections inside this tab. This should be
	 * unique to each tab.
	 */
	std::shared_ptr<ImGuiWindowClass> SectionDockspace;

	/** Unique dockspace identifier for this tab. */
	ImGuiID UiTabID;

private:

	/** CSV State for this tab, stores info about the current row for each CSV file where data is displayed. */
	std::shared_ptr<TabCSVState> TabState;

	/** 
	 * Layout manager for this tab, interfaces with layout settings
	 * to control the current layout of the tab.
	 */
	std::shared_ptr<TabLayoutManager> LayoutManager;

	/**
	 * Dockspace for the tab as a whole. This should be the dockspace
	 * of the Main Editor.
	 */
	std::shared_ptr<ImGuiWindowClass> TabDockspace;

	/**
	 * Is this tab active? (as in currently visible on screen.
	 * We only refresh/update tab data for visible tabs. However
	 * Once this tab becomes active its data will be refreshed so that
	 * it is current.
	 */
	bool bIsTabActive = false;

	/** Is this tab focused? (as in the tab has keyboard/mouse focus) */
	bool bIsTabFocused = false;
};
