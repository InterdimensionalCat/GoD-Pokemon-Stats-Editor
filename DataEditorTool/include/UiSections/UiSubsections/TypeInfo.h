#pragma once
#include "UiSubsection.h"
//#include <vector>

class TypeInfo : public UiSubsection {
public:
	TypeInfo(OldUiSection* InParent, const std::string& InSubsectionName);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const;

private:

	std::vector<std::string> TypesListItems;

	std::shared_ptr<std::string> CurrentType1 = std::make_shared<std::string>("---");
	std::shared_ptr<std::string> CurrentType2 = std::make_shared<std::string>("---");

	std::shared_ptr<std::string> CurrentType1Filter = std::make_shared<std::string>("");
	std::shared_ptr<std::string> CurrentType2Filter = std::make_shared<std::string>("");
};
