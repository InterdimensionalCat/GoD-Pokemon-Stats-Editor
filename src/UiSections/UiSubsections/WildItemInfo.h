#pragma once
#include "UiSubsection.h"
#include <vector>

class WildItemInfo : public UiSubsection {
public:
	WildItemInfo(UiSection* InParent, const std::string& InSubsectionName);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const;

private:

	std::vector<std::string> WildItemsListItems;

	std::shared_ptr<std::string> CurrentWildItem1 = std::make_shared<std::string>("---");
	std::shared_ptr<std::string> CurrentWildItem2 = std::make_shared<std::string>("---");

	std::shared_ptr<std::string> CurrentWildItem1Filter = std::make_shared<std::string>("");
	std::shared_ptr<std::string> CurrentWildItem2Filter = std::make_shared<std::string>("");
};
