/*****************************************************************//**
 * \file   BaseStat.h
 * \brief  UiElement for displaying and editing a Pokemon's base stat.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"

class SimpleText;
class CSVIntBox;
class SimpleProgressBar;

/**
 * \brief  UiElement for displaying and editing a Pokemon's base stat.
 * 
 * This element displays the name of the stat, an integer input box
 * for editing the stat value, a text display of the valid range for
 * this stat, and a progress bar visualizing the stat value within
 * its valid range.
 * 
 * The progress bar will be filled proportionally to where the current
 * stat value falls within this range 0-255. Base stats can be increased
 * past 255 but the progress bar will be capped at 100%.
 */
class BaseStat : public UiSingleLineMultiElement
{

public:

	/**
	 * Construct a BaseStat element with the supplied stat name and CSV column name.
	 * 
	 * \param InStatName The name of the stat to display (e.g. "HP", "Attack", etc).
	 * \param InParent The parent UiSection for this element.
	 * \param InStatColumnName The name of the CSV column this stat corresponds to.
	 */
	BaseStat(
		const std::string& InStatName,
		UiSection* InParent,
		const std::string& InStatColumnName
	);

	/** Update the progress bar color and progress every tick. */
	void Tick() override;

	/** Update the progress bar color/progress based on the current value of the StatIntBox. */
	void UpdateProgressBarColorAndProgress();

	/** Update the valid stat range text based on the current value of the StatIntBox. */
	void UpdateStatRange();

	/**
	 * Get a formatted string representing the valid range for this stat.
	 * 
	 * \param StatLow The minimum valid value for this stat.
	 * \param StatHigh The maximum valid value for this stat.
	 * \return A formatted string of the form "({StatLow}-{StatHigh})".
	 */
	std::string GetFormattedStatRange(const int32_t StatLow, const int32_t StatHigh);

	/**
	 * Get the CSVIntBox used to edit this stat's value.
	 * 
	 * \return A shared pointer to the CSVIntBox used to edit this stat's value.
	 */
	std::shared_ptr<CSVIntBox> GetStatIntBox();

private:

	/** The name of the stat being represented by this element. */
	std::shared_ptr<SimpleText> StatNameText;

	/** The IntBox that edits this BaseStat. */
	std::shared_ptr<CSVIntBox> StatIntBox;

	/** The stat range (minium/maximum at level 100) for the current BaseStat. */
	std::shared_ptr<SimpleText> StatRangeText;

	/** The progress bar for the current BaseStat. */
	std::shared_ptr<SimpleProgressBar> StatProgressBar;
};
