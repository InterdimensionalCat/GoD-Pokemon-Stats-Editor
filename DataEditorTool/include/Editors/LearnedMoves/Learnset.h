/*****************************************************************//**
 * \file   Learnset.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

class SimpleImageBox;
class CSVTextBox;

#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"

class Learnset : public UiSingleLineMultiElement
{

public:

	Learnset(
		const std::string& InName,
		UiSection* InParent,
		int32_t InCurrentRow
	);

	void Refresh() override;

private:

	/**
	 * Get all the columns in the Pokemon Stats CSV file that correspond to a taught move type (TM, HM, or TutorMove).
	 *
	 * \param MoveColumnPrefix The prefix of the move column type to search for (e.g. "TM", "HM", or "TutorMove").
	 * \return A vector of all column names that start with the specified prefix.
	 */
	std::vector<std::string> GetMoveColumns(const std::string& MoveColumnPrefix) const;

	std::shared_ptr<SimpleImageBox> PokefaceImage;

	std::shared_ptr<CSVTextBox> PokemonName;

	int32_t CurrentRow;
};
