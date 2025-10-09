/*****************************************************************//**
 * \file   CheckBox.h
 * \brief  UiComponent that displays and edits a boolean value via a checkbox.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiComponent/UiComponent.h"

class UiElement;
class UiSize;

/**
 * \brief  UiComponent that displays and edits a boolean value via a checkbox.
 */
class CheckBox : public UiComponent
{

public:

	/**
	 * Construct a CheckBox with the supplied name and parent element.
	 * This CheckBox will have a label by default.
	 * 
	 * \param InName Name of this CheckBox.
	 * \param InParent Parent UiSingleElement of this CheckBox.
	 */
	CheckBox
	(
		const std::string& InName,
		UiSingleElement* InParent
	);

	/**
	 * Display this CheckBox using ImGui::CheckBox.
	 */
	virtual void DisplayComponent() override;

	/**
	 * Calculate the internal space required by this CheckBox,
	 * excluding label size.
	 * 
	 * \return The internal space required by this CheckBox, excluding label size.
	 */
	virtual float CalculateInternalSpace() const override;

	/**
	 * Set the value of the internal boolean buffer used by this CheckBox.
	 * 
	 * \param InBufferVal The new value for the internal boolean buffer.
	 */
	void SetBoolBuffer(const bool InBufferVal);

	/**
	 * Get the value of the internal boolean buffer used by this CheckBox.
	 * 
	 * \return The value of the internal boolean buffer.
	 */
	bool GetBoolBuffer() const;

private:

	/* Internal boolean buffer used by this CheckBox. */
	bool bBoolBuffer = false;
};
