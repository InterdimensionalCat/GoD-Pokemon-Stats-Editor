/*****************************************************************//**
 * \file   SimpleSectionDivider.h
 * \brief  UiSingleElement that manages SectionDivider component
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiElement/UiSingleElement.h"

class SectionDivider;

/**
 * \brief UiSingleElement that contains a SectionDivider component
 * 
 * A SimpleSectionDivider is a UiSingleElement that contains
 * a SectionDivider component. This is used to create a visual
 * divider between sections of UI elements in a UiSection.
 */
class SimpleSectionDivider : public UiSingleElement
{

public:

	/**
	 * Construct a SimpleSectionDivider with the supplied name and parent section.
	 * 
	 * \param InName Name of this SimpleSectionDivider.
	 * \param InParent Parent section of this SimpleSectionDivider.
	 */
	SimpleSectionDivider(const std::string& InName, UiSection* InParent);

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * Does nothing for a SectionDivider.
	 */
	virtual void UiComponentUpdated() override;

	/**
	 * Set the number of space lengths in the SectionDivider component.
	 * 
	 * \param NewNumSpaceLengths The new number of space lengths in the SectionDivider component.
	 */
	void SetNumSpaceLengths(const uint32_t NewNumSpaceLengths);

private:

	/* Shared pointer to the SectionDivider component managed by this SimpleSectionDivider. */
	std::shared_ptr<SectionDivider> SectionDividerComponent;

};
