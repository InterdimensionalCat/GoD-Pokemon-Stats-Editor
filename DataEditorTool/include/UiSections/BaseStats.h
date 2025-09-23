#pragma once
#include "UiSection.h"

class BaseStatsInfo : public OldUiSection {
public:
	BaseStatsInfo(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	void UpdateStat(std::shared_ptr<int32_t> Stat, const std::string& StatName, const float MaxTextLength);

	virtual float CalculateMinNeededLineLength() const;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const override;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const override;

	void OnFontUpdated() override;

private:

	std::array<std::string, 6> BaseStatStrings = { "HP", "Attack", "Defense", "Sp. Atk", "Sp. Def", "Speed" };

	std::shared_ptr<int32_t> BaseHP = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> BaseAttack = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> BaseDefense = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> BaseSpecialAttack = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> BaseSpecialDefense = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> BaseSpeed = std::make_shared<int32_t>(-1);
};
