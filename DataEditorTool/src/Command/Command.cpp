#include "include.h"

#include "Command/Command.h"

std::vector<std::shared_ptr<Command>> Command::CommandQueue = std::vector<std::shared_ptr<Command>>();
int32_t Command::CurrentCommand = -1;

Command::Command(std::shared_ptr<OldUiSection> InModifiedSection) : ModifiedSection(InModifiedSection)
{

}

void Command::ExecuteCommand()
{

}

void Command::UndoCommand()
{

}

void Command::RedoCommand()
{

}

std::string Command::GetCommandName()
{
	return "Base Command";
}

void Command::PushNewCommandAndExecute(std::shared_ptr<Command> NewCommand)
{

	// If current command is not at the end, pop old redo commands until we are at the end.
	int32_t OldCommandsIndex = CommandQueue.size() - 1;
	while (CurrentCommand < OldCommandsIndex)
	{
		CommandQueue.pop_back();
		OldCommandsIndex--;
	}

	// Execute the new command before adding it to the queue.
	NewCommand->ExecuteCommand();

	// The section executed on now has unsaved progress.
	NewCommand->ModifiedSection->SetUnsavedProgress(true);

	// Push the new command and update the current command value.
	CommandQueue.push_back(NewCommand);
	CurrentCommand += 1;
}

void Command::Undo()
{
	// Ensure that we can undo.
	if (!CanUndo())
	{
		return;
	}

	// Run the undo function for the current command.
	CommandQueue.at(CurrentCommand)->UndoCommand();

	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Success, 2000);
	toast->setTitle("Undo");
	std::cout << "Undo: " << CommandQueue.at(CurrentCommand)->GetCommandName() << "\n";
	toast->setContent("Undo: %s", CommandQueue.at(CurrentCommand)->GetCommandName().c_str());
	ImGui::InsertNotification(*toast);

	// Move the current command back one.
	CurrentCommand -= 1;
}

void Command::Redo()
{
	// Ensure that we can redo.
	if (!CanRedo())
	{
		return;
	};

	// Move the current command forward one.
	CurrentCommand += 1;

	// Run the redo function for the current command.
	CommandQueue.at(CurrentCommand)->RedoCommand();

	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Success, 2000);
	toast->setTitle("Redo");
	std::cout << "Redo: " << CommandQueue.at(CurrentCommand)->GetCommandName() << "\n";
	toast->setContent("Redo: %s", CommandQueue.at(CurrentCommand)->GetCommandName().c_str());
	ImGui::InsertNotification(*toast);

}

bool Command::CanUndo()
{
	// Can't undo if the queue is empty, or if the current command is -1
	return (!CommandQueue.empty() && CurrentCommand >= 0);
}

bool Command::CanRedo()
{
	// Can't redo if the queue is empty, or if there are no commands ahead of the current one.
	bool bQueueNotEmpty = !CommandQueue.empty();
	int32_t LastQueueIndex = CommandQueue.size() - 1;
	bool bNotAtHead = CurrentCommand < LastQueueIndex;
	return (bQueueNotEmpty && bNotAtHead);
}

void Command::ClearCommandQueue()
{
	CommandQueue.clear();
	CurrentCommand = -1;
}
