#pragma once

#include "UI/UiSection.h"

class PokemonStatsEditor;
class SimpleImageBox;
class CSVTextBox;
typedef unsigned int GLuint;

class PokemonStatsSpeciesInfo : public UiSection
{

public:

	PokemonStatsSpeciesInfo(PokemonStatsEditor* InParent);

	virtual void Refresh() override;

	void InitPokefaceData();

	void CalculateElementMaxWidth();

private:
	std::shared_ptr<CSVTextBox> NameID;
	std::shared_ptr<SimpleImageBox> PokefaceImage;

	/**
	 * List of loaded Pokeface image ids.
	 * 
	 * A deque is used here so that references to
	 * elements do not become invalidated when
	 * the container is resized
	 * 
	 * (this may not be necessasary)
	 */
	std::deque<GLuint> PokefaceData;

	bool bPokefaceDataLoaded = false;
};
