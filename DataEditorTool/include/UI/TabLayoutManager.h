#pragma once

class UiTab;
class LayoutSettings;

class TabLayoutManager
{

public:

	TabLayoutManager(UiTab* InParentTab);

	void Tick();

	void TabOpened();

	void LoadOrCreateLayoutSettings();

	void LoadCurrentLayout();

	void LoadDefaultLayout();

	void ReloadLayoutNextTick();

	UiTab* GetParentTab();

	const UiTab* GetParentTab() const;

	fs::path GetLayoutDirectory() const;

	std::shared_ptr<LayoutSettings> GetLayoutSettings() const;

	std::vector<std::string> GetAvailableLayouts() const;

private:

	bool bShouldReloadLayoutNextTick = false;

	UiTab* ParentTab;

	std::shared_ptr<LayoutSettings> TabLayoutSettings;

};