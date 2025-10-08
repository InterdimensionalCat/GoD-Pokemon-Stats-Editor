/*****************************************************************//**
 * \file   BlockUnsavedProgress.h
 * \brief  Modal that blocks progress if there are unsaved changes in any open CSV files.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "Modal/Modal.h"

/**
 * \brief  Modal that blocks progress if there are unsaved changes in any open CSV files.
 * 
 * This modal will display a list of all modified CSV files,
 * and allow the user to select which ones to save before
 * proceeding. The user can also choose to bypass the modal
 * and not save any changes, which will call the optional
 * BypassModalCallback provided in the constructor.
 */
class BlockUnsavedProgress : public Modal
{
public:

	/**
	 * Construct a BlockUnsavedProgress modal with the specified top message.
	 * The top message is displayed above the list of modified CSV files.
	 * 
	 * An optional BypassModalCallback can be provided,
	 * which will be called if the modal is bypassed
	 * (for example, if the user chooses to not save changes).
	 */
	BlockUnsavedProgress(const std::string& InPopupTopMessage, const std::function<void()>& InBypassModalCallback);

protected:

	/**
	 * Called when this modal is made active.
	 * This will clear any previous button state and
	 * get the list of modified CSV files.
	 */
	virtual void OnModalMadeActive() override;

	/** Called each frame when this modal is active. This will display the modal contents. */
	virtual void DisplayModal() override;

private:

	/** List of all modified CSV files that need to be saved. */
	std::vector<std::string> ModifiedCSVFiles;

	/**
	 * Selection state for each save toggle button.
	 * std::deque is needed here becuase std::vector<bool> cannot return
	 * a pointer to each index due to it being stored as a bitfield.
	 */
	std::deque<bool> ButtonSelectionState;

	/** Whether or not the "Select All" checkbox is checked. */
	bool bSelectAll = false;

	/**
	 * Message to display at the top of the modal,
	 * above the list of modified CSV files.
	 */
	std::string PopupTopMessage;

};