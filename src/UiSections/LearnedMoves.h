#pragma once
#include "UiSection.h"

class LearnedMovesInfo : public UiSection {
public:

	LearnedMovesInfo(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	virtual float CalculateMinNeededLineLength() const;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const override;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const override;

	void OnFontUpdated();

private:

	// Combination of:
	// Level up moves
	// Egg moves
};
