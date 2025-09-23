#include "include.h"

#include "Command/SwapMoves.h"
#include "UiSections/UiSubsections/LevelUpMoves.h"

SwapMovesCommand::SwapMovesCommand(std::shared_ptr<OldUiSection> InModifiedSection, std::shared_ptr<LevelUpMovesInfo> InLevelUpMoves, const int32_t InMoveOneIndex, const int32_t InMoveTwoIndex) : Command(InModifiedSection), LevelUpMoves(InLevelUpMoves), MoveOneIndex(InMoveOneIndex), MoveTwoIndex(InMoveTwoIndex)
{

}

void SwapMovesCommand::ExecuteCommand()
{
	LevelUpMoves->SwapMoves(MoveOneIndex, MoveTwoIndex);
}

void SwapMovesCommand::UndoCommand()
{
	LevelUpMoves->SwapMoves(MoveOneIndex, MoveTwoIndex);
}

void SwapMovesCommand::RedoCommand()
{
	LevelUpMoves->SwapMoves(MoveOneIndex, MoveTwoIndex);
}

std::string SwapMovesCommand::GetCommandName()
{
	return "Swap moves";
}
