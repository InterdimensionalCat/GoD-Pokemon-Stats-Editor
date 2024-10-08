#pragma once
#include "CSV Data.h"

#include <map>

class csv::CSVRow;

using json = nlohmann::json;

class PokemonStatsCSV : public CSVData
{
public:
	PokemonStatsCSV();

	std::vector<std::string> GetPokemonList();

	bool CanPokemonLearn(uint32_t index, const std::string& key);

	bool Init() override;

	void SaveCSV();

private:
	std::vector<std::string> PokemonList;
};
