#pragma once
#include "CSVData.h"

using json = nlohmann::json;

class PokemonMovesCSV : public CSVData
{
public:
	PokemonMovesCSV();

	std::vector<std::string> GetMovesList();

	bool Init() override;

private:
	std::vector<std::string> MovesList;
};
