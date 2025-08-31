#include "include.h"
#include "CSV/CSVRow.h"

using namespace GoDCSV;

CSVRow::CSVRow(const json& InRowFields) : RowFields(InRowFields)
{

}

std::string CSVRow::GetName() const
{
	return GetStringAtColumn("Entry Name");
}

bool CSVRow::GetBoolAtColumn(const std::string& ColumnName) const
{
	std::string BoolStr = RowFields[ColumnName].get<std::string>();
	std::transform(BoolStr.begin(), BoolStr.end(), BoolStr.begin(), ::tolower);
	if (BoolStr == "true")
	{
		return true;
	}

	if (BoolStr == "false")
	{
		return false;
	}

	throw std::runtime_error("Value at key and index was not a bool");
	return false;
}

float CSVRow::GetFloatAtColumn(const std::string& ColumnName) const
{
	return std::stof(RowFields[ColumnName].get<std::string>());
}

int32_t CSVRow::GetIntAtColumn(const std::string& ColumnName) const
{
	return (int32_t)std::stoi(RowFields[ColumnName].get<std::string>());
}

std::string CSVRow::GetStringAtColumn(const std::string& ColumnName) const
{
	return RowFields[ColumnName].get<std::string>();
}

void CSVRow::SetBoolAtColumn(const std::string& ColumnName, const bool NewValue)
{
	if (NewValue)
	{
		RowFields[ColumnName] = "true";
	}
	else
	{
		RowFields[ColumnName] = "false";
	}
}

void CSVRow::SetFloatAtColumn(const std::string& ColumnName, const float NewValue)
{
	// We want to store whole float values with 1 trailing zero
	// (EG: 1 should be "1.0" but we don't want to lose precision
	// with more specific numbers (3.14 should be "3.14") so
	// we need 2 cases.
	if (std::fmod(NewValue, 1.0) == 0.0) {
		RowFields[ColumnName] = std::format("{:.1f}", NewValue);
	}
	else {
		RowFields[ColumnName] = std::format("{}", NewValue);
	}
}

void CSVRow::SetIntAtColumn(const std::string& ColumnName, const int32_t NewValue)
{
	RowFields[ColumnName] = std::format("{}", NewValue);
}

void CSVRow::SetStringAtColumn(const std::string& ColumnName, const std::string& NewValue)
{
	RowFields[ColumnName] = NewValue;
}

const json& GoDCSV::CSVRow::GetRowJson() const
{
	return RowFields;
}