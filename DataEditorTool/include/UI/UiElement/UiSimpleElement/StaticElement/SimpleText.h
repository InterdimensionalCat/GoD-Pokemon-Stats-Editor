#pragma once
#include "UI/UiElement/UiSingleElement.h"

class Text;

class SimpleText : public UiSingleElement
{

public:

	SimpleText
	(
		const std::string& InName,
		UiSection* InParent
	);

	virtual void UiComponentUpdated() override;

	void SetText(const std::string& NewText);

private:

	std::shared_ptr<Text> TextComponent;

};
