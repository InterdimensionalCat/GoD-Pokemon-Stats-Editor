/*****************************************************************//**
 * \file   UiElement.h
 * \brief Lowest level Ui object. Manages and displays 1 UI element.
 * Such as a button or text entry box. Ui elements in ImGui always 
 * have a label along with a UI element. both need to be used in width calcluations
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once
#include "UI/UiObject.h"

class UiSection;
class UiSize;
class UiConstrainedSize;

/**
 * Lowest level Ui object. Manages and displays 1 UI element.
 * Such as a button or text entry box.
 *
 * Ui elements in ImGui always have a label along with a UI element.
 * both need to be used in width calculations
 */
class UiElement : public UiObject
{
public:

	UiElement(const std::string& InName, UiSection* InParent);

	/**
	 * Tick any child UiElements and display any UiComponents
	 */
	virtual void Tick() override = 0;

	/**
	 * Calculate the constrained size of this UiElement,
	 * and calculate the constrained size of  any child UiElements.
	 * 
	 * This will be the pushed item width for this element.
	 */
	virtual void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	);

	void SetShouldOverrideSyncedSize(const bool bInShouldOverride);

	/**
	 * Get the size constraints for this UiElement. For single UiElements
	 * this will be the size constraints of its UiComponent, for
	 * UiMultiElements this will be a UiCompoundSize depending on the
	 * type of MultiElement.
	 */
	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const = 0;

	virtual void SetSameLine(const bool bInSameLine) = 0;

	virtual void SetDisabled(const bool bInDisabled) = 0;

	bool ShouldOverrideSyncedSize() const;

protected:

	UiSection* ParentSection;

	std::shared_ptr<UiConstrainedSize> ConstrainedSize;

private:

	bool bShouldOverrideSyncedSize = false;

	// put in single UIElement
	// std::shared_ptr<UiComponent> UiComponent;

	/**
	 * A single UiElement doesn't have its own UiSize,
	 * but does have a getter for one, because it inherits
	 * it size constraints from its UiComponent. However,
	 * MultiUiElements do have their own UiSize.
	 */
	// UiSize ElementSize;

};
