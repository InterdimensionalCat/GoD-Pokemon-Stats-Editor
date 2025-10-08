/*****************************************************************//**
 * \file   PokemonStatsEditor.h
 * \brief  UiTab for editing the Pokemon Stats csv file.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiTab.h"

 /** \brief  UiTab for editing the Pokemon Stats csv file. */
class PokemonStatsEditor : public UiTab
{

public:

	/** Construct a PokemonStatsEditor tab. */
	PokemonStatsEditor(std::shared_ptr<ImGuiWindowClass> InTabDockspace);

	/**
	 * Initialize the PokemonStatsEditor tab,
	 * creating all UiSections used in the Pokemon Stats Editor.
	 */
	virtual void Init() override;

	/**
	 * Load the default layout for the PokemonStatsEditor tab.
	 */
	virtual void LoadDefaultLayout() override;
};