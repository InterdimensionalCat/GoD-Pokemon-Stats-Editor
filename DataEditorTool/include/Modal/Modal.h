/*****************************************************************//**
 * \file   Modal.h
 * \brief  Class representing a blocking modal popup window in ImGui.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

/** Possible states for a Modal popup. */
enum class OpenPopupStatus
{
	Inactive,
	ShouldOpen,
	Active,
	ShouldBypass,
	ShouldClose
};

/**
 * \brief  Class representing a blocking modal popup window in ImGui.
 * 
 * This class represents a blocking modal popup window in ImGui.
 * It can be activated, deactivated, and ticked each frame to
 * display its contents when active.
 * 
 * When the modal is activated, the OnModalMadeActive() function
 * is called, which can be overridden by subclasses to perform
 * any necessary setup when the modal becomes active.
 * 
 * The DisplayModal() function is called each frame when the
 * modal is active, and should be overridden by subclasses to
 * display the contents of the modal.
 * 
 * If the modal is bypassed (for example, if the user chooses
 * to not save changes), the BypassModalCallback function
 * is called if it was provided in the constructor.
 */
class Modal
{
public:

	/**
	 * Construct a Modal with the specified name.
	 * The name is used to identify the modal in ImGui.
	 * 
	 * An optional BypassModalCallback can be provided,
	 * which will be called if the modal is bypassed
	 * (for example, if the user chooses to not save changes).
	 * 
	 * \param InModalName The name of the modal.
	 * \param InBypassModalCallback Optional callback to call if the modal is bypassed.
	 */
	Modal(const std::string& InModalName, const std::function<void()>& InBypassModalCallback);

	/**
	 * Tick this modal. This will call DisplayModal()
	 * and update the PopupStatus state as needed.
	 */
	void Tick();

	/**
	 * Get the name of this modal.
	 * 
	 * \return The name of this modal.
	 */
	std::string GetModalName() const;

	/**
	 * Check if this modal is active or not, only active modals are ticked each frame.
	 * 
	 * \return True if this modal is active, false otherwise.
	 */
	bool IsModalActive() const;

	/**
	 * Set the status of this modal, which will trigger state
	 * updates the next time Tick() is called.
	 * 
	 * \param InStatus The new status to set for this modal.
	 */
	void SetModalStatus(const OpenPopupStatus InStatus);

protected:

	/** Called when this modal is made active. This should be overridden by subclasses. */
	virtual void OnModalMadeActive() = 0;

	/** Called each frame when this modal is active. This should be overridden by subclasses to display the modal contents. */
	virtual void DisplayModal() = 0;

	/** The name of this modal. */
	std::string ModalName;

	/** Optional callback to call if the modal is bypassed. */
	std::function<void()> BypassModalCallback;

	/** The current status of this modal. */
	OpenPopupStatus PopupStatus = OpenPopupStatus::Inactive;
};
