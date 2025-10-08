/*****************************************************************//**
 * \file   CommandQueue.h
 * \brief  Class that manages a queue of commands for undo/redo functionality.
 * 
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

class Command;

/**
 * \brief  Class that manages a queue of commands for undo/redo functionality.
 * 
 * This class maintains a list of executed commands and allows
 * undoing and redoing them in sequence. When a new command is executed,
 * any commands that were undone are discarded. Each UiTab has a unique
 * CommandQueue (located on its TabCSVState) to manage its own command 
 * history. Most commands are simply modifications to a CSV file, but 
 * some commands perform other functions, such as switching the 
 * current row.
 */
class CommandQueue {

public:

	/**
	 * Construct a CommandQueue with no commands.
	 */
	CommandQueue();

	/**
	 * Execute a new command and add it to the queue.
	 * 
	 * This will call the Execute() method on the command,
	 * and add it to the queue. If there are any commands
	 * that were undone, they will be deleted from the queue.
	 * 
	 * \param NewCommand The command to execute and add to the queue.
	 */
	void ExecuteCommand(std::shared_ptr<Command> NewCommand);

	/** Undo the last executed command in the queue. */
	void Undo();

	/** Redo the last undone command in the queue. */
	void Redo();

	/** Is there a command that can be undone in this queue? */
	bool CanUndo();

	/** Is there a command that can be redone in this queue? */
	bool CanRedo();

	/** Clear all commands from the queue. */
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