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

	TrainersEditor* GetParentEditor() const;

private:

	TrainersEditor* ParentEditor;
};
