#include "include.h"
#include "CSV/CSVData.h"
#include "CSV/CSVLoader.h"
#include "CSV/CSVHeader.h"
#include "CSV/CSVRow.h"

using namespace GoDCSV;

CSVData::CSVData(const std::string& CSVFileName) : FileName(CSVFileName)
{

}

void CSVData::Init()
{
	try
	{
		// Try and load the CSV file, this will throw if loading fails.
		auto CSVHeaderAndRows = CSVLoader::TryLoadCSV(GetName());

		InitFromLoadedData(CSVHeaderAndRows);
	}
	catch (const std::exception& e)
	{
		HeaderRow.reset();
		DataRows.clear();
		throw e;
	}
}

void CSVData::InitFromLoadedData(std::pair<std::vector<std::string>, std::vector<json>> InLoadedData)
{
	// Set the header row based on the loaded data.
	HeaderRow = std::make_shared<CSVHeader>(InLoadedData.first);

	for (json& DataRowFields : InLoadedData.second)
	{
		DataRows.push_back(std::make_shared<CSVRow>(DataRowFields));
	}

	// If everything succeeded, set bLoaded to true.
	bLoaded = true;
}

std::string CSVData::Save()
{
	if (!bLoaded)
	{
		// Throw if we attempt to save an unloaded CSV file.
		throw std::runtime_error(std::format("Attempted to save unloaded CSV file {}.csv", GetName()));
	}

	if (bModified)
	{
		try
		{
			std::vector<json> DataRowJsons;
			DataRowJsons.reserve(DataRows.size());

			for (const auto& DataRow : DataRows)
			{
				DataRowJsons.push_back(DataRow->GetRowJson());
			}

			// Attempt to save CSV file. Will throw if CSV file saving fails.
			CSVLoader::TrySaveCSV(GetName(), { HeaderRow->GetColumnNamesArray(), DataRowJsons});

			// This CSV file is no longer marked as modified since we saved it.
			bModified = false;

			// File saving has succeeded.
			ICLogger::PushInfoNotification(
				std::format("{}.csv Saved Successfully", GetName()),
				6000,
				"CSV file {}.csv saved successfully",
				GetName()
			);
		}
		catch (const std::exception& e)
		{
			ICLogger::PushErrorNotification("CSV file saving failed", 6000, "Error saving CSV file {}.csv: {}", GetName(), e.what());
			return e.what();
		}
	}
	else
	{
		// Warn if we attempted to save an unmodified CSV file.
		ICLogger::Warn("Attempted to save unmodified CSV file {}.csv", GetName());
	}

	return "";
}

std::shared_ptr<const CSVRow> CSVData::GetRowAtIndex(const uint32_t RowIndex)
{
	if (!bLoaded)
	{
		ICLogger::Warn("{}.csv {} called on an unloaded CSV file, null row will be returned.", GetName(), "GetRowAtIndex");
		return nullptr;
	}

	return DataRows.at(RowIndex);
}

std::shared_ptr<const CSVRow> CSVData::GetRowByName(const std::string& RowName)
{
	if (!bLoaded)
	{
		ICLogger::Warn("{}.csv {} called on an unloaded CSV file, null row will be returned.", GetName(), "GetRowByName");
		return nullptr;
	}

	auto FoundIt = std::find_if(
		DataRows.begin(), 
		DataRows.end(), 
		[RowName](const std::shared_ptr<CSVRow> InRow) 
		{
			// For GoD CSV's, the first entry in each row is always "Entry Name"
			return InRow->GetStringAtColumn("Entry Name") == RowName;
		}
	);

	if (FoundIt == DataRows.end())
	{
		// Throw if the supplied RowName could not be found.
		throw std::out_of_range(std::format("Row name {} does not exist in {}.csv", RowName, GetName()));
	}

	return *FoundIt;
}

std::shared_ptr<const CSVHeader> GoDCSV::CSVData::GetHeaderRow() const
{
	return HeaderRow;
}

std::vector<bool> CSVData::GetBoolColumn(const std::string& ColumnName)
{
	if (!bLoaded)
	{
		ICLogger::Warn("{}.csv {} called on an unloaded CSV file, no results will be returned.", GetName(), "GetBoolColumn");
		return std::vector<bool>();
	}

	std::vector<bool> BoolsInColumn;
	BoolsInColumn.reserve(DataRows.size());
	for (const auto& Row : DataRows)
	{
		BoolsInColumn.push_back(Row->GetBoolAtColumn(ColumnName));
	}
	return BoolsInColumn;
}

