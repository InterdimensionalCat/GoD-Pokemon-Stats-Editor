#pragma once

#include "UI/UiElement/UiElement.h"

class UiComponent;

class UiSingleElement : public UiElement
{

public:

	UiSingleElement(
		const std::string& InName,
		UiSection* InParent
	);

	virtual void Tick() override;

	virtual void UiComponentUpdated() = 0;

	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

	std::shared_ptr<const UiComponent> GetUiComponent() const;

	virtual void SetSameLine(const bool bInSameLine) override;

	virtual void SetSameLine(const float OffsetFromStart) override;

	virtual void SetDisabled(const bool bInDisabled) override;

	void SetIsFixedSize(const bool bInIsFixedSize);

protected:

	void SetUiComponent(std::shared_ptr<UiComponent> NewComponent);

	std::shared_ptr<UiComponent> Component;
};