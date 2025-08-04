#pragma once
#include "UiSubsection.h"
//#include <vector>

class LevelUpMovesInfo : public UiSubsection {
public:
	LevelUpMovesInfo(UiSection* InParent, const std::string& InSubsectionName);

	void UpdateElement() override;

	void SwapMoves(const int32_t MoveOneIndex, const int32_t MoveTwoIndex);

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const;

	void OnFontUpdated() override;

private:

	std::vector<std::string> MoveItems;

	std::vector<std::shared_ptr<std::string>> LevelUpMovesMove;

	std::vector<std::shared_ptr<int32_t>> LevelUpMovesLevels;

	std::vector<std::shared_ptr<std::string>> StringTypedWhileFocused;

	float MaxMoveTextSize = -1.f;
};
