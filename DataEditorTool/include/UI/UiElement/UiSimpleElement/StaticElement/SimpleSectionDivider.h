#pragma once
#include "UI/UiElement/UiSingleElement.h"

class SectionDivider;

class SimpleSectionDivider : public UiSingleElement
{

public:

	SimpleSectionDivider(const std::string& InName, UiSection* InParent);

	virtual void UiComponentUpdated() override;

	void SetNumSpaceLengths(const uint32_t NewNumSpaceLengths);

private:

	std::shared_ptr<SectionDivider> SectionDividerComponent;

};
