/*****************************************************************//**
 * \file   PokemonStatsTaughtMoves.h
 * \brief  UiSection for editing the taught moves of a Pokemon in the PokemonStatsEditor tab.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSection.h"

class PokemonStatsEditor;
class LevelUpMove;

/**
 * \brief  UiSection for editing the taught moves of a Pokemon in the PokemonStatsEditor tab.
 * 
 * This section allows editing of the moves a Pokemon can be taught
 * via TMs/HMs or Move Tutors.
 */
class PokemonStatsTaughtMoves : public UiSection
{

public:

	/**
	 * Construct a PokemonStatsTaughtMoves section
	 * under the supplied PokemonStatsEditor tab.
	 * 
	 * \param InParent Parent PokemonStatsEditor tab.
	 */
	PokemonStatsTaughtMoves(PokemonStatsEditor* InParent);

private:

	/**
	 * Get all the columns in the Pokemon Stats CSV file that correspond to a taught move type (TM, HM, or TutorMove).
	 * 
	 * \param MoveColumnPrefix The prefix of the move column type to search for (e.g. "TM", "HM", or "TutorMove").
	 * \return A vector of all column names that start with the specified prefix.
	 */
	std::vector<std::string> GetMoveColumns(const std::string& MoveColumnPrefix) const;

};
