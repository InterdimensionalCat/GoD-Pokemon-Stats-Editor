#pragma once
#include "UI/MultiUiElement.h"

class UiCSVElement;

class UiElementSwitcher : public MultiUiElement
{
public:

	UiElementSwitcher(const std::string& InName, UiSection* InParent);

	virtual void Tick() override;

	virtual void Refresh() override;

	virtual void PushConstrainedElementSize();

	virtual void PopConstrainedElementSize();

	virtual void PushConstrainedSizeForElement(const uint32_t ElementIndex);

	virtual void PopConstrainedSizeForElement(const uint32_t ElementIndex);

	virtual void AddCSVElement(const std::shared_ptr<UiCSVElement> NewElement);
	virtual void AddElement(const std::shared_ptr<UiElement> NewElement);

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

	std::vector<std::shared_ptr<UiElement>> UiElementsToSwitchBetween;

};
