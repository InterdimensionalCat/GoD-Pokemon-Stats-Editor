#pragma once
#include "UiSubsection.h"
//#include <vector>

class AbilityInfo : public UiSubsection {
public:
	AbilityInfo(UiSection* InParent, const std::string& InSubsectionName);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const;

private:

	std::vector<std::string> AbilitiesListItems;

	std::shared_ptr<std::string> CurrentAbility1 = std::make_shared<std::string>("---");
	std::shared_ptr<std::string> CurrentAbility2 = std::make_shared<std::string>("---");

	std::shared_ptr<std::string> CurrentAbility1Filter = std::make_shared<std::string>("");
	std::shared_ptr<std::string> CurrentAbility2Filter = std::make_shared<std::string>("");
};