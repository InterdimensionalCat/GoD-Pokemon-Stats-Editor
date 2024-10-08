#pragma once
#include "UiSubsection.h"
#include <vector>
#include <string>

class MiscInfo : public UiSubsection {
public:
	MiscInfo(UiSection* InParent, const std::string& InSubsectionName);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const;

private:
	std::shared_ptr<std::string> ExpRate = std::make_shared<std::string>("---");
	std::shared_ptr<int32_t> ExpYield = std::make_shared<int32_t>(-1);

	std::shared_ptr<std::string> GenderRatio = std::make_shared<std::string>("---");
	std::shared_ptr<int32_t> CatchRate = std::make_shared<int32_t>(-1);

	std::shared_ptr<int32_t> Height = std::make_shared<int32_t>(-1);
	std::shared_ptr<int32_t> Weight = std::make_shared<int32_t>(-1);

	std::shared_ptr<std::string> HappinessString = std::make_shared<std::string>("---");
	std::shared_ptr<int32_t> HappinessInt = std::make_shared<int32_t>(-1);

	std::vector<std::string> ExpRateList;
	std::vector<std::string> GenderRatioList;

	std::shared_ptr<std::string> ExpRateFilterString = std::make_shared<std::string>("");
	std::shared_ptr<std::string> GenderRatioFilterString = std::make_shared<std::string>("");
};
