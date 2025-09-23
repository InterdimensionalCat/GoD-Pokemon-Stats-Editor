#pragma once
#include "UI/MultiUiElement.h"

class UiCSVElement;

class MultiLineUiElement : public MultiUiElement
{
public:

	MultiLineUiElement(const std::string& InName, UiSection* InParent);

	virtual void PushConstrainedSizeForElement(const uint32_t ElementIndex) override;

	virtual void PopConstrainedSizeForElement(const uint32_t ElementIndex) override;

	virtual void AddCSVElement(const std::shared_ptr<UiCSVElement> NewElement) override;
	virtual void AddElement(const std::shared_ptr<UiElement> NewElement) override;

private:

	virtual float CalculateSpaceBetweenElements() const;

	int32_t GetNumFixedSizeElements() const;

};
