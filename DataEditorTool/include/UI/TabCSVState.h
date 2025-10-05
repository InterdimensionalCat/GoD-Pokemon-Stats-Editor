#pragma once

class UiTab;
class UiCSVElement;
class Command;
class CommandQueue;

/** TODO: rename to UiTabController **/
class TabCSVState
{

public:

	/**
	 * TODO: Allow multiple CSV files to have a current row so we can link entries from multiple
	 * CSV files together in one tab.
	 */
	TabCSVState(UiTab* InParentTab);

	void Tick();

	void SetShouldRefresh();

	void AddElementToUpdate(UiCSVElement* NewElement);

	void PushCommand(std::shared_ptr<Command> NewCommand);

	void Undo();

	void Redo();

	void SetCurrentRow(const int32_t NewRowValue);

	bool CanUndo() const;

	bool CanRedo() const;

	int32_t GetCurrentRow() const;

private:

	void Refresh();

	bool bShouldRefresh = false;

	/** Smart pointer not needed because we don't own this object. */
	UiTab* ParentTab;

	int32_t CurrentRow = 0;

	/**
	 * TODO: if element removal is ever implemented, 
	 * then raw UiCSVElement pointers could potentially 
	 * become invalid, and we will likely need to change this.
	 */
	std::vector<UiCSVElement*> ElementsToUpdate;

	/**
	 * Undo/Redo queue for this tab.
	 */
	std::shared_ptr<CommandQueue> CommandHistory;
};
