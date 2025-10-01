#pragma once

#include "UI/UiElement/UiMultiElement/UiMultiElement.h"

class UiSummedSize;

class UiSingleLineMultiElement : public UiMultiElement
{
public:

	UiSingleLineMultiElement(const std::string& InName, UiSection* InParent);

	virtual void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	) override;

	virtual void AddElement(const std::shared_ptr<UiElement> NewElement) override;

	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

private:

	std::vector<std::shared_ptr<UiElement>> GetFixedSizeElements() const;

	std::shared_ptr<UiSummedSize> SizeConstraints;

};
