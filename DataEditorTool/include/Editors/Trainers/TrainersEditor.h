/*****************************************************************//**
 * \file   TrainersEditor.h
 * \brief  
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiTab.h"

class TrainersEditor : public UiTab
{

public:

	TrainersEditor(std::shared_ptr<ImGuiWindowClass> InTabDockspace);

	/**
	 * Initialize the TrainersEditor tab,
	 * creating all UiSections used in the Trainers Editor.
	 */
	virtual void Init() override;

	/**
	 * Load the default layout for the TrainersEditor tab.
	 */
	virtual void LoadDefaultLayout() override;

private:

	std::string TrainerCSVFileName = "Trainer DeckData_Story.bin";

	std::string TrainerPokemonCSVFileName = "Trainer Pokemon DeckData_Colosseum.bin";

	std::string TrainerAICSVFileName = "Trainer AI DeckData_Story.bin";

};