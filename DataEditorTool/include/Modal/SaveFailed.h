/*****************************************************************//**
 * \file   SaveFailed.h
 * \brief  Modal that displays a list of files that failed to save.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "Modal/Modal.h"

/**
 * \brief  Modal that displays a list of files that failed to save.
 * 
 * This modal will display a list of files that failed to save,
 * along with the reason for the failure. The user can select
 * which files to attempt to save again, or choose to bypass
 * saving these files.
 */
class SaveFailed : public Modal
{
public:

	/**
	 * Construct a SaveFailed modal with the specified list of failed files.
	 * Each entry in the list should be a pair of:
	 * {FileName, FailureReason}
	 * 
	 * An optional BypassModalCallback can be provided,
	 * which will be called if the user chooses to bypass
	 * saving the failed files.
	 */
	SaveFailed(
		std::vector<std::pair<std::string, std::string>> InFailedCSVFiles, 
		const std::function<void()>& InBypassModalCallback);

protected:

	/** Called when this modal is made active. */
	virtual void OnModalMadeActive() override;

	/** Called each frame when this modal is active. This displays the modal contents. */
	virtual void DisplayModal() override;

private:

	/** The list of files that failed to save, along with the reason for the failure. */
	std::vector<std::pair<std::string, std::string>> FailedCSVFiles;

	/**
	 * Selection state for each retry save toggle button.
	 * std::deque is needed here becuase std::vector<bool> cannot return
	 * a pointer to each index due to it being stored as a bitfield.
	 */
	std::deque<bool> ButtonSelectionState;

	/** Whether or not the "Select All" checkbox is checked. */
	bool bSelectAll = false;

	/**
	 * Message to display at the top of the modal,
	 * above the list of save failed CSV files.
	 */
	const std::string PopupTopMessage = "Some files failed to Save";

};