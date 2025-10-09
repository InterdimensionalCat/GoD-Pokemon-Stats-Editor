/*****************************************************************//**
 * \file   UiComponent.h
 * \brief  UiObject that manages and displays a single ImGui UI element, such as a button or text box.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiObject.h"

class UiSingleElement;
class UiSize;

/**
 * \brief  UiObject that manages and displays a single ImGui UI element, 
 * such as a button or text box.
 */
class UiComponent : public UiObject
{
public:

	/**
	 * Construct a UiComponent with the supplied name, parent element,
	 * and whether or not this component has a label.
	 * 
	 * \param InName Name of this UiComponent.
	 * \param InParent Parent UiSingleElement of this UiComponent.
	 * \param InHasLabel Whether or not this UiComponent has a label.
	 */
	UiComponent(
		const std::string& InName,
		UiSingleElement* InParent,
		const bool InHasLabel
	);

	/**
	 * Construct a UiComponent with the supplied name and parent element.
	 * This UiComponent will have a label by default.
	 * 
	 * \param InName Name of this UiComponent.
	 * \param InParent Parent UiSingleElement of this UiComponent.
	 */
	UiComponent(
		const std::string& InName,
		UiSingleElement* InParent
	);

	/**
	 * Prepare this UiComponent for display by setting state such
	 * as disabled and same line, then call DisplayComponent() to
	 * render this element. Any Component specific display code
	 * should be overridden in DisplayComponent().
	 */
	void Tick();

	/**
	 * Display this UiComponent using whatever ImGui UI
	 * this UiComponent implements.
	 * 
	 * This should be overridden by subclasses to.
	 */
	virtual void DisplayComponent() = 0;

	/**
	 * Notify the parent UiSingleElement that this UiComponent
	 * has been updated.
	 */
	void ComponentUpdated();

	/**
	 * Set whether or not this element should be displayed
	 * on the same line as the previous element in the parent section.
	 * 
	 * \param IsSameLine True if this element should be displayed on the same line as the previous element.
	 */
	void SetSameLine(const bool IsSameLine);

	/**
	 * Set whether or not this element should be displayed
	 * on the same line as the previous element in the parent section,
	 * with an offset from the start of the line.
	 * 
	 * \param OffsetFromStart The offset from the start of the line to display this element at.
	 */
	void SetSameLine(const float OffsetFromStart);

	/**
	 * Set whether or not this element should be disabled (grayed out).
	 * 
	 * \param InIsDisabled True if this element should be disabled.
	 */
	void SetDisabled(const bool InIsDisabled);

	/**
	 * Set the minimum content size this UiComponent must be
	 * able to support.
	 * 
	 * \param NewMinString A string representing the minimum content size this UiComponent must be able to support.
	 */
	void SetMinContentSizeFromString(const std::string& NewMinString);

	/**
	 * Set the maximum content size this UiComponent must be
	 * able to support.
	 * 
	 * \param NewMaxString A string representing the maximum content size this UiComponent can be.
	 */
	void SetMaxContentSizeFromString(const std::string& NewMaxString);

	/**
	 * Set the minimum content size this UiComponent must be
	 * able to support, based on the length of a string.
	 * 
	 * \param NewMinStringLength The length of a string representing the minimum content size this UiComponent must be able to support.
	 */
	void SetMinContentSizeFromStringLength(const uint32_t NewMinStringLength);

	/**
	 * Set the maximum content size this UiComponent must be
	 * able to support, based on the length of a string.
	 * 
	 * \param NewMaxStringLength The length of a string representing the maximum content size this UiComponent can be.
	 */
	void SetMaxContentSizeFromStringLength(const uint32_t NewMaxStringLength);

	/**
	 * Get the size constraints for this UiComponent.
	 * 
	 * \return The size constraints for this UiComponent.
	 */
	std::shared_ptr<UiSize> GetSizeConstraints();

	/**
	 * Get the size constraints for this UiComponent.
	 * 
	 * \return The size constraints for this UiComponent.
	 */
	std::shared_ptr<const UiSize> GetSizeConstraints() const;

	/**
	 * Return whether or not this UiComponent should be
	 * displayed on the same line as the previous element
	 * in the parent section.
	 * 
	 * \return True if this UiComponent should be displayed on the same line as the previous element.
	 */
	bool IsSameLine() const;

	/**
	 * Should this UiComponent be disabled (grayed out)?
	 * 
	 * \return True if this UiComponent should be disabled.
	 */
	bool IsDisabled() const;

	/**
	 * Return whether or not this UiComponent has a label. UiComponents
	 * without a label will not factor in the label or InnerItemSpacing
	 * in size constraint calculations.
	 * 
	 * \return True if this UiComponent has a label.
	 */
	bool HasLabel() const;

	/**
	 * Calculate the internal space this UiComponent,
	 * not including the InnerItemSpacing between
	 * the label and the element itself.
	 * 
	 * \return The internal space this UiComponent requires.
	 */
	virtual float CalculateInternalSpace() const;

protected:

	/* Parent UiSingleElement of this UiComponent. */
	UiSingleElement* ParentElement;

	/** The size constraints of this UiComponent. */
	std::shared_ptr<UiSize> ComponentSize;


private:

	/* Does this UiComponent have a label? */
	bool bHasLabel = true;

	/* Should this UiComponent be displayed on the same line as the previous element? */
	bool bIsSameLine = false;

	/* If this UiComponent is set to be on the same line, the offset from the start of the line to display it at. */
	float SameLineOffsetFromStart = 0.f;

	/* Should this UiComponent be disabled (grayed out)? */
	bool bIsDisabled = false;

};