/*****************************************************************//**
 * \file   UiBasicCSVElement.h
 * \brief  UiCSVElement that displays and edits a single primitive value from a specified column in a CSV file.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once
#include "UI/UiElement/UiCSVElement/UiCSVElement.h"

#include "UI/TabCSVState.h"
#include "CSV/CSVDatabase.h"
#include "CSV/CSVData.h"
#include "CSV/CSVRow.h"
#include "Command/ModifySingleCSVValue.h"

class UiComponent;

/** \brief   CSV data will only contain ints, floats, std::strings, and bools */
template <typename CSVPrimitiveType>
concept PrimitiveTypeSupportedByCSV =
std::same_as<CSVPrimitiveType, bool> ||
std::same_as<CSVPrimitiveType, float> ||
std::same_as<CSVPrimitiveType, int32_t> ||
std::same_as<CSVPrimitiveType, std::string>;

template <PrimitiveTypeSupportedByCSV CSVPrimitiveType>
/**
 * \brief  UiCSVElement that displays and edits a single primitive value from a specified column in a CSV file.
 * 
 * Contains a ManagedValue of the specified primitive type
 * that serves as a buffer between the UI component and the CSV file.
 * When this managed value is updated, the corresponding value in the CSV file
 * is updated via a ModifySingleCSVValue command pushed to the tab's command queue.
 */
class UiBasicCSVElement : public UiCSVElement
{
public:

	/**
	 * Construct a UiBasicCSVElement with the supplied name, parent section,
	 * CSV file name, and column name.
	 *
	 * \param InName Name of this UiBasicCSVElement.
	 * \param InParent Parent section of this UiBasicCSVElement.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 * \param InColumnName The name of the column in the CSV file to display data from.
	 */
	UiBasicCSVElement(
		const std::string& InName, 
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName) :
		UiCSVElement(InName, InParent, InCSVFileName, InColumnName)
	{

	}

	/**
	 * Construct a UiBasicCSVElement with the supplied name, parent section,
	 * and CSV file name. The column name will be set to the same value as the name.
	 *
	 * \param InName Name of this UiBasicCSVElement.
	 * \param InParent Parent section of this UiBasicCSVElement.
	 * \param InCSVFileName The name of the CSV file to display data from, without the ".csv" extension.
	 */
	UiBasicCSVElement(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName) :
		UiBasicCSVElement(InName, InParent, InCSVFileName, InName)
	{

	}

	/**
	 * Refresh references to the underlying data this UiObject manages.
	 * 
	 * For a UiCSVElement, this refresh the ManagedValue to match the current
	 * value in the CSV file. This will allow the element to stay up to date if
	 * other UiElements modify the same CSV field.
	 */
	virtual void Refresh() override
	{
		UpdateManagedValueFromCSV();
	}

	/**
	 * Update the managed value to match the current value of this
	 * field in the CSV file.
	 * 
	 * This is explicitly instantiated in the .cpp file for
	 * each valid CSVPrimitiveType.
	 */
	void UpdateManagedValueFromCSV();

	/**
	 * Set the managed value to a new value and update the value of the
	 * CSV field this element currently manages via a ModifySingleCSVValue command.
	 * 
	 * \param NewValue The new value to set the managed value to.
	 */
	void SetManagedValue(const CSVPrimitiveType& NewValue)
	{
		if constexpr(std::same_as<CSVPrimitiveType, std::string>)
		{
			auto NewValueStr = NewValue;
			auto ManagedValueStr = ManagedValue;

			if (NewValueStr.length() == ManagedValueStr.length())
			{
				for (size_t i = 0; i < NewValueStr.length(); ++i)
				{
					if (NewValueStr[i] != ManagedValueStr[i])
					{
						ICLogger::Info("CSV string value change detected at index {}: '{}' -> '{}'", i, ManagedValueStr[i], NewValueStr[i]);
					}
				}
			}
		}

		// Don't bother updating the CSV file and marking it dirty
		// If we are just setting the same value
		if (NewValue != ManagedValue)
		{
			ManagedValue = NewValue;
			GetTabState()->PushCommand(std::make_shared<ModifySingleCSVValue>(
				GetCSVFileName(),
				GetColumnName(),
				GetCurrentRow(),
				NewValue
			));

			GetTabState()->SetShouldRefresh();
		}
	}

	/**
	 * Get the value this UiBasicCSVElement manages.
	 * 
	 * \return The value this UiBasicCSVElement manages.
	 */
	CSVPrimitiveType GetManagedValue() const
	{
		return ManagedValue;
	}

private:

	/* The primitive value this UiBasicCSVElement manages. */
	CSVPrimitiveType ManagedValue;
};