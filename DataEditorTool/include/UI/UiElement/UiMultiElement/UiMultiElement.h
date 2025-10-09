/*****************************************************************//**
 * \file   UiMultiElement.h
 * \brief  UiElement that manages and displays multiple child UiElements
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiElement.h"

class UiCSVElement;
class UiConstrainedSize;
class UiSize;

/**
 * \brief UiElement that manages and displays multiple child UiElements
 * 
 * A UiMultiElement contains and displays multiple child UiElements.
 * It handles displaying its child elements and managing their layout.
 */
class UiMultiElement : public UiElement
{
public:

	/**
	 * Construct a UiMultiElement with the supplied name and parent section.
	 * 
	 * \param InName Name of this UiMultiElement.
	 * \param InParent Parent section of this UiMultiElement.
	 */
	UiMultiElement(const std::string& InName, UiSection* InParent);

	/**
	 * Tick all child UiElements managed by this UiMultiElement.
	 */
	virtual void Tick() override;

	/**
	 * Refresh all child UiElements managed by this UiMultiElement.
	 * This should be called whenever the data displayed by any
	 * child UiElement is updated, to ensure the UI reflects the
	 * current state of the data.
	 */
	virtual void Refresh() override;

	/**
	 * Calculate the constrained size of this UiMultiElement,
	 * and calculate the constrained size of all child UiElements.
	 * 
	 * Subclasses may need to override this function depending on
	 * how the layout of their child elements.
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
	 * Set whether or not this element should be displayed
	 * on the same line as the previous element in the parent section.
	 *
	 * \param bInSameLine True if this element should be displayed on the same line as the previous element.
	 */
	virtual void SetSameLine(const bool bInSameLine) override;

	/**
	 * Set whether or not this element should be displayed
	 * on the same line as the previous element in the parent section,
	 * with an offset from the start of the line.
	 * 
	 * \param OffsetFromStart The offset from the start of the line to display this element at.
	 */
	virtual void SetSameLine(const float OffsetFromStart) override;

	/**
	 * Set whether or not this element should be disabled (grayed out).
	 * 
	 * \param bInDisabled True if this element should be disabled.
	 */
	virtual void SetDisabled(const bool bInDisabled) override;

	/**
	 * Add a child UiElement to this UiMultiElement.
	 * 
	 * \param NewElement Element to add to this UiMultiElement.
	 */
	virtual void AddElement(const std::shared_ptr<UiElement> NewElement);

protected:

	/** All UiElements contained in this multi-element. */
	std::vector<std::shared_ptr<UiElement>> UiElements;

};