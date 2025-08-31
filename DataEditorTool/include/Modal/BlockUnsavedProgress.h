#pragma once
#include "Modal/Modal.h"

class BlockUnsavedProgress : public Modal
{
public:

	BlockUnsavedProgress(const std::string& InPopupTopMessage, const std::function<void()>& InBypassModalCallback);

protected:

	virtual void OnModalMadeActive() override;

	virtual void DisplayModal() override;

private:

	std::vector<std::string> ModifiedCSVFiles;

	/**
	 * std::deque is needed here becuase std::vector<bool> cannot return
	 * a pointer to each index due to it being stored as a bitfield.
	 */
	std::deque<bool> ButtonSelectionState;

	bool bSelectAll = false;

	std::string PopupTopMessage;

};