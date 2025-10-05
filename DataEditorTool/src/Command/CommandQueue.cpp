#include "include.h"
#include "Command/CommandQueue.h"
#include "Command/Command.h"

CommandQueue::CommandQueue() :
	UndoQueue(std::vector<std::shared_ptr<Command>>()),
	CurrentCommand(-1)
{

}

void CommandQueue::ExecuteCommand(std::shared_ptr<Command> NewCommand)
{
	// If current command is not at the end, pop old undone commands until we are at the end.
	int32_t OldCommandsIndex = UndoQueue.size() - 1;
	while (CurrentCommand < OldCommandsIndex)
	{
		ICLogger::Info("Undone command removed: {}: {}", UndoQueue.at(OldCommandsIndex)->GetName(), UndoQueue.at(OldCommandsIndex)->ToString());
		UndoQueue.pop_back();
		OldCommandsIndex--;
	}

	// Execute the new command before adding it to the queue.
	ICLogger::Info("Executing new Command: {}: {}", NewCommand->GetName(), NewCommand->ToString());
	NewCommand->Execute();

	// Push the new command and update the current command value.
	UndoQueue.push_back(NewCommand);
	CurrentCommand += 1;
}

void CommandQueue::Undo()
{
	// Ensure that we can undo.
	if (!CanUndo())
	{
		ICLogger::Warn("ComandQueue::Undo called when there are no commands that can be undone");
		return;
	}


	std::shared_ptr<Command> CommandToUndo = UndoQueue.at(CurrentCommand);

	// Run the undo function for the current command.
	CommandToUndo->Undo();

	// Move the current command back one.
	CurrentCommand -= 1;

	// Show a notification that we performed an undo operation.
	auto InfoNotifTitle = std::format("Undo: {}", CommandToUndo->GetName());
	ICLogger::Info("{}", InfoNotifTitle);
	ICLogger::PushInfoNotification(InfoNotifTitle, 2000, "Undoing: {}", CommandToUndo->ToString());
}

void CommandQueue::Redo()
{
	// Ensure that we can redo.
	if (!CanRedo())
	{
		ICLogger::Warn("ComandQueue::Redo called when there are no commands that can be redone");
		return;
	};

	// Move the current command forward one.
	CurrentCommand += 1;
	std::shared_ptr<Command> CommandToRedo = UndoQueue.at(CurrentCommand);

	// Run the redo function for the current command.
	CommandToRedo->Redo();

	// Show a notification that we performed a redo operation.
	auto InfoNotifTitle = std::format("Redo: {}", CommandToRedo->GetName());
	ICLogger::Info("{}", InfoNotifTitle);
	ICLogger::PushInfoNotification(InfoNotifTitle, 2000, "Redoing: {}", CommandToRedo->ToString());
}

bool CommandQueue::CanUndo()
{
	// Can't undo if the queue is empty, or if the current command is -1
	return (!UndoQueue.empty() && CurrentCommand >= 0);
}

bool CommandQueue::CanRedo()
{
	// Can't redo if the queue is empty, or if there are no commands ahead of the current one.
	bool bQueueNotEmpty = !UndoQueue.empty();
	int32_t LastQueueIndex = UndoQueue.size() - 1;
	bool bNotAtHead = CurrentCommand < LastQueueIndex;
	return (bQueueNotEmpty && bNotAtHead);
}

void CommandQueue::Clear()
{
	UndoQueue.clear();
	CurrentCommand = -1;
}
