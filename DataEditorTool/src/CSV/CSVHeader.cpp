#include "include.h"
#include "CSV/CSVHeader.h"

using namespace GoDCSV;

CSVHeader::CSVHeader(const std::vector<std::string>& InColumnNames) : ColumnNames(InColumnNames)
{

}

std::string CSVHeader::GetColumnName(const int32_t ColumnIndex) const
{
	return ColumnNames.at(ColumnIndex);
}

int32_t CSVHeader::GetIndexOfColumn(const std::string& ColumnName) const
{
	const auto It = std::find(
		ColumnNames.begin(),
		ColumnNames.end(),
		ColumnName
	);

	// Element not found
	if (It == ColumnNames.end())
	{
		ICLogger::Warn("Column name {} not found in CSVHeader", ColumnName);
		return -1;
	}
	else
	{
		return std::distance(ColumnNames.begin(), It);
	}
}

const std::vector<std::string>& GoDCSV::CSVHeader::GetColumnNamesArray() const
{
	return ColumnNames;
}