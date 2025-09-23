#pragma once
#include "UI/UiElement.h"

/**
 * UiElement that shows a header and seperator after
 * some space, which is used to break up large sections
 * of UI elements into subsections.
 *
 * The number of ItemSpacing lengths to leave blank
 * before drawing the header is configurable.
 */
class SectionDivider : public UiElement
{

public:

	SectionDivider(const std::string& InName, UiSection* InParent);

	virtual void Tick() override;

	void SetNumSpaceLengths(const uint32_t NewNumSpaceLengths);

	/**
	 * Never include Section Dividers
	 * in the label size.
	 */
	virtual float GetLabelSize() override;

private:

	uint32_t NumSpaceLengths;

};