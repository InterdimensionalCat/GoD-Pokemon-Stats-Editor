#pragma once
#include "CSV Data.h"

using json = nlohmann::json;

class PokemonAbilitiesCSV : public CSVData
{
public:
	PokemonAbilitiesCSV();

	std::vector<std::string> GetAbilitiesList();

	bool Init() override;

private:
	std::vector<std::string> AbilitiesList;
};
