#pragma once

class MainMenuSection;

class MainMenu
{
public:

	MainMenu();

	void Tick();

	void AddSection(const std::shared_ptr<MainMenuSection>& InMenuSection);

private:

	std::vector<std::shared_ptr<MainMenuSection>> MenuSections;

	// TODO: Add/remove/disable setions based on
	// Currently opened tabs and the currently
	// selected tab
};
