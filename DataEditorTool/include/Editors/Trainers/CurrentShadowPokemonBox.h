/*****************************************************************//**
 * \file   CurrentShadowPokemonBox.h
 * \brief  
 *
 * \author Bennett Thomas
 * \date   December 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiCSVElement/StringElement/CSVIntHexComboBox.h"

/**
 * \brief  UiCSVElement
 */
class CurrentShadowPokemonBox : public CSVIntHexComboBox
{

public:

	CurrentShadowPokemonBox
	(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName
	);

protected:

	/**
	 * Reload the entries list from the specified CSV file and column.
	 */
	virtual void UpdateEntriesList() override;
};
