#pragma once
#include "UiSubsection.h"

class IdentificationInfo : public UiSubsection {
public:
	// Contains Name ID, species Name ID, 
	IdentificationInfo(UiSection* InParent, const std::string& InSubsectionName);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	// Min needed size of the largest label
	float CalculateLargestLabelLength() const override;

	// Min needed size for the largest line of elements
	float CalculateLargestElementLength() const override;

private:
	std::shared_ptr<std::string> CurrentNameID = std::make_shared<std::string>("---");
	std::shared_ptr<std::string> CurrentSpeciesNameID = std::make_shared<std::string>("---");
	std::string CurrentIndex = "---";
	int32_t CurrentRegionalDexID = -1;
	int32_t CurrentNationalDexID = -1;
};
