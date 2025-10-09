/*****************************************************************//**
 * \file   UiElement.h
 * \brief UiElement displayed inside a UiSection. Manages either a UiComponent or other UiElements
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
 *\brief UiElement displayed inside a UiSection. Manages either a UiComponent or other UiElements
 * 
 * Each UiElement should either inherit from UiSingleElement or UiMultiElement,
 * other than those 2 classes nothing should inherit from this.
 * 
 * This common class between the two is needed so that we can mix Single and Multi
 * UiElements inside a UiSection in an arbitrary order.
 */
class UiElement : public UiObject
{
public:

	/**
	 * Construct a UiElement with the supplied name and parent section.
	 * 
	 * \param InName Name of this UiElement.
	 * \param InParent Parent section of this UiElement.
	 */
	UiElement(const std::string& InName, UiSection* InParent);

	/**
	 * Tick any child UiElements and display any UiComponents.
	 */
	virtual void Tick() override = 0;

	/**
	 * Calculate the constrained size of this UiElement,
	 * and calculate the constrained size of  any child UiElements.
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
	 * Set whether or not this Element should override its parent's synced size.
	 * 
	 * \param bInShouldOverride True if this element should override its parent's synced size.
	 */
	void SetShouldOverrideSyncedSize(const bool bInShouldOverride);

	/**
	 * Get the size constraints for this UiElement. For single UiElements
	 * this will be the size constraints of its UiComponent, for
	 * UiMultiElements this will be a UiCompoundSize depending on the
	 * type of MultiElement.
	 * 
	 * \return The size constraints for this UiElement.
	 */
	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const = 0;

	/**
	 * Set whether or not this element should be displayed
	 * on the same line as the previous element in the parent section.
	 * 
	 * \param bInSameLine True if this element should be displayed on the same line as the previous element.
	 */
	virtual void SetSameLine(const bool bInSameLine) = 0;

	/**
	 * Set whether or not this element should be displayed
	 * on the same line as the previous element in the parent section,
	 * with an offset from the start of the line.
	 * 
	 * \param OffsetFromStart The offset from the start of the line to display this element at.
	 */
	virtual void SetSameLine(const float OffsetFromStart) = 0;

	/**
	 * Set whether or not this element should be disabled (grayed out).
	 * 
	 * \param bInDisabled True if this element should be disabled.
	 */
	virtual void SetDisabled(const bool bInDisabled) = 0;

	/**
	 * Should this element override its parent's synced size?
	 * 
	 * \return True if this element should override its parent's synced size.
	 */
	bool ShouldOverrideSyncedSize() const;

protected:

	/* Parent section of this UiElement. */
	UiSection* ParentSection;

	/* The constrained size of this UiElement, used for PushItemWidth. */
	std::shared_ptr<UiConstrainedSize> ConstrainedSize;

private:

	/* Should this element override its parent's synced size? */
	bool bShouldOverrideSyncedSize = false;

};
