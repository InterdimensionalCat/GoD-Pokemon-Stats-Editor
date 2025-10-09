#include "include.h"
#include "Editors/PokemonStats/PokemonStatsPokemonList.h"

#include "Editors/PokemonStats/PokemonStatsEditor.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVRowSelector.h"

PokemonStatsPokemonList::PokemonStatsPokemonList(PokemonStatsEditor* InParent) : UiSection("Pokémon List", InParent)
{
	const std::string CSVName = "Pokemon Stats";

	std::shared_ptr<CSVRowSelector> PokemonEntrySelector = std::make_shared<CSVRowSelector>("##Pokemon Entry List", this, CSVName, "Entry Name");

	AddElement(PokemonEntrySelector);
}