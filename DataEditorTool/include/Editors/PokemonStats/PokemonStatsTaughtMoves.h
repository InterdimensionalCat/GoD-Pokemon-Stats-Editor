#pragma once

#include "UI/UiSection.h"

class PokemonStatsEditor;
class LevelUpMove;

class PokemonStatsTaughtMoves : public UiSection
{

public:

	PokemonStatsTaughtMoves(PokemonStatsEditor* InParent);

private:

	std::vector<std::string> GetMoveColumns(const std::string& MoveColumnPrefix) const;

};
