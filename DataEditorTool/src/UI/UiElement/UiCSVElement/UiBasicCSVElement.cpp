#include "include.h"
#include "UI/UiElement/UiCSVElement/UiBasicCSVElement.h"

template<>
void UiBasicCSVElement<bool>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::CSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetBoolAtColumn(GetColumnName());
}
template<>
void UiBasicCSVElement<float>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::CSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetFloatAtColumn(GetColumnName());
}

template<>
void UiBasicCSVElement<int32_t>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::CSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetIntAtColumn(GetColumnName());
}

template<>
void UiBasicCSVElement<std::string>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::CSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetStringAtColumn(GetColumnName());
}