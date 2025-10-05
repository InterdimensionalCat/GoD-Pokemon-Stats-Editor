#pragma once
#include "Command/Command.h"

class MultiCommand : public Command {

public:

	MultiCommand();

	MultiCommand(const std::string& InCommandName);

	void AddCommandAndExecute(std::shared_ptr<Command> NewCommand);

	void Execute() override;

	void Undo() override;

	void Redo() override;

	std::string GetName() const override;

	std::string ToString() const override;

protected:

	std::string CommandName = "Multi Command";

	std::vector<std::shared_ptr<Command>> SubCommands;

};