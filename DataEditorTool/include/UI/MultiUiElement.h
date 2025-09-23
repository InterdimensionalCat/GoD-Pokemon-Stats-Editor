#pragma once
#include "UI/UiElement.h"

class UiCSVElement;

class MultiUiElement : public UiElement
{
public:

	MultiUiElement(const std::string& InName, UiSection* InParent);

	virtual void Tick() override;

	virtual void Refresh() override;

	/**
	 * Sets the ImGui next element width to the appropreate
	 * value for this UiElement based on its UiSizeSource.
	 */
	virtual void PushConstrainedElementSize();

	/**
	 * Pops the ImGui next element width set by
	 * PushConstrainedElementSize().
	 */
	virtual void PopConstrainedElementSize();

	virtual void PushConstrainedSizeForElement(const uint32_t ElementIndex);

	virtual void PopConstrainedSizeForElement(const uint32_t ElementIndex);

	virtual void AddCSVElement(const std::shared_ptr<UiCSVElement> NewElement);
	virtual void AddElement(const std::shared_ptr<UiElement> NewElement);

	/**
	 * The min/max of a multi-line element is the sum
	 * of the max/min of each of its child elements.
	 */
	virtual void CalculateSizeConstraints();

	/**
	 * The label size for this is the combined
	 * label size of all its elements.
	 */
	virtual float GetLabelSize() override;

protected:

	std::vector<std::shared_ptr<UiElement>> UiElements;

	float ConstrainedSizeForThisFrame = 0;

};
