/*****************************************************************//**
 * \file   CSVTextBox.h
 * \brief  UiBasicCSVElement that displays and edits a string value from a specified column in a CSV file
 * via a TextBox.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

class TextBox;

/**
 * \brief  UiBasicCSVElement that displays and edits a string value from a specified column in a CSV file
 * via a TextBox.
 */
class CSVTextBox : public UiBasicCSVElement<std::string>
{

public:

	/**
	 * Construct a CSVTextBox with the supplied name, parent section,
	 * CSV file name, and column name.
	 * 
	 * \param InName Name of this CSVTextBox.
	 * \param InParent Parent section of this CSVTextBox.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to display data from.
	 */
	CSVTextBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

	/**
	 * Construct a CSVTextBox with the supplied name, parent section,
	 * and CSV file name. The column name will be set to the same value as the name.
	 * 
	 * \param InName Name of this CSVTextBox.
	 * \param InParent Parent section of this CSVTextBox.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 */
	CSVTextBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName
	);

	/** 
	 * Refresh references to the underlying data this CSVTextBox manages.
	 * 
	 * For a CSVTextBox, this just refreshes the managed value to match the current
	 * value in the CSV file, and sets the text box buffer to match.
	 */
	virtual void Refresh() override;

	/**
	 * Called whenever the TextBox component is updated.
	 * 
	 * For a CSVTextBox, this sets the managed value to match the text box buffer.
	 */
	virtual void UiComponentUpdated() override;

	/**
	 * Set the minimum content size of the TextBox based on the length of the longest string
	 * in the provided list of possible strings.
	 * 
	 * This is useful for ensuring that the TextBox is wide enough to display any of the
	 * possible strings without clipping.
	 * 
	 * \param PossibleStrings A vector of strings to determine the longest string from.
	 */
	void SetMinFromLongestString(const std::vector<std::string>& PossibleStrings);

private:

	/* The TextBox component managed by this element. */
	std::shared_ptr<TextBox> TextBoxComponent;
};
