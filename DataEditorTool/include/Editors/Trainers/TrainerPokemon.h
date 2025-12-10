/*****************************************************************//**
 * \file   TrainerPokemon.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiChildWindow.h"

class TrainersEditorTrainerPokemon;
class SimpleImageBox;
class UiGroup;
class CSVComboBox;
class CSVIntBox;
class CSVIntHexComboBox;
class UiElementSwitcher;

class TrainerPokemon : public UiChildWindow
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

	void Tick() override;

	virtual void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	) override;

	void SetCurrentRow(const int32_t InRow);

	int32_t GetCurrentRow() const;

private:

	void UpdatePokefaceImageSize();

	TrainersEditorTrainerPokemon* ParentTrainerPokemon;

	int32_t PartyIndex = 0;

	int32_t CurrentRow = -1;

	std::vector<std::shared_ptr<UiCSVElement>> RowElements;

	std::vector<std::shared_ptr<UiCSVElement>> ShadowPokemonElements;

	void InitPokefaceGroup();
	std::shared_ptr<UiGroup> PokefaceGroup;
	/** Pokeface image of the current trainer's Pokemon. */
	std::shared_ptr<SimpleImageBox> PokefaceImage;
	std::shared_ptr<UiElementSwitcher> CurrentPokemonSwitcher;
	std::shared_ptr<CSVIntHexComboBox> CurrentPokemonComboBox;
	std::shared_ptr<CSVIntHexComboBox> CurrentShadowPokemonComboBox;


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

	bool IsShadowPokemon = false;
};
