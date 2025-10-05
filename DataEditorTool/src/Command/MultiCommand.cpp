#include "include.h"
#include "Command/MultiCommand.h"

MultiCommand::MultiCommand() 
{
	
}

MultiCommand::MultiCommand(const std::string& InCommandName) 
	: CommandName(InCommandName) 
{
	
}

void MultiCommand::AddCommandAndExecute(std::shared_ptr<Command> NewCommand)
{
	NewCommand->Execute();
	SubCommands.push_back(NewCommand);
}

void MultiCommand::Execute()
{
	// Implementation left intentionally blank.
}

void MultiCommand::Undo()
{
	// Undo all sub-commands in reverse order.
	for (auto CommandIt = SubCommands.rbegin(); CommandIt != SubCommands.rend(); ++CommandIt)
	{
		(*CommandIt)->Undo();
	}
}

void MultiCommand::Redo()
{
	// Redo all sub-commands in original order.
	for (const auto& Command : SubCommands)
	{
		Command->Redo();
	}
}

std::string MultiCommand::GetName() const
{
	return CommandName;
}

std::string MultiCommand::ToString() const
{
	std::string Result = "";
	for (const auto& Command : SubCommands)
	{
		Result += "\n" + Command->ToString();
	}
	return Result;
}