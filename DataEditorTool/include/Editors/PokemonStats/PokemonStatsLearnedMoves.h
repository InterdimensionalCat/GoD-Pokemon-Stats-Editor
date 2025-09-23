#pragma once

#include "UI/UiSection.h"

class PokemonStatsEditor;
class LevelUpMove;

class PokemonStatsLearnedMoves : public UiSection
{

public:

	PokemonStatsLearnedMoves(PokemonStatsEditor* InParent);

	std::shared_ptr<LevelUpMove> GetLevelUpMoveAtIndex(const int32_t Index);

	const std::vector<std::shared_ptr<LevelUpMove>>& GetLevelUpMoves() const;

private:

	std::vector<std::shared_ptr<LevelUpMove>> LevelUpMoves;

};
