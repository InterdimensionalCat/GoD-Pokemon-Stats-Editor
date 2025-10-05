#include "include.h"
#include "Editors/PokemonStats/BaseStat.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleProgressBar.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntBox.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleText.h"

BaseStat::BaseStat(
	const std::string& InStatName,
	UiSection* InParent,
	const std::string& InStatColumnName
) :
	UiSingleLineMultiElement(std::format("{}-MultiLine", InStatName), InParent)
{
	const std::string CSVName = "Pokemon Stats";

	// Show simple text on the left as a label
	StatNameText = std::make_shared<SimpleText>(InStatName, InParent);

	// Show an IntBox that modifies the base stat.
	auto StatIntBoxName = std::format("##{}-IntBox", InStatName);
	StatIntBox = std::make_shared<CSVIntBox>(StatIntBoxName, InParent, CSVName, InStatColumnName, 1, 5);

	StatIntBox->SetElementMinSize(3);
	StatIntBox->SetIsFixedSize(true);

	StatIntBox->SetBounds(0, 999);

	// Show a Progress Bar which displays the value of the base stat.
	auto StatProgressBarName = std::format("##{}-ProgressBar", InStatName);
	StatProgressBar = std::make_shared<SimpleProgressBar>(StatProgressBarName, InParent);
	StatProgressBar->SetBarMinSize(128.f);

	// Show the range of possible values a Pokemon's stat
	// can be with the current base stat
	StatRangeText = std::make_shared<SimpleText>(GetFormattedStatRange(999, 999), InParent);

	AddElement(StatNameText);
	AddElement(StatIntBox);
	AddElement(StatProgressBar);
	AddElement(StatRangeText);
}

void BaseStat::Tick()
{
	// TODO: Most of this can probably go in refresh rather than tick.

	// Update the stat progress bar's color and progress
	UpdateProgressBarColorAndProgress();

	// Update the min/max stat range to the right of the progress bar
	UpdateStatRange();

	UiSingleLineMultiElement::Tick();
}

void BaseStat::UpdateProgressBarColorAndProgress()
{
	// Get the base stat value from the IntBox,
	// we use the buffer value instead of the managed value
	// because the managed value will only update when we
	// commit a new value.
	int32_t BaseStatInt = StatIntBox->GetIntBuffer();

	// If base stat is less than half the progress bar max (255/2 = 127.5),
	// this is equal to the percent of the way to 127.5
	// Otherwise it is equal to 1 (or 100%)
	float FirstHalfProgress = static_cast<float>(BaseStatInt) / 127.5f;

	// Ensure that FirstHalfProgress does not exceed percent ranges
	FirstHalfProgress = std::clamp(FirstHalfProgress, 0.f, 1.f);

	// If base stat is less than half the progress bar max, this is 0,
	// otherwise its the percent of the way from half to full the stat
	// is (so 127.5 is 0, 255 is 1)
	float SecondHalfProgress = 0.f;

	if (FirstHalfProgress >= 1.f)
	{
		// Calculate the percent above half we are for SecondHalfProgress
		SecondHalfProgress = (static_cast<float>(BaseStatInt) - 127.5f) / 127.5f;

		// Ensure that SecondHalfProgress does not exceed percent ranges
		SecondHalfProgress = std::clamp(SecondHalfProgress, 0.f, 1.f);
	}

	// We want the progress bar movement to be more pronounce for the
	// lower half of displayable values (0 - 127.5), so we weight
	// each half's progress differently in color/percentage calculations.
	// the first half gets a 2/3 weight, meaning a value of exactly half (127.5)
	// will show the progress bar as 2/3 completed. The second half's progress
	// gets weighted to 1/3 to ensure that the max is still 255
	const float WeightedFirstHalfProgress = FirstHalfProgress * (2.f / 3.f);
	const float WeightedSecondHalfProgress = SecondHalfProgress * (1.f / 3.f);

	// The total progress is just the sum of both weighted progresses, clamped
	// to ensure it remains a valid percent
	const float TotalProgress = std::clamp(
		WeightedFirstHalfProgress + WeightedSecondHalfProgress, 0.f, 1.f);

	// Set the progress bar's progress to the Total Progress.
	StatProgressBar->SetCurrentProgress(TotalProgress);

	// Calculate the color this progress bar should be at this percentage

	// The red color starts at 100%, then goes down to 0.2 over time
	// After we hit the halfway mark the reduction in red slows
	float RedColor = 1.f - TotalProgress;
	RedColor = std::max(0.2f, RedColor);
	RedColor += WeightedSecondHalfProgress;
	RedColor = std::clamp(RedColor, 0.2f, 1.0f);

	// The green color starts at 0.2, then goes up to 100 as we hit halfway,
	// then goes back down to 0, the rate of green reduction is reduced after
	// the halfway point
	float GreenColor = 1.f - abs(2.f * (TotalProgress - 0.5));
	GreenColor = std::max(0.2f, GreenColor);
	GreenColor += WeightedSecondHalfProgress;
	GreenColor = std::clamp(GreenColor, 0.2f, 1.0f);

	// The blue color is 0 for the entire first half, then scales up linearly, but
	// at a faster rate in the second half, maxing at 0.9 instead of 1.0

	float BlueColor = WeightedSecondHalfProgress * 3.f;
	BlueColor = std::clamp(BlueColor, 0.f, 0.9f);

	StatProgressBar->SetProgressBarColor(ImVec4(RedColor, GreenColor, BlueColor, 1.f));

	//StatProgressBar->SetCurrentProgress(static_cast<float>(StatIntBox->GetManagedValue()) / 255.f);

	//StatProgressBar->SetCurrentProgress(static_cast<float>(StatIntBox->GetManagedValue()) / 255.f);
}

