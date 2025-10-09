/*****************************************************************//**
 * \file   SimpleText.h
 * \brief  UiSingleElement that manages a Text component.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiElement/UiSingleElement.h"

class Text;

/**
 * \brief  UiSingleElement that manages a Text component.
 * 
 * This is a simple UI element that displays a static text string.
 * The text can be updated via SetText, but does not manage any
 * underlying data.
 */
class SimpleText : public UiSingleElement
{

public:

	/**
	 * Construct a SimpleText element with the supplied name and parent section.
	 * 
	 * \param InName Name of this SimpleText element.
	 * \param InParent Parent section of this SimpleText element.
	 */	
	SimpleText
	(
		const std::string& InName,
		UiSection* InParent
	);

	/**
	 * Function that is called whenever the UiComponent
	 * managed by this UiSingleElement is updated.
	 *
	 * Does nothing for a SimpleText element.
	 */
	virtual void UiComponentUpdated() override;

	/**
	 * Set the text of this SimpleText element to the supplied string.
	 * 
	 * \param NewText The new text to display.
	 */
	void SetText(const std::string& NewText);

private:

	/* The Text component managed by this SimpleText element. */
	std::shared_ptr<Text> TextComponent;

};
