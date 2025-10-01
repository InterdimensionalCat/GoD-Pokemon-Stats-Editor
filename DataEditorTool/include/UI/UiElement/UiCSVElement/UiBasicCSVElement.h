#pragma once
#include "UI/UiElement/UiCSVElement/UiCSVElement.h"

#include "UI/TabCSVState.h"
#include "CSV/CSVDatabase.h"
#include "CSV/NewCSVData.h"
#include "CSV/CSVRow.h"

class UiComponent;

/** CSV data will only contain int32_ts, floats, std::strings, and bools */
template <typename CSVPrimitiveType>
concept PrimitiveTypeSupportedByCSV =
std::same_as<CSVPrimitiveType, bool> ||
std::same_as<CSVPrimitiveType, float> ||
std::same_as<CSVPrimitiveType, int32_t> ||
std::same_as<CSVPrimitiveType, std::string>;

template <PrimitiveTypeSupportedByCSV CSVPrimitiveType>
class UiBasicCSVElement : public UiCSVElement
{
public:

	UiBasicCSVElement(
		const std::string& InName, 
		UiSection* InParent,
		const std::string& InCSVFileName,
		const std::string& InColumnName) :
		UiCSVElement(InName, InParent, InCSVFileName, InColumnName)
	{

	}

	UiBasicCSVElement(
		const std::string& InName,
		UiSection* InParent,
		const std::string& InCSVFileName) :
		UiBasicCSVElement(InName, InParent, InCSVFileName, InName)
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
			std::shared_ptr<GoDCSV::NewCSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(GetCSVFileName());

			/**
			 * TODO: once the command queue is up and running change this to
			 * pushing a modify value command instead.
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