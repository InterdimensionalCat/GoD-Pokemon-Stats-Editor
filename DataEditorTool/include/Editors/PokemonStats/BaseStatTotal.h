#pragma once

#include "UI/MultiLineUiElement.h"

class SimpleText;
class IntBox;

class BaseStatTotal : public MultiLineUiElement
{

public:

	BaseStatTotal(
		const std::string& InName,
		UiSection* InParent
	);

	void UpdateStatTotal(int32_t NewStatTotal);

	std::shared_ptr<IntBox> GetIntBox();

private:

	std::shared_ptr<SimpleText> StatNameText;

	std::shared_ptr<IntBox> TotalIntBox;

};
