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
	 * (this may not be necessary)
	 * 
	 * These are static values because we want them to
	 * stay loaded through new project loads. Attempting
	 * to reload them every time a new project is loaded
	 * causes undefined behavior where we may (and probably)
	 * will fail to open one of the image files (probably because
	 * its still open in this program).
	 */
	static std::deque<GLuint> PokefaceData;

	static bool bPokefaceDataLoaded;
};
