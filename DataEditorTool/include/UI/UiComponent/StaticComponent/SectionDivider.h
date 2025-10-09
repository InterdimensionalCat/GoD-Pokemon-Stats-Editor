/*****************************************************************//**
 * \file   SectionDivider.h
 * \brief  UiComponent that shows a header and separator to break up large sections of UI elements into subsections.
 * 
 * \author bthomas
 * \date   October 2025
 *********************************************************************/
#pragma once
#include "UI/UiComponent/UiComponent.h"

/**
 * \brief  UiComponent that shows a header and separator after
 * some space, which is used to break up large sections
 * of UI elements into subsections.
 *
 * The number of ItemSpacing lengths to leave blank
 * before drawing the header is configurable.
 */
class SectionDivider : public UiComponent
{

public:
	
	/**
	 * Construct a SectionDivider with the supplied name and parent element.
	 * This SectionDivider will no label by default.
	 * 
	 * \param InName Name of this SectionDivider.
	 * \param InParent Parent UiSingleElement of this SectionDivider.
	 */
	SectionDivider(const std::string& InName, UiSingleElement* InParent);

	/**
	 * Display this SectionDivider using ImGui::SeparatorText.
	 * 
	 * This will display some space, then the name of this SectionDivider
	 * as a header, then a separator line.
	 */
	virtual void DisplayComponent() override;

	/**
	 * Set the number of ItemSpacing lengths to leave blank
	 * before drawing the header.
	 * 
	 * \param NewNumSpaceLengths The new number of ItemSpacing lengths to leave blank.
	 */
	void SetNumSpaceLengths(const uint32_t NewNumSpaceLengths);

	/**
	 * Calculate the internal space required by this SectionDivider,
	 * excluding label size.
	 * 
	 * \return The internal space required by this SectionDivider, excluding label size.
	 */
	virtual float CalculateInternalSpace() const override;

private:

	/* The number of ItemSpacing lengths to leave blank before drawing the header. */
	uint32_t NumSpaceLengths;
};