#pragma once
#include <memory>
#include <filesystem>
#include "csv.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class csv::CSVRow;

class CSVData
{
public:
	CSVData();

	virtual bool Init();

	virtual void ProcessRow(csv::CSVRow& row);

	std::vector<std::string> GetAllEntriesOfKey(const std::string& key, const bool bConvertFormat);

	std::string GetStringAtKeyAndIndex(uint32_t index, const std::string& key);

	int32_t GetIntAtKeyAndIndex(uint32_t index, const std::string& key);

	bool GetboolAtKeyAndIndex(uint32_t index, const std::string& key);

	int32_t CountQuoteOccurances(const std::string& PotentialQuoteString);

	std::vector<std::shared_ptr<json>> GetDataObject();

	std::vector<std::string> GetHeaderArray() const;

protected:

	std::vector<std::string> HeaderArray;

	std::vector<std::shared_ptr<json>> DataObject;

	std::filesystem::path Path;

	//std::shared_ptr<csv::CSVReader> ItemCSVReader;
	//csv::CSVFormat ItemCSVFormat;
};