void BaseStat::UpdateStatRange()
{
	int32_t StatLow = 0;
	int32_t StatHigh = 0;

	int32_t StatNumber = StatIntBox->GetManagedValue();

	// Base HP is calculated differently than all the other stats,
	// so it needs to be special cased
	if (StatIntBox->GetColumnName() == "Base Stats HP")
	{
		// A pokemon's HP stat at level 100 with no modifiers is
		// 2 times its base stat + 110, this is the lowest the
		// stat can be
		StatLow = std::floor((StatNumber * 2) + 110);

		// Natures can never affect HP, so only EVs and IVs
		// can increase HP. IVs can increase it by up to 31,
		// and EVs can increase it by up to 63 (252/4)
		StatHigh = std::floor(StatLow + 31 + 63);

		// Special case for Shedinja, who has a base stat of 1,
		// A base stat of 1 does not compute to an actual base
		// stat of 1, but Shedinja is hard coded to always have
		// 1 hp
		if (StatNumber == 1)
		{
			StatLow = 1;
			StatHigh = 1;
		}

	}
	else
	{
		// A Pokemon's other stats at level 100 with no modifiers all 
		// follow the same pattern: 2 times its base stat + 5,
		// however, this is not the lowest the stat can be because
		// of natures, natures can increase/decrease a stat by 10%,
		// so the min value is the base stat value * 0.9
		const float StatBaseValue = static_cast<float>((StatNumber * 2) + 5);

		StatLow = static_cast<int32_t>(std::floor(StatBaseValue * 0.9f));

		// The max stat gets the 31 boost from IVs and the 63 boost from EVs,
		// but also can get a 10% boost from nature, this multiplier affects
		// the boost from IVs and EVs as well.
		StatHigh = static_cast<int32_t>(std::floor((StatBaseValue + 31.f + 63.f) * 1.1f));
	}

	// A stat of 0 only occurs for invalid/unfinished entries, 
	// but a stat of zero will result in nonzero stat ranges,
	// so we special case it to avoid confusion.
	if (StatNumber == 0)
	{
		StatLow = 0;
		StatHigh = 0;
	}

	// Clamp the min/max to ensure they don't exceed 999 for display purposes,
	// a stat of >1000 is possible in game, but no pokemon has base stats high
	// enough for it without boosts
	StatLow = std::clamp(StatLow, 0, 999);
	StatHigh = std::clamp(StatHigh, 0, 999);

	StatRangeText->SetText(GetFormattedStatRange(StatLow, StatHigh));
}

std::string BaseStat::GetFormattedStatRange(const int32_t StatLow, const int32_t StatHigh)
{
	return std::format("( {:3d} - {:<3d} )", StatLow, StatHigh);
}

std::shared_ptr<CSVIntBox> BaseStat::GetStatIntBox()
{
	return StatIntBox;
}