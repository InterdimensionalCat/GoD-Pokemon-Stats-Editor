/*****************************************************************//**
 * \file   TextBox.h
 * \brief  UiComponent that displays a text box for editing string values.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiComponent/UiComponent.h"

/**
 * \brief  UiComponent that displays a text box for editing string values.
 */
class TextBox : public UiComponent
{

public:

	/**
	 * Construct a TextBox with the supplied name and parent element.
	 * This TextBox will have a label by default.
	 * 
	 * \param InName Name of this TextBox.
	 * \param InParent Parent UiSingleElement of this TextBox.
	 */
	TextBox
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	/**
	 * Display this TextBox using ImGui::InputText.
	 */
	virtual void DisplayComponent() override;

	/**
	 * Calculate the internal space required by this TextBox,
	 * excluding label size.
	 * 
	 * \return The internal space required by this TextBox, excluding label size.
	 */
	virtual float CalculateInternalSpace() const override;

	/**
	 * Set the value of the internal string buffer used by this TextBox.
	 * 
	 * \param NewBufferValue The new value for the internal string buffer.
	 */
	void SetTextBoxBuffer(const std::string& NewBufferValue);

	/**
	 * Get the value of the internal string buffer used by this TextBox.
	 * 
	 * \return The value of the internal string buffer.
	 */
	std::string GetTextBoxBuffer() const;

protected:

	/* The string buffer used by this TextBox. */
	std::string TextBoxBuffer = "---";
};