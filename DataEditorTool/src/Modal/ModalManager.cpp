#include "include.h"
#include "Modal/ModalManager.h"
#include "Modal/Modal.h"

void ModalManager::Tick()
{

	if (CurrentlyActiveModal == nullptr)
	{
		return;
	}

	if (CurrentlyActiveModal->IsModalActive())
	{
		CurrentlyActiveModal->Tick();
	}
}

void ModalManager::SetCurrentlyActiveModal(const std::shared_ptr<Modal> InActiveModal)
{
	CurrentlyActiveModal.reset();
	CurrentlyActiveModal = InActiveModal;
	CurrentlyActiveModal->SetModalStatus(OpenPopupStatus::ShouldOpen);
}

bool ModalManager::WindowBlockedByModal() const
{
	if (CurrentlyActiveModal != nullptr)
	{
		return CurrentlyActiveModal->IsModalActive();
	}
	else
	{
		return false;
	}
}