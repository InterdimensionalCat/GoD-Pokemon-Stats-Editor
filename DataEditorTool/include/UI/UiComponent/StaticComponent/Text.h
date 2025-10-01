#pragma once
#include "UI/UiComponent/UiComponent.h"

class Text : public UiComponent
{

public:

	Text
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	virtual void DisplayElement() override;

	void SetText(const std::string& NewText);

	virtual float GetLabelSize() override;

	virtual bool HasLabel() const override;

	virtual float CalculateInternalSpace() const override;

private:

	std::string TextToDisplay = "";
};