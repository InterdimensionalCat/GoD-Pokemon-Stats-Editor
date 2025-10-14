/*****************************************************************//**
 * \file   PokemonStatsSpeciesInfo.h
 * \brief  UiSection that contains basic species info and misc characteristics
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiSection.h"

class PokemonStatsEditor;
class SimpleImageBox;
class CSVTextBox;
typedef unsigned int GLuint;

/**
 * \brief  UiSection that contains basic species info and misc characteristics
 */
class PokemonStatsSpeciesInfo : public UiSection
{

public:

	/**
	 * Construct a PokemonStatsSpeciesInfo section under the
	 * specified PokemonStatsEditor parent.
	 * 
	 * \param InParent Parent PokemonStatsEditor tab.
	 */
	PokemonStatsSpeciesInfo(PokemonStatsEditor* InParent);

	/**
	 * Refresh references to the underlying data this UiObject manages.
	 * 
	 * This will update the Pokeface image and species name
	 * to match the currently selected species in the
	 * PokemonStatsEditor tab's TabCSVState.
	 */
	virtual void Refresh() override;

	/** Calculate the max content size of elements in this section. */
	void CalculateElementMaxWidth();

private:

	/** Name ID of the current species. */
	std::shared_ptr<CSVTextBox> NameID;

	/** Pokeface image of the current species. */
	std::shared_ptr<SimpleImageBox> PokefaceImage;

	/**
	 * List of loaded Pokeface image ids.
	 * 
	 * A deque is used here so that references to
	 * elements do not become invalidated when
	 * the container is resized
	 * 
	 * (this may not be necessary)
	 * 
	 * These are static values because we want them to
	 * stay loaded through new project loads. Attempting
	 * to reload them every time a new project is loaded
	 * causes undefined behavior where we may (and probably)
	 * will fail to open one of the image files (probably because
	 * its still open in this program).
	 */
	//static std::deque<GLuint> PokefaceData;

	/** Has Pokeface data been loaded yet? */
	//static bool bPokefaceDataLoaded;
};
