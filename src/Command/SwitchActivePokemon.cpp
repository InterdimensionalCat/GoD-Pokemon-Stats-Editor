#include "SwitchActivePokemon.h"
#include "UiSections/PokemonList.h"

SwitchActivePokemon::SwitchActivePokemon(std::string InPrevActivePokemon, std::string InNextActivePokemon, std::shared_ptr<PokemonList> InModifiedSection) : Command(std::static_pointer_cast<UiSection>(InModifiedSection)), PrevActivePokemon(InPrevActivePokemon), NextActivePokemon(InNextActivePokemon), ModifiedPokemonList(InModifiedSection)
{

}

void SwitchActivePokemon::ExecuteCommand()
{
	ModifiedPokemonList->SetCurrentlySelectedItem(NextActivePokemon);
}

void SwitchActivePokemon::UndoCommand()
{
	ModifiedPokemonList->SetCurrentlySelectedItem(PrevActivePokemon);
	ModifiedPokemonList->FilterString = "";
	ModifiedPokemonList->SetScrollToItem(true);
}

void SwitchActivePokemon::RedoCommand()
{
	ModifiedPokemonList->SetCurrentlySelectedItem(NextActivePokemon);
	ModifiedPokemonList->FilterString = "";
	ModifiedPokemonList->SetScrollToItem(true);
}

std::string SwitchActivePokemon::GetCommandName()
{
	return "Switch active Pokemon";
}
