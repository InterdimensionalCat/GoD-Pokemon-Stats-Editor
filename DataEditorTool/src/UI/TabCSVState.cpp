#include "include.h"
#include "UI/TabCSVState.h"

#include "UI/UiTab.h"
#include "UI/UiElement/UiCSVElement/UiCSVElement.h"
#include "Command/Command.h"
#include "Command/CommandQueue.h"

TabCSVState::TabCSVState(UiTab* InParentTab): 
	ParentTab(InParentTab),
	CurrentRow(0),
	bShouldRefresh(false),
	CommandHistory(std::make_shared<CommandQueue>())
{

}

void TabCSVState::Tick()
{
	if (bShouldRefresh)
	{
		Refresh();
		bShouldRefresh = false;
	}
}

void TabCSVState::SetShouldRefresh()
{
	bShouldRefresh = true;
}

void TabCSVState::AddElementToUpdate(UiCSVElement* NewElement)
{
	ElementsToUpdate.push_back(NewElement);
	bShouldRefresh = true;
}

void TabCSVState::PushCommand(std::shared_ptr<Command> NewCommand)
{
	CommandHistory->ExecuteCommand(NewCommand);
	bShouldRefresh = true;
}

void TabCSVState::Undo()
{
	CommandHistory->Undo();
	bShouldRefresh = true;
}

void TabCSVState::Redo()
{
	CommandHistory->Redo();
	bShouldRefresh = true;
}

void TabCSVState::SetCurrentRow(const int32_t NewRowValue)
{
	CurrentRow = NewRowValue;
	bShouldRefresh = true;
}

int32_t TabCSVState::GetCurrentRow() const
{
	return CurrentRow;
}

void TabCSVState::Refresh()
{
	for (auto& Element : ElementsToUpdate)
	{
		if (Element->ShouldSyncRowToCSVState())
		{
			Element->SetCurrentRow(CurrentRow);
		}
	}

	ParentTab->Refresh();
}

bool TabCSVState::CanUndo() const
{
	return CommandHistory->CanUndo();
}

bool TabCSVState::CanRedo() const
{
	return CommandHistory->CanRedo();
}