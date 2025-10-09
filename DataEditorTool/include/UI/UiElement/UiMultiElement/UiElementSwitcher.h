/*****************************************************************//**
 * \file   UiElementSwitcher.h
 * \brief  UiMultiElement that only displays one child element at a time,
 * but can switch which element is displayed.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiMultiElement.h"

class UiSyncedSize;
class UiConstrainedSize;
class UiSize;

/**
 * \brief UiMultiElement that only displays one child element at a time,
 * but can switch which element is displayed.
 * 
 * A UiElementSwitcher manages multiple child UiElements, but only
 * displays one of them at a time. It provides a function to switch
 * which child element is currently active and being displayed.
 * The size constraints of the switcher are synced between all its
 * child elements, so switching elements does not cause layout shifts.
 */
class UiElementSwitcher : public UiMultiElement
{
public:

	/**
	 * Construct a UiElementSwitcher with the supplied name and parent section.
	 * 
	 * \param InName Name of this UiElementSwitcher.
	 * \param InParent Parent section of this UiElementSwitcher.
	 */
	UiElementSwitcher(const std::string& InName, UiSection* InParent);

	/**
	 * Tick the currently active child UiElement.
	 */
	void Tick() override;

	/**
	 * Calculate the constrained size of this UiElementSwitcher,
	 * and calculate the constrained size of all child UiElements.
	 * 
	 * A UiElementSwitcher calculates its size constraints to be
	 * the synced size between all its child elements, so that
	 * switching the active element does not cause layout shifts.
	 * It also only calculates the constrained size of the currently
	 * active child element, as that is the only one being displayed.
	 * 
	 * This will be the pushed item width for this element.
	 * 
	 * \param ParentConstrainedSize The constrained size of the parent UiElement.
	 * \param ParentSizeConstraints The size constraints of the parent UiElement.
	 */
	virtual void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	);

	/**
	 * Add a child UiElement to this UiElementSwitcher. This will
	 * update the size constraints of the switcher to include
	 * the new element.
	 * 
	 * The first element added will be set as the the currently
	 * active element by default.
	 * 
	 * \param NewElement Element to add to this UiElementSwitcher.
	 */
	virtual void AddElement(const std::shared_ptr<UiElement> NewElement) override;

	/**
	 * Switch the currently active child UiElement to the supplied element.
	 * If the supplied element is not a child of this switcher, this function
	 * will do nothing.
	 * 
	 * \param NewActiveElement The new element to set as active.
	 */
	void SwitchCurrentlyActiveElement(std::shared_ptr<UiElement> NewActiveElement);

	/**
	 * Get the size constraints for this UiElementSwitcher.
	 * 
	 * The size constraints for an element switcher is
	 * the synced size between all its possible
	 * child elements.
	 */
	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

protected:

	/** The currently active child UiElement being displayed. */
	std::shared_ptr<UiElement> CurrentlyActiveElement;

private:

	/**
	 * The size constraints for an element switcher is
	 * always the synced size between all its possible
	 * child elements.
	 */
	std::shared_ptr<UiSyncedSize> SizeConstraints;

	/** The index of the currently active element in the UiElements vector, or -1 if none is active. */
	int32_t CurrentlyActiveElementIndex = -1;

};