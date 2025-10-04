#pragma once

#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"


class SimpleText;
class SimpleIntBox;

class BaseStatTotal : public UiSingleLineMultiElement
{

public:

	BaseStatTotal(
		const std::string& InName,
		UiSection* InParent
	);

	void UpdateStatTotal(int32_t NewStatTotal);

	std::shared_ptr<SimpleIntBox> GetIntBox();

private:

	std::shared_ptr<SimpleText> StatNameText;

	std::shared_ptr<SimpleIntBox> TotalIntBox;

};
