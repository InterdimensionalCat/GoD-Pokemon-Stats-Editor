#pragma once

#include "UI/UiSection.h"

class PokemonStatsEditor;
class BaseStat;
class BaseStatTotal;

class PokemonStatsBaseStats : public UiSection
{

public:

	PokemonStatsBaseStats(PokemonStatsEditor* InParent);

	void Tick() override;

	void CalculateBaseStatTotal();

private:

	std::array<std::shared_ptr<BaseStat>, 6> BaseStatElements;

	std::shared_ptr<BaseStatTotal> CurrentBST;

};
