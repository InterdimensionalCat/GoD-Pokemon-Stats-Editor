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
class Learnset;
class UiTable;
class CSVTextBox;

class LearnedMovesLearnsets : public UiSection
{

public:

	LearnedMovesLearnsets(LearnedMovesEditor* InParent);

	void Refresh() override;


private:

	/**
	 * Get all the columns in the Pokemon Stats CSV file that correspond to a taught move type (TM, HM, or TutorMove).
	 *
	 * \param MoveColumnPrefix The prefix of the move column type to search for (e.g. "TM", "HM", or "TutorMove").
	 * \return A vector of all column names that start with the specified prefix.
	 */
	std::vector<std::string> GetMoveColumns(const std::string& MoveColumnPrefix) const;

	std::shared_ptr<UiTable> LearnsetsTable;

	//std::vector<std::shared_ptr<Learnset>> PokemonLearnsets;
};