#pragma once

class Modal;

class ModalManager
{
public:

	ModalManager() = default;

	void Tick();

	void SetCurrentlyActiveModal(const std::shared_ptr<Modal> InActiveModal);

	bool WindowBlockedByModal() const;

private:

	std::shared_ptr<Modal> CurrentlyActiveModal;

};
