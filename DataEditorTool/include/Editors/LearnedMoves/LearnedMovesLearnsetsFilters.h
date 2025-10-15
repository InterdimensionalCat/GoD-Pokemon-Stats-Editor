/*****************************************************************//**
 * \file   LearnedMovesLearnsets.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiSection.h"

class LearnedMovesEditor;
class SimpleTextBox;

class LearnedMovesLearnsetsFilters : public UiSection
{

public:

	LearnedMovesLearnsetsFilters(LearnedMovesEditor* InParent);

	void Refresh() override;

	std::string GetMoveFilterText() const;

	std::string GetPokemonFilterText() const;

private:
	
	std::shared_ptr<SimpleTextBox> MoveFilterBox;

	std::shared_ptr<SimpleTextBox> PokemonFilterBox;
};