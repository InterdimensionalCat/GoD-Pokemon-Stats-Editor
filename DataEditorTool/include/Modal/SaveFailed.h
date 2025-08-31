#pragma once
#include "Modal/Modal.h"

class SaveFailed : public Modal
{
public:

	SaveFailed(
		std::vector<std::pair<std::string, std::string>> InFailedCSVFiles, 
		const std::function<void()>& InBypassModalCallback);

protected:

	virtual void OnModalMadeActive() override;

	virtual void DisplayModal() override;

private:

	std::vector<std::pair<std::string, std::string>> FailedCSVFiles;

	/**
	 * std::deque is needed here becuase std::vector<bool> cannot return
	 * a pointer to each index due to it being stored as a bitfield.
	 */
	std::deque<bool> ButtonSelectionState;

	bool bSelectAll = false;

	const std::string PopupTopMessage = "Some files failed to Save";

};