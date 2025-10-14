/*****************************************************************//**
 * \file   RadioButton.h
 * \brief  UiComponent that displays and edits a boolean value via a radio button.
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once
#include "UI/UiComponent/UiComponent.h"

class UiElement;
class UiSize;

/**
 * \brief  UiComponent that displays and edits a boolean value via a radio button.
 */
class RadioButton : public UiComponent
{

public:

	/**
	 * Construct a RadioButton with the supplied name and parent element.
	 * This RadioButton will have a label by default.
	 *
	 * \param InName Name of this RadioButton.
	 * \param InParent Parent UiSingleElement of this RadioButton.
	 */
	RadioButton
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	/**
	 * Display this RadioButton using ImGui::RadioButton.
	 */
	virtual void DisplayComponent() override;

	/**
	 * Calculate the internal space required by this RadioButton,
	 * excluding label size.
	 *
	 * \return The internal space required by this RadioButton, excluding label size.
	 */
	virtual float CalculateInternalSpace() const override;

	/**
	 * Set the value of the internal boolean buffer used by this RadioButton.
	 *
	 * \param InBufferVal The new value for the internal boolean buffer.
	 */
	void SetBoolBuffer(const bool InBufferVal);

	/**
	 * Get the value of the internal boolean buffer used by this RadioButton.
	 *
	 * \return The value of the internal boolean buffer.
	 */
	bool GetBoolBuffer() const;

private:

	/* Internal boolean buffer used by this RadioButton. */
	bool bBoolBuffer = false;
};
