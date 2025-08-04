#pragma once

//#include <string>

class UnsavedProgressModal {
public:

	UnsavedProgressModal(const bool InCloseWindow, const std::string& InPopupMsg);

	void Tick();

	bool GetEnabled() const;

	void SetEnabled(const bool InEnabled);

	bool GetBypassModal() const;

	void SetBypassModal(const bool InBypassModal);

protected:

	std::string PopupMsg;

	bool bCloseWindow;

	bool bEnabled = false;

	bool bBypassModal = false;
};
