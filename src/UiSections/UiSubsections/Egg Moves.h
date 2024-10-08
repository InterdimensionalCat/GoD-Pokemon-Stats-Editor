#pragma once
#include "UiSubsection.h"
#include <vector>

class EggMovesInfo : public UiSubsection {
public:
	EggMovesInfo(UiSection* InParent, const std::string& InSubsectionName);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const;

private:

	std::vector<std::string> MoveItems;

	std::vector<std::shared_ptr<std::string>> EggMovesMove;

	std::vector<std::shared_ptr<std::string>> StringTypedWhileFocused;

	int32_t ItemsPerLine = 2;
};
