/*****************************************************************//**
 * \file   TabCSVState.h
 * \brief  Class that interfaces between a UiTab's UI and the CSV data it displays.
 *
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

class UiTab;
class UiCSVElement;
class Command;
class CommandQueue;

/** TODO: rename to UiTabController **/
/**
 * \brief  Class that interfaces between a UiTab's UI and the CSV data it displays.
 * 
 * Contains a current row index, which is shared by all UiCSVElements with row
 * sharing enabled. Also contains the Undo/Redo command queue for this tab.
 */
class TabCSVState
{

public:

	 /**
	  * Construct a TabCSVState for the supplied UiTab.
	  *  
	  * TODO: Allow multiple CSV files to have a current row so we can link entries from multiple
	  * CSV files together in one tab.
	  * 
	  * \param InParentTab Parent UiTab for this TabCSVState.
	  */
	TabCSVState(UiTab* InParentTab);

	/** Refresh this UiTab if bShouldRefresh is set. */
	void Tick();

	/** Mark this TabCSVState to refresh on the next tick. */
	void SetShouldRefresh();

	/**
	 * Add a UiCSVElement to the list of elements to update
	 * when the current row changes.
	 * 
	 * \param NewElement Element to add to the update list.
	 */
	void AddElementToUpdate(UiCSVElement* NewElement);

	/**
	 * Execute a new command and add it to this tab's the undo/redo queue.
	 * 
	 * This will call the Execute() function on the command,
	 * and add it to the queue. If there are any commands
	 * that were undone, they will be deleted from the queue.
	 * 
	 * \param NewCommand The command to execute and add to the queue.
	 */
	void PushCommand(std::shared_ptr<Command> NewCommand);

	/** Undo the last executed command in this tab's command queue. */
	void Undo();

	/** Redo the last undone command in this tab's command queue. */
	void Redo();

	/**
	 * Set the current row for this tab, and update all
	 * all UiCSVElements that are syncing to this tab's current row.
	 * 
	 * \param NewRowValue New current row value for this tab.
	 */
	void SetCurrentRow(const int32_t NewRowValue);

	/** Is there a command that can be undone in this tab's command queue? 
	 *
	 * \return True if there is a command that can be undone.
	 */
	bool CanUndo() const;

	/** Is there a command that can be redone in this tab's command queue? 
	 *
	 * \return True if there is a command that can be redone.
	 */
	bool CanRedo() const;

	/**
	 * Get the current row for this tab.
	 * 
	 * \return The current row for this tab.
	 */
	int32_t GetCurrentRow() const;

private:

	/** Refresh all UiCSVElements that need updating, and refresh the parent tab. */
	void Refresh();

	/** Should we refresh the parent tab on the next tick? */
	bool bShouldRefresh = false;

	/** 
	 * The UiTab this TabCSVState belongs to.
	 * Smart pointer not needed because we don't own this object. 
	 */
	UiTab* ParentTab;

	/** Current row index for this tab. */
	int32_t CurrentRow = 0;

	/**
	 * List of UiCSVElements that need to be updated when the current row changes.
	 * 
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
