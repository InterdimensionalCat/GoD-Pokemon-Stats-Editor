#pragma once

#include "UI/UiElement/UiMultiElement/UiMultiElement.h"

class UiSyncedSize;
class UiConstrainedSize;
class UiSize;

class UiElementSwitcher : public UiMultiElement
{
public:

	UiElementSwitcher(const std::string& InName, UiSection* InParent);

	void Tick() override;

	virtual void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	);

	virtual void AddElement(const std::shared_ptr<UiElement> NewElement) override;

	void SwitchCurrentlyActiveElement(std::shared_ptr<UiElement> NewActiveElement);

	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

protected:

	std::shared_ptr<UiElement> CurrentlyActiveElement;

private:

	/**
	 * The size constraints for an element switcher is
	 * always the synced size between all its possible
	 * child elements.
	 */
	std::shared_ptr<UiSyncedSize> SizeConstraints;

	int32_t CurrentlyActiveElementIndex = -1;

};