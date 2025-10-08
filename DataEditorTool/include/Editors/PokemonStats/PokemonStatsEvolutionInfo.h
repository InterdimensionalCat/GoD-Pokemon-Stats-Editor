/*****************************************************************//**
 * \file   PokemonStatsEvolutionInfo.h
 * \brief  UiSection for editing evolution information in the Pokemon Stats Editor.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSection.h"

class PokemonStatsEditor;

/**
 * \brief  UiSection for editing evolution information in the Pokemon Stats Editor.
 * 
 * This section allows editing of evolution methods, conditions, and target evolutions
 * for the currently selected Pokemon species.
 */
class PokemonStatsEvolutionInfo : public UiSection
{

public:

	/** Construct a PokemonStatsEvolutionInfo section under the supplied PokemonStatsEditor tab. */
	PokemonStatsEvolutionInfo(PokemonStatsEditor* InParent);

};
