#pragma once

#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"

class CSVComboBox;
class CSVIntBox;
class PokemonStatsLearnedMoves;

template<typename T>
class SimpleDragDropButton;

class LevelUpMove : public UiSingleLineMultiElement
{

public:

	LevelUpMove(
		const std::string& InName,
		PokemonStatsLearnedMoves* InParent,
		int32_t InLevelUpMoveNumber
	);

	virtual void Tick() override;

private:

	PokemonStatsLearnedMoves* ParentLearnedMoves;

	int32_t LevelUpMoveIndex = 0;

	std::shared_ptr<SimpleDragDropButton<int32_t>> DragDrop;

	std::shared_ptr<CSVComboBox> MoveComboBox;

	std::shared_ptr<CSVIntBox> LevelIntBox;

};
