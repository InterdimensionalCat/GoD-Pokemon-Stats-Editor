/*****************************************************************//**
 * \file   BaseStatTotal.h
 * \brief  Ui element that displays the calculated base stat total.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"


class SimpleText;
class SimpleIntBox;

/**
 * \brief  Ui element that displays the calculated base stat total.
 * 
 * This is a single line multi element that contains a
 * SimpleText element for the stat name, and a SimpleIntBox
 * element for the total value.
 */
class BaseStatTotal : public UiSingleLineMultiElement
{

public:

	/**
	 * Construct a BaseStatTotal element with the supplied name and parent section.
	 * 
	 * \param InName Name of this BaseStatTotal element.
	 * \param InParent Parent section of this BaseStatTotal element.
	 */
	BaseStatTotal(
		const std::string& InName,
		UiSection* InParent
	);

	/**
	 * Update the displayed stat total to the supplied value.
	 * 
	 * \param NewStatTotal The new stat total to display.
	 */
	void UpdateStatTotal(int32_t NewStatTotal);

	/**
	 * Get the SimpleIntBox element that displays the base stat total.
	 * 
	 * \return The SimpleIntBox element that displays the base stat total.
	 */
	std::shared_ptr<SimpleIntBox> GetIntBox();

private:

	/** The SimpleText element that displays the stat name. */
	std::shared_ptr<SimpleText> StatNameText;

	/** The SimpleIntBox element that displays the total base stat value. */
	std::shared_ptr<SimpleIntBox> TotalIntBox;

};
