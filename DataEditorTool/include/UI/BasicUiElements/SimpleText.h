#pragma once
#include "UI/UiElement.h"

class SimpleText : public UiElement
{

public:

	SimpleText
	(
		const std::string& InName,
		UiSection* InParent
	);

	virtual void Tick() override;

	void SetText(const std::string& NewText);

	virtual float GetLabelSize() override;

private:

	std::string TextToDisplay = "";

};
