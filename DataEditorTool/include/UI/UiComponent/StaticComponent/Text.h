/*****************************************************************//**
 * \file   Text.h
 * \brief  UiComponent that displays static text.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiComponent/UiComponent.h"

/**
 * \brief  UiComponent that displays static text.
 */
class Text : public UiComponent
{

public:

	/**
	 * Construct a Text with the supplied name and parent element.
	 * This Text will have no label by default.
	 * 
	 * \param InName Name of this Text.
	 * \param InParent Parent UiSingleElement of this Text.
	 */
	Text
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	/**
	 * Display this Text using ImGui::Text.
	 */
	virtual void DisplayComponent() override;

	/**
	 * Set the text to display in this Text component.
	 * 
	 * \param NewText The new text to display.
	 */
	void SetText(const std::string& NewText);

	/**
	 * Calculate the internal space required by this Text,
	 * excluding label size.
	 * 
	 * \return The internal space required by this Text, excluding label size.
	 */
	virtual float CalculateInternalSpace() const override;

private:

	/* The text to display in this Text component. */
	std::string TextToDisplay = "";
};