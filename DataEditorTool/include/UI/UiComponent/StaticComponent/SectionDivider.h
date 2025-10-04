#pragma once
#include "UI/UiComponent/UiComponent.h"

/**
 * UiComponent that shows a header and separator after
 * some space, which is used to break up large sections
 * of UI elements into subsections.
 *
 * The number of ItemSpacing lengths to leave blank
 * before drawing the header is configurable.
 */
class SectionDivider : public UiComponent
{

public:

	SectionDivider(const std::string& InName, UiSingleElement* InParent);

	virtual void DisplayComponent() override;

	void SetNumSpaceLengths(const uint32_t NewNumSpaceLengths);

	virtual float CalculateInternalSpace() const override;

private:

	uint32_t NumSpaceLengths;

};