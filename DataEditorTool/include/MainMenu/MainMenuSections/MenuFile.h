#pragma once

#include "MainMenu/MainMenuSections/MainMenuSection.h"

class MenuFile : public MainMenuSection
{
public:

	MenuFile();

	virtual void Tick() override;

	virtual void CheckShortcuts() override;

private:

	void SetProjectRootPath();

	void Save();

	void CloseCurrentRoot();
};