/*****************************************************************//**
 * \file   PokemonStatsLearnedMoves.h
 * \brief  UiSection for editing a Pokemon's level-up and egg moves.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSection.h"

class PokemonStatsEditor;
class LevelUpMove;

/**
 * \brief  UiSection for editing a Pokemon's level-up and egg moves.
 * 
 * This section displays a list of LevelUpMove entries for the currently
 * selected Pokemon in the PokemonStatsEditor tab. Each LevelUpMove entry
 * contains a level and a move that the Pokemon can learn at that level.
 * 
 * The list of LevelUpMove Ui elements are stored in the LevelUpMoves vector,
 * which can be accessed via GetLevelUpMoves() and individual entries
 * can be accessed via GetLevelUpMoveAtIndex().
 */
class PokemonStatsLearnedMoves : public UiSection
{

public:

	/**
	 * Construct a PokemonStatsLearnedMoves section under the supplied
	 * PokemonStatsEditor parent tab.
	 * 
	 * \param InParent Parent PokemonStatsEditor tab.
	 */
	PokemonStatsLearnedMoves(PokemonStatsEditor* InParent);

	/**
	 * Get the LevelUpMove Ui element at the specified index.
	 * 
	 * \param Index The index of the LevelUpMove to get.
	 * \return A shared pointer to the LevelUpMove at the specified index.
	 */
	std::shared_ptr<LevelUpMove> GetLevelUpMoveAtIndex(const int32_t Index);

	/**
	 * Get a read-only reference to the vector of LevelUpMove Ui elements.
	 * 
	 * \return A read-only reference to the vector of LevelUpMove Ui elements.
	 */
	const std::vector<std::shared_ptr<LevelUpMove>>& GetLevelUpMoves() const;

private:

	/** The Level up move Ui Elements present in this UiSection. */
	std::vector<std::shared_ptr<LevelUpMove>> LevelUpMoves;

};
