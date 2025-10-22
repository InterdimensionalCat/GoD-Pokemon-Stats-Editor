/*****************************************************************//**
 * \file   TrainerPokemon.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"

class TrainersEditorTrainerPokemon;
class SimpleImageBox;
class UiGroup;
class CSVComboBox;
class CSVIntBox;

class TrainerPokemon : public UiSingleLineMultiElement
{

public:
	/**
	 * Construct a TrainerPokemon multi-element
	 * under the TrainersEditor InParent.
	 *
	 * \param InParent Parent TrainersEditor of this multi-element.
	 */
	TrainerPokemon(
		const std::string& InName,
		TrainersEditorTrainerPokemon* InParent,
		int32_t InPartyIndex
	);

	void Refresh() override;

	void SetCurrentRow(const int32_t InRow);

	int32_t GetCurrentRow() const;

private:

	TrainersEditorTrainerPokemon* ParentTrainerPokemon;

	int32_t PartyIndex = 0;

	int32_t CurrentRow = 0;

	std::vector<std::shared_ptr<UiCSVElement>> RowElements;

	void InitPokefaceGroup();
	std::shared_ptr<UiGroup> PokefaceGroup;
	/** Pokeface image of the current trainer's Pokemon. */
	std::shared_ptr<SimpleImageBox> PokefaceImage;

	void InitPokemonInfoGroup();
	std::shared_ptr<UiGroup> PokemonInfoGroup;

	void InitIVsGroup();
	void InitIVElement(const std::string& ItemName, const std::string& ItemColumn);
	std::shared_ptr<UiGroup> IVsGroup;

	void InitEVsGroup();
	void InitEVElement(const std::string& ItemName, const std::string& ItemColumn);
	std::shared_ptr<UiGroup> EVsGroup;

	void InitMovesGroup();
	void InitMoveElement(int32_t MoveIndex);
	std::shared_ptr<UiGroup> MovesGroup;

	void InitMiscGroup();
	void InitComboRoleElement(const std::string& ComboName, int32_t RoleNum);
	std::shared_ptr<UiGroup> MiscGroup;
};