std::vector<float> CSVData::GetFloatColumn(const std::string& ColumnName)
{
	if (!bLoaded)
	{
		ICLogger::Warn("{}.csv {} called on an unloaded CSV file, no results will be returned.", GetName(), "GetFloatColumn");
		return std::vector<float>();
	}

	std::vector<float> FloatsInColumn;
	FloatsInColumn.reserve(DataRows.size());
	for (const auto& Row : DataRows)
	{
		FloatsInColumn.push_back(Row->GetFloatAtColumn(ColumnName));
	}
	return FloatsInColumn;
}

std::vector<int32_t> CSVData::GetIntColumn(const std::string& ColumnName)
{
	if (!bLoaded)
	{
		ICLogger::Warn("{}.csv {} called on an unloaded CSV file, no results will be returned.", GetName(), "GetIntColumn");
		return std::vector<int32_t>();
	}

	std::vector<int32_t> IntsInColumn;
	IntsInColumn.reserve(DataRows.size());
	for (const auto& Row : DataRows)
	{
		IntsInColumn.push_back(Row->GetIntAtColumn(ColumnName));
	}
	return IntsInColumn;
}

std::vector<std::string> CSVData::GetStringColumn(const std::string& ColumnName)
{
	if (!bLoaded)
	{
		ICLogger::Warn("{}.csv {} called on an unloaded CSV file, no results will be returned.", GetName(), "GetStringColumn");
		return std::vector<std::string>();
	}

	std::vector<std::string> StringsInColumn;
	StringsInColumn.reserve(DataRows.size());
	for (const auto& Row : DataRows)
	{
		StringsInColumn.push_back(Row->GetStringAtColumn(ColumnName));
	}
	return StringsInColumn;
}

std::string CSVData::GetName() const
{
	return FileName;
}

void CSVData::SetField(
	const std::string& ColumnName, 
	const int32_t RowIndex, 
	const std::variant<bool, float, int32_t, std::string> NewValue
)
{
	if (!bLoaded)
	{
		ICLogger::Warn("{}.csv {} called on an unloaded CSV file, no operation will be performed.", GetName(), "SetField");
		return;
	}

	if (std::holds_alternative<bool>(NewValue))
	{
		// Bool field value passed in.
		DataRows.at(RowIndex)->SetBoolAtColumn(ColumnName, std::get<bool>(NewValue));
		bModified = true;
	}
	else if (std::holds_alternative<float>(NewValue))
	{
		// Float field value passed in.
		DataRows.at(RowIndex)->SetFloatAtColumn(ColumnName, std::get<float>(NewValue));
		bModified = true;
	}
	else if (std::holds_alternative<int32_t>(NewValue))
	{
		// Int field value passed in.
		DataRows.at(RowIndex)->SetIntAtColumn(ColumnName, std::get<int32_t>(NewValue));
		bModified = true;
	}
	else if (std::holds_alternative<std::string>(NewValue))
	{
		// String field value passed in.
		DataRows.at(RowIndex)->SetStringAtColumn(ColumnName, std::get<std::string>(NewValue));
		bModified = true;
	}
}

bool CSVData::HasCSVFileBeenModified() const
{
	return bModified;
}

bool GoDCSV::CSVData::DoesCSVFileExist() const
{
	fs::path CSVFilePath = CSVLoader::GetCSVFileDir();
	CSVFilePath /= FileName;
	CSVFilePath += +".csv";

	if (!fs::exists(CSVFilePath))
	{
		return false;
	}

	return true;
}

bool GoDCSV::CSVData::IsCSVFileLoaded() const
{
	return bLoaded;
}

//std::vector<std::string> CSVData::GetAllEntriesOfKey(const std::string& key, const bool bConvertFormat)
//{
//	std::vector<std::string> Entries;
//	for (std::shared_ptr<json> row : DataObject) {
//		std::string NextEntry = (*row)[key];
//
//		if (bConvertFormat) {
//			// convert from ["ENTRY"  - #] format to [ENTRY (#)] format
//
//			// remove all " occurances
//			NextEntry.erase(std::remove(NextEntry.begin(), NextEntry.end(), '\"'), NextEntry.end());
//			std::size_t DashPos = NextEntry.find_last_of("-");
//			if (DashPos == std::string::npos)
//			{
//				throw std::runtime_error("Data at Key does not require bConvertFormat.");
//			}
//
//			// Seperate into Text and number along the '-' character.
//			std::string EntryText = NextEntry.substr(0, DashPos - 2);
//			std::string EntryNumber = NextEntry.substr(DashPos + 2, NextEntry.length());
//
//			// Re-format as [ENTRY (#)]
//			std::string CorrectFormat = std::format("{} ({})", EntryText, EntryNumber);
//
//			Entries.push_back(CorrectFormat);
//		}
//		else
//		{
//			Entries.push_back(NextEntry);
//		}
//	}
//
//	return Entries;
//}

