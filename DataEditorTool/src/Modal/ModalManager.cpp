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
	ICLogger::Debug("Setting currently active modal to {}", InActiveModal->GetModalName());

	if (CurrentlyActiveModal != nullptr)
	{
		ICLogger::Debug("Resetting previously active modal {}", CurrentlyActiveModal->GetModalName());
	}
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