/*****************************************************************//**
 * \file   MultiCommand.h
 * \brief  Command that executes multiple sub-commands in sequence.
 * 
 * \author bthomas
 * \date   October 2025
 *********************************************************************/
#pragma once
#include "Command/Command.h"

/**
 * \brief  Command that executes multiple sub-commands in sequence.
 * 
 * This command can be used to group multiple commands into a single
 * command that can be executed, undone, and redone as a unit.
 * 
 * The name of this command can be specified in the constructor,
 * otherwise it will default to "Multi Command".
 */
class MultiCommand : public Command {

public:

	/** Construct a MultiCommand with the default name "Multi Command". */
	MultiCommand();

	/** Construct a MultiCommand with the specified name. */
	MultiCommand(const std::string& InCommandName);

	/** Add a new sub-command to this MultiCommand and execute it immediately. */
	void AddCommandAndExecute(std::shared_ptr<Command> NewCommand);

	/**
	 * Execute does nothing in the MultiCommand implementation,
	 * as subcommands are executed as they are added.
	 */
	void Execute() override;

	/** Undo all sub-commands in reverse order. */
	void Undo() override;

	/** Redo all sub-commands in order. */
	void Redo() override;

	/** Get the name of this MultiCommand. */
	std::string GetName() const override;

	/** Get a string representation of each sub-command's action. */
	std::string ToString() const override;

protected:

	/** The name of this MultiCommand. Defaults to "Multi Command". */
	std::string CommandName = "Multi Command";

	/** The sub-commands that make up this MultiCommand. */
	std::vector<std::shared_ptr<Command>> SubCommands;

};