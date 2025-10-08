/*****************************************************************//**
 * \file   ModalManager.h
 * \brief  Class that manages the currently active modal.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

class Modal;

/**
 * \brief  Class that manages the currently active modal.
 * 
 * This class keeps track of the currently active modal,
 * and provides functions to tick the modal each frame,
 * set a new active modal, and check if the window is
 * currently blocked by a modal.
 */
class ModalManager
{
public:

	/**
	 * Construct a ModalManager.
	 */
	ModalManager() = default;

	/**
	 * Tick the currently active modal, if there is one.
	 * This will call the modal's Tick() function.
	 */
	void Tick();

	/**
	 * Set the currently active modal to the supplied modal.
	 * This will replace any currently active modal.
	 */
	void SetCurrentlyActiveModal(const std::shared_ptr<Modal> InActiveModal);

	/** Returns true if there is a currently active modal. */
	bool WindowBlockedByModal() const;

private:

	/** The currently active modal, or nullptr if there is none. */
	std::shared_ptr<Modal> CurrentlyActiveModal;

};
