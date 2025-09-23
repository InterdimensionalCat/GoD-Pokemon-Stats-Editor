/*****************************************************************//**
 * \file   BasicUiElement.h
 * \brief  Subclass of UiElement that manages only 1 field from CSV data at a time
 * This field must always be from the same CSV file and column. The currently managed row 
 * of the data can be changed, but should usually match the currently selected entry 
 * of its UiSection/UiTab
 * 
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once
#include "UI/UiCSVElement.h"
#include "UI/TabCSVState.h"
#include "CSV/CSVDatabase.h"
#include "CSV/NewCSVData.h"
#include "CSV/CSVRow.h"

/** CSV data will only contain int32_ts, floats, std::strings, and bools */
template <typename CSVPrimitiveType>
concept PrimitiveTypeSupportedByCSV =
std::same_as<CSVPrimitiveType, bool> ||
std::same_as<CSVPrimitiveType, float> ||
std::same_as<CSVPrimitiveType, int32_t> ||
std::same_as<CSVPrimitiveType, std::string>;

template <PrimitiveTypeSupportedByCSV CSVPrimitiveType>
class BasicUiElement : public UiCSVElement
{
public:

	BasicUiElement(
		const std::string& InName, 
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName) :
		UiCSVElement(InName, InParent, InCSVFileName, InColumnName)
	{

	}

	BasicUiElement(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName) :
		BasicUiElement(InName, InParent, InCSVFileName, InName) 
	{

	}

	virtual void Refresh() override
	{
		UpdateManagedValueFromCSV();
	}

	/** Explicitly instantiated below. */
	void UpdateManagedValueFromCSV();

	/**
	 * Set the managed value to a new value and update the value of the
	 * CSV field this element currently manages.
	 */
	void SetManagedValue(const CSVPrimitiveType& NewValue)
	{
		// Don't bother updating the CSV file and marking it dirty
		// If we are just setting the same value
		if (NewValue != ManagedValue)
		{
			ManagedValue = NewValue;
			std::shared_ptr<GoDCSV::NewCSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile<GoDCSV::NewCSVData>(GetCSVFileName());

			/**
			 * TODO: once the command queue is up and running change this to
			 * pusing a modify value command instead.
			 */
			CSVData->SetField(GetColumnName(), GetCurrentRow(), NewValue);
			GetTabState()->RefreshTab();
		}
	}

	CSVPrimitiveType GetManagedValue() const
	{
		return ManagedValue;
	}

private:

	CSVPrimitiveType ManagedValue;
};

inline void BasicUiElement<bool>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::NewCSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile<GoDCSV::NewCSVData>(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetBoolAtColumn(GetColumnName());
}

inline void BasicUiElement<float>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::NewCSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile<GoDCSV::NewCSVData>(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetFloatAtColumn(GetColumnName());
}

inline void BasicUiElement<int32_t>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::NewCSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile<GoDCSV::NewCSVData>(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetIntAtColumn(GetColumnName());
}

inline void BasicUiElement<std::string>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::NewCSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile<GoDCSV::NewCSVData>(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetStringAtColumn(GetColumnName());
}