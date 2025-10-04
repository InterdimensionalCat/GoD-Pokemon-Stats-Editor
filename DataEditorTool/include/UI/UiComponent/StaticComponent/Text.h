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

	virtual void DisplayComponent() override;

	void SetText(const std::string& NewText);

	virtual float CalculateInternalSpace() const override;

private:

	std::string TextToDisplay = "";
};