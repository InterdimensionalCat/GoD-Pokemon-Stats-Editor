#pragma once
#include "UiSubsection.h"

class EVYieldInfo : public UiSubsection {
public:
	EVYieldInfo(OldUiSection* InParent, const std::string& InSubsectionName);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const;

private:

	std::shared_ptr<int32_t> HPEVYield = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> AttackEVYield = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> DefenseEVYield = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> SpecialAttackEVYield = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> SpecialDefenseEVYield = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> SpeedEVYield = std::make_shared<int32_t>(-1);
};
