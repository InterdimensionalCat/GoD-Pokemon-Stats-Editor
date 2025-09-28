#include "include.h"
#include "UI/BasicUiElements/BasicUiElement.h"

template<>
void BasicUiElement<bool>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::NewCSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetBoolAtColumn(GetColumnName());
}
template<>
void BasicUiElement<float>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::NewCSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetFloatAtColumn(GetColumnName());
}

template<>
void BasicUiElement<int32_t>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::NewCSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetIntAtColumn(GetColumnName());
}

template<>
void BasicUiElement<std::string>::UpdateManagedValueFromCSV()
{
	std::shared_ptr<GoDCSV::NewCSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(GetCSVFileName());

	auto CurrentRowData = CSVData->GetRowAtIndex(GetCurrentRow());
	ManagedValue = CurrentRowData->GetStringAtColumn(GetColumnName());
}