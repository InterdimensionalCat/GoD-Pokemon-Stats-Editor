/*****************************************************************//**
 * \file   MultiLineTextBox.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

#include  "UI/UiComponent/StringComponent/TextBox.h"

class MultiLineTextBox : public TextBox
{

public:

	/**
	 * Construct a MultiLineTextBox with the supplied name and parent element.
	 * This MultiLineTextBox will have a label by default.
	 *
	 * \param InName Name of this MultiLineTextBox.
	 * \param InParent Parent UiSingleElement of this MultiLineTextBox.
	 */
	MultiLineTextBox
	(
		const std::string& InName,
		UiSingleElement* InParent
	);
	/**
	 * Display this MultiLineTextBox using ImGui::InputTextMultiline.
	 */
	virtual void DisplayComponent() override;
};
