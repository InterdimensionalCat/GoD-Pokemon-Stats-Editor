/*****************************************************************//**
 * \file   GenralSettingsSection.h
 * \brief
 *
 * \author Joe DeLuca
 * \date   November 2025
 *********************************************************************/
#pragma once

#include "MainMenu/MainMenuSections/MainMenuSection.h"

 /**
  * \brief  Main Menu "Settings" section, containing options for the
  * general application settings.
  */
class MenuSettings : public MainMenuSection
{
public:
	/** Construct the Main Menu "Settings" section. */
	MenuSettings();

	/** Tick this section, displaying general application settings. */
	virtual void Tick() override;

	/** Check for and handle keyboard shortcuts for this section. */
	virtual void CheckShortcuts() override;

private:

};