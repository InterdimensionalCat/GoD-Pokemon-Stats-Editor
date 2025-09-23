#pragma once
#include "UiSections/UiSection.h"
//#include <vector>
//#include <memory>
//#include <string>

class OldUiSection;

class Command {
public:
	Command(std::shared_ptr<OldUiSection> InModifiedSection);

	virtual void ExecuteCommand();

	virtual void UndoCommand();

	virtual void RedoCommand();

	virtual std::string GetCommandName();

	static void PushNewCommandAndExecute(std::shared_ptr<Command> NewCommand);

	static void Undo();

	static void Redo();

	static bool CanUndo();

	static bool CanRedo();

	static void ClearCommandQueue();

private:

	std::shared_ptr<OldUiSection> ModifiedSection;

	static std::vector<std::shared_ptr<Command>> CommandQueue;
	static int32_t CurrentCommand;
};