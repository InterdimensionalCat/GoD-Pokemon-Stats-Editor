/*****************************************************************//**
 * \file   LevelUpMove.h
 * \brief  UiElement representing a single level-up move for a Pokemon.
 * 
 * \author bthomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"

class CSVComboBox;
class CSVIntBox;
class PokemonStatsLearnedMoves;

template<typename T>
class SimpleDragDropButton;

/**
 * \brief  UiElement representing a single level-up move for a Pokemon.
 * 
 * This element contains a drag-and-drop handle, a combo box for selecting
 * the move, and an integer box for specifying the level at which the
 * Pokemon learns the move.
 * 
 * This element is designed to be used within a PokemonStatsLearnedMoves
 * UiSection, which manages multiple LevelUpMove elements.
 */
class LevelUpMove : public UiSingleLineMultiElement
{

public:

	/**
	 * Construct a LevelUpMove element with the specified name,
	 * parent PokemonStatsLearnedMoves section, and index within
	 * that section.
	 * 
	 * The InLevelUpMoveNumber is used to identify this element
	 * within its parent section, and should be unique among
	 * all LevelUpMove elements in that section.
	 * 
	 * \param InName Name of this LevelUpMove element.
	 * \param InParent Parent PokemonStatsLearnedMoves section.
	 * \param InLevelUpMoveNumber Index of this LevelUpMove within its parent section.
	 */
	LevelUpMove(
		const std::string& InName,
		PokemonStatsLearnedMoves* InParent,
		int32_t InLevelUpMoveNumber
	);

	/**
	 * Draw the invisible Drag/drop button and handle drag/drop
	 * behavior if a drag/drop target is received.
	 */
	virtual void Tick() override;

private:

	/** Reference to the parent PokemonStatsLearnedMoves section. */
	PokemonStatsLearnedMoves* ParentLearnedMoves;

	/** The index of this LevelUpMove within its parent section. */
	int32_t LevelUpMoveIndex = 0;

	/** The drag-and-drop handle for this LevelUpMove element. */
	std::shared_ptr<SimpleDragDropButton<int32_t>> DragDrop;

	/** The combo box for selecting the move. */
	std::shared_ptr<CSVComboBox> MoveComboBox;

	/** The integer box for specifying the level. */
	std::shared_ptr<CSVIntBox> LevelIntBox;

};
