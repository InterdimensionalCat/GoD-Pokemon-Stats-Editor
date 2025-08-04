#pragma once
#include "Command.h"

class LevelUpMovesInfo;

class SwapMovesCommand : public Command {
public:
	SwapMovesCommand(std::shared_ptr<UiSection> InModifiedSection, std::shared_ptr<LevelUpMovesInfo> InLevelUpMoves, const int32_t InMoveOneIndex, const int32_t InMoveTwoIndex);

	void ExecuteCommand() override;

	void UndoCommand() override;

	void RedoCommand() override;

	std::string GetCommandName() override;

private:

	std::shared_ptr<LevelUpMovesInfo> LevelUpMoves;

	int32_t MoveOneIndex;
	int32_t MoveTwoIndex;
};