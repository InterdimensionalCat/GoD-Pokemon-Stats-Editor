#pragma once

class Command;

class CommandQueue {

public:

	CommandQueue();

	void ExecuteCommand(std::shared_ptr<Command> NewCommand);

	void Undo();

	void Redo();

	bool CanUndo();

	bool CanRedo();

	void Clear();

private:

	/**
	 * Queue of commands that have been executed and
	 * can be undone/redone.
	 */
	std::vector<std::shared_ptr<Command>> UndoQueue;

	/**
	 * The index of the last executed command that has not
	 * been undone. Any commands past this index will be
	 * deleted when a new command is executed.
	 */
	int32_t CurrentCommand;
};