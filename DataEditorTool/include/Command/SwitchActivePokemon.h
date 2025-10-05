//#pragma once
//#include "Command.h"
//
//class PokemonList;
//
//class SwitchActivePokemon : public Command {
//public:
//	SwitchActivePokemon(std::string InPrevActivePokemon, std::string InNextActivePokemon, std::shared_ptr<PokemonList> InModifiedSection);
//
//	void ExecuteCommand() override;
//
//	void UndoCommand() override;
//
//	void RedoCommand() override;
//
//	std::string GetCommandName() override;
//
//private:
//
//	std::shared_ptr<PokemonList> ModifiedPokemonList;
//
//	std::string PrevActivePokemon;
//	std::string NextActivePokemon;
//};