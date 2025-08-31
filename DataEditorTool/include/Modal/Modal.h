#pragma once

enum class OpenPopupStatus
{
	Inactive,
	ShouldOpen,
	Active,
	ShouldBypass,
	ShouldClose
};

class Modal
{
public:

	Modal(const std::string& InModalName, const std::function<void()>& InBypassModalCallback);

	void Tick();

	std::string GetModalName() const;

	/** Check if this modal is active or not, only active modals are ticked each frame. */
	bool IsModalActive() const;

	void SetModalStatus(const OpenPopupStatus InStatus);

	// void SetModalActive(const bool IsModalActive);

protected:

	virtual void OnModalMadeActive();

	virtual void DisplayModal();

	std::string ModalName;

	std::function<void()> BypassModalCallback;

	OpenPopupStatus PopupStatus = OpenPopupStatus::Inactive;

};
