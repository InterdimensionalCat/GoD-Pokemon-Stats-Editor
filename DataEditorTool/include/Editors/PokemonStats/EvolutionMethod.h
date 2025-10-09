/*****************************************************************//**
 * \file   EvolutionMethod.h
 * \brief  UiElement for selecting an evolution method from a dropdown.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiCSVElement/StringElement/CSVComboBox.h"

class EvolutionElement;

/**
 * \brief  UiElement for selecting an evolution method from a dropdown.
 * 
 * This is a CSVComboBox that is specifically designed to select
 * evolution methods for an EvolutionElement. When the selected
 * evolution method is changed, it will update the EvoluionCondition
 * in the parent EvolutionElement to an appropriate default
 * condition for the selected method.
 */
class EvolutionMethod : public CSVComboBox
{

public:

	/**
	 * Construct an EvolutionMethod element.
	 * 
	 * \param InName Name of this UiElement.
	 * \param InParent Parent UiSection of this UiElement.
	 * \param InParentElement The parent EvolutionElement for this EvolutionMethod.
	 * \param InCSVFileName The name of the CSV file to get the evolution methods from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to get the evolution methods from.
	 * \param InEntriesListCSVFileName The name of the CSV file to get the entries list from, without the ".csv" extension.
	 * \param InEntriesListColumnName The name of the column in the entries list CSV file to get the entries from.
	 */
	EvolutionMethod
	(
		const std::string& InName,
		UiSection* InParent,
		EvolutionElement* InParentElement,
		const std::string& InCSVFileName,
		const std::string& InColumnName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	/**
	 * Construct an EvolutionMethod element with the ColumnName set to the Element Name.
	 * 
	 * \param InName Name of this UiElement.
	 * \param InParent Parent UiSection of this UiElement.
	 * \param InParentElement The parent EvolutionElement for this EvolutionMethod.
	 * \param InCSVFileName The name of the CSV file to get the evolution methods from, without the ".csv" extension.
	 * \param InEntriesListCSVFileName The name of the CSV file to get the entries list from, without the ".csv" extension.
	 * \param InEntriesListColumnName The name of the column in the entries list CSV file to get the entries from.
	 */
	EvolutionMethod
	(
		const std::string& InName,
		UiSection* InParent,
		EvolutionElement* InParentElement,
		const std::string& InCSVFileName,
		const std::string& InEntriesListCSVFileName,
		const std::string& InEntriesListColumnName
	);

	/**
	 * Update the EvolutionCondition in the parent EvolutionElement
	 * to an appropriate default condition for the selected method
	 * if the selected method has changed.
	 */
	virtual void UiComponentUpdated() override;

private:

	/** The parent EvolutionElement for this EvolutionMethod */
	EvolutionElement* ParentElement;

};
