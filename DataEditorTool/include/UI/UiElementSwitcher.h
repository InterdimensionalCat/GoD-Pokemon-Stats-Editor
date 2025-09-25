#pragma once
#include "UI/MultiUiElement.h"

class UiCSVElement;

class UiElementSwitcher : public MultiUiElement
{
public:

	UiElementSwitcher(const std::string& InName, UiSection* InParent);

	virtual void Tick() override;

	void SwitchCurrentlyActiveElement(std::shared_ptr<UiElement> NewActiveElement);

	/**
	 * The size constraints of an element switcher is the size constraints
	 * of its largest element
	 */
	virtual void CalculateSizeConstraints() override;

	/**
	 * The label size of an element switcher is
	 * the label size of its largest element
	 */
	virtual float GetLabelSize() override;

private:

	std::shared_ptr<UiElement> CurrentlyActiveElement;

	int32_t CurrentlyActiveElementIndex = -1;

};
