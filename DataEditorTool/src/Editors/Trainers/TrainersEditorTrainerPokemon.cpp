#include "include.h"
#include "Editors/Trainers/TrainersEditorTrainerPokemon.h"
#include "Editors/Trainers/TrainersEditor.h"
#include "Editors/Trainers/TrainerPokemon.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleSectionDivider.h"

TrainersEditorTrainerPokemon::TrainersEditorTrainerPokemon(TrainersEditor* InParent) :
	UiSection("Trainer Pokemon", InParent),
	ParentEditor(InParent)
{
	auto SectionDividerOne = std::make_shared<SimpleSectionDivider>("Pokemon 1", this);
	SectionDividerOne->SetNumSpaceLengths(1);
	auto TrainerPokemonElementOne = std::make_shared<TrainerPokemon>("##TrainerPokemonElementOne", this, 1);
	auto SectionDividerTwo = std::make_shared<SimpleSectionDivider>("Pokemon 2", this);
	SectionDividerTwo->SetNumSpaceLengths(1);
	auto TrainerPokemonElementTwo = std::make_shared<TrainerPokemon>("##TrainerPokemonElementTwo", this, 2);
	auto SectionDividerThree = std::make_shared<SimpleSectionDivider>("Pokemon 3", this);
	SectionDividerThree->SetNumSpaceLengths(1);
	auto TrainerPokemonElementThree = std::make_shared<TrainerPokemon>("##TrainerPokemonElementThree", this, 3);
	auto SectionDividerFour = std::make_shared<SimpleSectionDivider>("Pokemon 4", this);
	SectionDividerFour->SetNumSpaceLengths(1);
	auto TrainerPokemonElementFour = std::make_shared<TrainerPokemon>("##TrainerPokemonElementFour", this, 4);
	auto SectionDividerFive = std::make_shared<SimpleSectionDivider>("Pokemon 5", this);
	SectionDividerFive->SetNumSpaceLengths(1);
	auto TrainerPokemonElementFive = std::make_shared<TrainerPokemon>("##TrainerPokemonElementFive", this, 5);
	auto SectionDividerSix = std::make_shared<SimpleSectionDivider>("Pokemon 6", this);
	SectionDividerSix->SetNumSpaceLengths(1);
	auto TrainerPokemonElementSix = std::make_shared <TrainerPokemon>("##TrainerPokemonElementSix", this, 6);

	AddElement(SectionDividerOne);
	AddElement(TrainerPokemonElementOne);
	AddElement(SectionDividerTwo);
	AddElement(TrainerPokemonElementTwo);
	AddElement(SectionDividerThree);
	AddElement(TrainerPokemonElementThree);
	AddElement(SectionDividerFour);
	AddElement(TrainerPokemonElementFour);
	AddElement(SectionDividerFive);
	AddElement(TrainerPokemonElementFive);
	AddElement(SectionDividerSix);
	AddElement(TrainerPokemonElementSix);
}

TrainersEditor* TrainersEditorTrainerPokemon::GetParentEditor() const
{
	return ParentEditor;
}