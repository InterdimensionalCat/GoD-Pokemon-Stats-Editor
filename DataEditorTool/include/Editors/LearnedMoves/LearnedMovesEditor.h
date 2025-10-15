/*****************************************************************//**
 * \file   PokemonStatsEditor.h
 * \brief  UiTab for editing the TM, HM, and Move Tutor moves learned by Pokemon.
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiTab.h"

class LearnedMovesLearnsetsFilters;

 /** \brief  UiTab for editing the TM, HM, and Move Tutor moves learned by Pokemon. */
class LearnedMovesEditor : public UiTab
{

public:

	/**
	 * Construct a LearnedMovesEditor tab.
	 *
	 * \param InTabDockspace The main editor's tab dockspace,
	 */
	LearnedMovesEditor(std::shared_ptr<ImGuiWindowClass> InTabDockspace);

	/**
	 * Initialize the LearnedMovesEditor tab,
	 * creating all UiSections used in the Pokemon Stats Editor.
	 */
	virtual void Init() override;

	/**
	 * Load the default layout for the LearnedMovesEditor tab.
	 */
	virtual void LoadDefaultLayout() override;

	std::shared_ptr<LearnedMovesLearnsetsFilters> GetLearnedMovesFiltersSection();

private:

	std::shared_ptr<LearnedMovesLearnsetsFilters> LearnedMovesFiltersSection;
};