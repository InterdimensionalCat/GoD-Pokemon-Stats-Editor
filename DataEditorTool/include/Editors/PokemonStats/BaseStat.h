#pragma once

#include "UI/MultiLineUiElement.h"

class SimpleText;
class CSVIntBox;
class CSVProgressBar;

class BaseStat : public MultiLineUiElement
{

public:

	BaseStat(
		const std::string& InStatName,
		UiSection* InParent,
		const std::string& InStatColumnName
	);

	void Tick() override;

	//void Refresh() override;

	void UpdateProgressBarColorAndProgress();

	void UpdateStatRange();

	std::string GetFormattedStatRange(const int32_t StatLow, const int32_t StatHigh);

	std::shared_ptr<CSVIntBox> GetStatIntBox();

private:

	std::shared_ptr<SimpleText> StatNameText;

	std::shared_ptr<CSVIntBox> StatIntBox;

	std::shared_ptr<SimpleText> StatRangeText;

	std::shared_ptr<CSVProgressBar> StatProgressBar;
};
