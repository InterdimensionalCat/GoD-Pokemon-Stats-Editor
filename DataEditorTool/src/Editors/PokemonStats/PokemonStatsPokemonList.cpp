#include "include.h"
#include "Editors/PokemonStats/PokemonStatsPokemonList.h"

#include "Editors/PokemonStats/PokemonStatsEditor.h"
#include "UI/BasicUiElements/CSVEntryRowSelector.h"

PokemonStatsPokemonList::PokemonStatsPokemonList(PokemonStatsEditor* InParent) : UiSection("Pokémon List", InParent)
{
	const std::string CSVName = "Pokemon Stats";

	std::shared_ptr<CSVEntryRowSelector> PokemonEntrySelector = std::make_shared<CSVEntryRowSelector>("##Pokemon Entry List", this, CSVName, "Entry Name");

	AddCSVElement(PokemonEntrySelector);
}