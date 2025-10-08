#include "include.h"
#include "Command/ModifySingleCSVValue.h"

#include "CSV/CSVDatabase.h"
#include "CSV/CSVData.h"
#include "CSV/CSVRow.h"

ModifySingleCSVValue::ModifySingleCSVValue(
	const std::string InCSVFileName,
	const std::string InCSVFileColumn,
	const int32_t InCSVFileRow,
	const CSVTypeVariant& InNewValue
) :
	CSVFileName(InCSVFileName),
	CSVFileColumn(InCSVFileColumn),
	CSVFileRow(InCSVFileRow),
	NewValue(InNewValue)
{
	// Get the previous value from the specified CSV
	// file/column/row.
	UpdatePrevValue();
}

void ModifySingleCSVValue::Execute()
{
	std::shared_ptr<GoDCSV::CSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(CSVFileName);
	CSVData->SetField(CSVFileColumn, CSVFileRow, NewValue);
}

void ModifySingleCSVValue::Undo()
{
	std::shared_ptr<GoDCSV::CSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(CSVFileName);
	CSVData->SetField(CSVFileColumn, CSVFileRow, PrevValue);
}

void ModifySingleCSVValue::Redo()
{
	Execute();
}

std::string ModifySingleCSVValue::GetName() const
{
	return std::format(
		"Modify {}.csv: ({}, {})",
		CSVFileName,
		CSVFileColumn,
		CSVFileRow
	);
}

std::string ModifySingleCSVValue::ToString() const
{
	return std::format(
		"{} -> {}",
		std::visit([](auto&& Arg) { return std::format("{}", Arg); }, PrevValue),
		std::visit([](auto&& Arg) { return std::format("{}", Arg); }, NewValue)
	);
}

void ModifySingleCSVValue::UpdatePrevValue()
{
	std::shared_ptr<GoDCSV::CSVData> CSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(CSVFileName);

	auto CurrentRowData = CSVData->GetRowAtIndex(CSVFileRow);
	if (std::holds_alternative<bool>(NewValue))
	{
		PrevValue = CurrentRowData->GetBoolAtColumn(CSVFileColumn);
		return;
	}
	else if (std::holds_alternative<float>(NewValue))
	{
		PrevValue = CurrentRowData->GetFloatAtColumn(CSVFileColumn);
		return;
	}
	else if (std::holds_alternative<int32_t>(NewValue))
	{
		PrevValue = CurrentRowData->GetIntAtColumn(CSVFileColumn);
		return;
	}
	else if (std::holds_alternative<std::string>(NewValue))
	{
		PrevValue = CurrentRowData->GetStringAtColumn(CSVFileColumn);
		return;
	}

	ICLogger::Warn("ModifySingleCSVValue command given an invalid or empty NewValue: {}",
		std::visit([](auto&& Arg) { return std::format("{}", Arg); }, NewValue));
}
