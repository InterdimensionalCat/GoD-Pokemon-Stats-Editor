#pragma once
#include "MainMenu/MainMenuSections/MainMenuSection.h"

class FontManager;
class FontSettings;

class MenuView : public MainMenuSection
{
public:

	MenuView();

	virtual void Tick() override;

	virtual void CheckShortcuts() override;

private:

	std::shared_ptr<FontManager> MainFontManager;
};