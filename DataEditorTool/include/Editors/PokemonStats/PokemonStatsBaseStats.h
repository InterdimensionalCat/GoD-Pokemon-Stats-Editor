/*****************************************************************//**
 * \file   PokemonStatsBaseStats.h
 * \brief  UiSection for editing a Pokemon's base stats, 
 * including HP, Attack, Defense, Sp. Atk, Sp. Def, and Speed.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSection.h"

class PokemonStatsEditor;
class BaseStat;
class BaseStatTotal;

/**
 * \brief  UiSection for editing a Pokemon's base stats, 
 * including HP, Attack, Defense, Sp. Atk, Sp. Def, and Speed.
 * 
 * This section contains six BaseStat elements for each
 * individual base stat, as well as a BaseStatTotal element
 * that displays the current Base Stat Total (BST).
 * 
 * The Base Stat Total is automatically calculated whenever
 * any of the individual base stats are changed.
 */
class PokemonStatsBaseStats : public UiSection
{

public:

	/** Construct a PokemonStatsBaseStats section under the supplied PokemonStatsEditor tab. */
	PokemonStatsBaseStats(PokemonStatsEditor* InParent);

	/** Recalculate the Base Stat Total every tick. */
	void Tick() override;

	/** Calculate the Base Stat Total from the current base stats and update the BaseStatTotal element. */
	void CalculateBaseStatTotal();

private:

	/** Base Stat Elements for each of the 6 base stats */
	std::array<std::shared_ptr<BaseStat>, 6> BaseStatElements;

	/** Base Stat Total element that displays the current Base Stat Total (BST) */
	std::shared_ptr<BaseStatTotal> CurrentBST;

};
