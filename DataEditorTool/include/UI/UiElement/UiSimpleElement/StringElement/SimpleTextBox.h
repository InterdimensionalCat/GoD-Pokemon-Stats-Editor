/*****************************************************************//**
 * \file   SimpleTextBox.h
 * \brief  SingleUiElement that manages a TextBox component.
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiSingleElement.h"

class TextBox;

/**
 * \brief  SingleUiElement that manages a TextBox component.
 */
class SimpleTextBox : public UiSingleElement
{

public:

	SimpleTextBox
	(
		const std::string& InName,
		UiSection* InParent
	);

	virtual void UiComponentUpdated() override;

	void SetMinFromLongestString(const std::vector<std::string>& PossibleStrings);

	void SetTextBoxBuffer(const std::string& NewBufferValue);

	std::string GetTextBoxBuffer() const;

private:

	/* The TextBox component managed by this element. */
	std::shared_ptr<TextBox> TextBoxComponent;
};
