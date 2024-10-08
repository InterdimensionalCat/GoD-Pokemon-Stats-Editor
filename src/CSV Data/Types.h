#pragma once
#include "CSV Data.h"

using json = nlohmann::json;

class PokemonTypesCSV : public CSVData
{
public:
	PokemonTypesCSV();

	std::vector<std::string> GetTypesList();

	bool Init() override;

private:
	std::vector<std::string> TypesList;
};
