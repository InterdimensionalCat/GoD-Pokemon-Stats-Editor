/*****************************************************************//**
 * \file   TrainersEditorTrainerPokemon.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiSection.h"

class TrainersEditor;
class UiSingleLineMultiElement;

class TrainersEditorTrainerPokemon : public UiSection
{

public:
	/**
	 * Construct a TrainersEditorTrainerPokemon section
	 * under the TrainersEditor InParent.
	 *
	 * \param InParent Parent TrainersEditor of this section.
	 */
	TrainersEditorTrainerPokemon(TrainersEditor* InParent);

	void InitTrainerPokemonForPartyIndex(const int32_t PartyIndex);

	TrainersEditor* GetParentEditor() const;

private:

	std::shared_ptr<UiSingleLineMultiElement> PokemonMultiLineElement;

	TrainersEditor* ParentEditor;
};
