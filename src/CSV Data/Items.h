#pragma once
#include "CSV Data.h"

using json = nlohmann::json;

class PokemonItemsCSV : public CSVData
{
public:
	PokemonItemsCSV();

	std::vector<std::string> GetItemsList();

	bool Init() override;

private:
	std::vector<std::string> ItemsList;
};
