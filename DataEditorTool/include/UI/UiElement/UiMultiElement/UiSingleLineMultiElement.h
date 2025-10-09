/*****************************************************************//**
 * \file   UiSingleLineMultiElement.h
 * \brief  UiMultiElement that arranges its child elements in a single horizontal line.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiMultiElement.h"

class UiSummedSize;

/**
 * \brief UiMultiElement that arranges its child elements in a single horizontal line.
 * 
 * A UiSingleLineMultiElement arranges all of its child UiElements
 * in a single horizontal line, from left to right. It calculates
 * its size constraints based on the summed size constraints of
 * all its child elements, and manages their layout accordingly.
 */
class UiSingleLineMultiElement : public UiMultiElement
{
public:

	/**
	 * Construct a UiSingleLineMultiElement with the supplied name and parent section.
	 * 
	 * \param InName Name of this UiSingleLineMultiElement.
	 * \param InParent Parent section of this UiSingleLineMultiElement.
	 */
	UiSingleLineMultiElement(const std::string& InName, UiSection* InParent);

	/**
	 * Calculate the constrained size of this UiMultiElement,
	 * and calculate the constrained size of all child UiElements.
	 * 
	 * A UiSingleLineMultiElement calculates its size constraints to be
	 * the sum of the size constraints of all its child elements, since each
	 * element is displayed together on one line. It also allows non-fixed size
	 * elements to expand equally to fill any remaining space after accounting
	 * for fixed size elements
	 * 
	 * This will be the pushed item width for this element.
	 * 
	 * \param ParentConstrainedSize The constrained size of the parent UiElement.
	 * \param ParentSizeConstraints The size constraints of the parent UiElement.
	 */
	virtual void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	) override;

	/**
	 * Add a child UiElement to this UiSingleLineMultiElement. This will
	 * set the child element's same line property if needed.
	 * 
	 * \param NewElement Element to add to this UiSingleLineMultiElement.
	 */
	virtual void AddElement(const std::shared_ptr<UiElement> NewElement) override;

	/**
	 * Get the size constraints for this UiSingleLineMultiElement.
	 * This will be the summed size constraints of all its child elements.
	 * 
	 * \return The size constraints for this UiSingleLineMultiElement.
	 */
	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

private:

	/**
	 * Get all child UiElements that have a fixed size.
	 * 
	 * \return A vector of all child UiElements that have a fixed size.
	 */
	std::vector<std::shared_ptr<UiElement>> GetFixedSizeElements() const;

	/* The summed size constraints of all child elements. */
	std::shared_ptr<UiSummedSize> SizeConstraints;

};
