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

class UiTab : public UiObject
{
public:

	UiTab(const std::string& InName, std::shared_ptr<ImGuiWindowClass> InTabDockspace);

	/**
	 * Unlike other UiObjects, UiTabs have an init function.
	 * At construction time, the CSV files a UiTab requires
	 * are not guarunteed to be loaded, as LoadRequiredCSVFiles
	 * has not been called yet. However, Init is only called
	 * once LoadRequiredCSVFiles is called, so all needed CSV
	 * files are guarunteed to be loaded.
	 */
	virtual void Init();

	virtual void Refresh() override;

	virtual void Tick() override;

	void AddSection(const std::shared_ptr<UiSection> NewSection);
	void SetTabActive(const bool InTabActive);
	void SetTabFocused(const bool InTabFocused);

	bool LoadRequiredCSVFiles();

	virtual void LoadDefaultLayout() = 0;

	std::shared_ptr<TabCSVState> GetTabCSVState();
	std::shared_ptr<TabLayoutManager> GetLayoutManager();
	const std::vector<std::string>& GetRequiredForEditCSVFiles() const;
	const std::vector<std::string>& GetRequiredForViewingCSVFiles() const;
	std::shared_ptr<ImGuiWindowClass> GetSectionDockspace() const;
	bool IsTabActive();
	bool IsTabFocused();

protected:

	/** UiSections contained in this Tab and its dockspace. */
	std::vector<std::shared_ptr<UiSection>> UiSections;

	/** TODO: prevent tabs from opening if one or more required CSV files don't exist. */
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

	/** Unique identifier for this tab. */
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
