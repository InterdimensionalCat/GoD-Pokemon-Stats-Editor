#pragma once
#include "UiSection.h"

//#include <vector>
//#include <string>

class TeachableMoveInfo : public UiSection {
public:
	TeachableMoveInfo(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	virtual float CalculateMinNeededLineLength() const;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const;

	void OnFontUpdated() override;

private:
	
	int32_t ItemsPerLine = 1;

	std::vector<std::shared_ptr<bool>> TMLearnField;
	std::vector<std::shared_ptr<bool>> HMLearnField;
	std::vector<std::shared_ptr<bool>> TutorLearnField;

	std::vector<std::string> TMCheckboxNames;
	std::vector<std::string> HMCheckboxNames;
	std::vector<std::string> TutorCheckboxNames;
};