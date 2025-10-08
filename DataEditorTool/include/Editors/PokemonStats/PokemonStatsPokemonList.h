/*****************************************************************//**
 * \file   PokemonStatsPokemonList.h
 * \brief  UiSection containing a list of all Pokemon rows in the Pokemon Stats CSV file.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSection.h"

class PokemonStatsEditor;

/** \brief  UiSection containing a list of all Pokemon rows in the Pokemon Stats CSV file. */
class PokemonStatsPokemonList : public UiSection
{

public:

	/** Construct a PokemonStatsPokemonList section under the supplied PokemonStatsEditor parent tab. */
	PokemonStatsPokemonList(PokemonStatsEditor* InParent);

};
