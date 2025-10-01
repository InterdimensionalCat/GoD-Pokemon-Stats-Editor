#pragma once

#include "UI/UiElement/UiElement.h"

class UiCSVElement;
class UiConstrainedSize;
class UiSize;

class UiMultiElement : public UiElement
{
public:

	UiMultiElement(const std::string& InName, UiSection* InParent);

	virtual void Tick() override;

	virtual void Refresh() override;

	virtual void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	);

	virtual void SetSameLine(const bool bInSameLine) override;

	virtual void SetDisabled(const bool bInDisabled) override;

	virtual void AddElement(const std::shared_ptr<UiElement> NewElement);

protected:

	std::vector<std::shared_ptr<UiElement>> UiElements;

};