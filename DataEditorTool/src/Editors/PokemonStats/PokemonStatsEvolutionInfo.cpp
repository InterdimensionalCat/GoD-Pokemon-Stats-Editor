#include "include.h"
#include "Editors/PokemonStats/PokemonStatsEvolutionInfo.h"
#include "Editors/PokemonStats/PokemonStatsEditor.h"
#include "Editors/PokemonStats/EvolutionElement.h"

PokemonStatsEvolutionInfo::PokemonStatsEvolutionInfo(PokemonStatsEditor* InParent) : UiSection("Evolution Info", InParent)
{
	const std::string CSVName = "Pokemon Stats";

	// Add the evolution info elements.

	// TODO: Consider determining this programatically rather than a hard coded value
	for (int32_t Index = 1; Index <= 5; Index++)
	{
		AddElement(std::make_shared<EvolutionElement>(std::format("Evolution Element {}", Index), this, Index));
	}
}