#pragma once

#include <string>
#include "imgui.h"
#include "nlohmann/json.hpp"

class UiSection;

class UiSubsection : public std::enable_shared_from_this<UiSubsection> {
public:
	// Contains Name ID, species Name ID, 
	UiSubsection(UiSection* InParent, const std::string& InSubsectionName);

	virtual void UpdateElement();

	virtual void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave);

	virtual void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson);

	std::string GetSubsectionName() const;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const;

	virtual void OnFontUpdated();

protected:

	std::map<std::string, std::string> FieldLabels;

	std::string SubsectionName;
	UiSection* Parent;
};
