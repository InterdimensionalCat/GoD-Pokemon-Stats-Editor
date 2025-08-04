#pragma once
#include "UiSection.h"
//#include <array>
//#include <vector>
//#include <memory>

class ModifyEvolutionMethod;

class EvolutionInfo : public UiSection {
public:
	// Contains Name ID, species Name ID, 
	EvolutionInfo(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize);

	void UpdateElement() override;

	void UpdateConditionAsLevel(const int32_t i);

	void UpdateConditionAsItem(const int32_t i);

	void UpdateConditionAsEvolutionStone(const int32_t i);

	void UpdateConditionAsKeyItem(const int32_t i);

	void SaveLevelCondition(std::shared_ptr<nlohmann::json> PokemonStatsJson, const int32_t i);

	void SaveItemCondition(std::shared_ptr<nlohmann::json> PokemonStatsJson, const int32_t i);

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	//void ChangeEvolutionMethod(std::shared_ptr<ModifyEvolutionMethod> Command);

	virtual float CalculateMinNeededLineLength() const;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const override;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const override;

	void OnFontUpdated() override;

private:

	int32_t GetIntFromFormattedEntry(const std::string& Entry);

	std::vector<std::shared_ptr<std::string>> EvolutionMethods;
	std::vector<std::shared_ptr<std::string>> EvolutionConditions;
	std::vector<std::shared_ptr<std::string>> EvolutionForms;

	std::vector<std::shared_ptr<int32_t>> EvolutionConditionInts;
	std::vector<std::shared_ptr<std::string>> EvolutionConditionItems;

	std::vector<std::string> EvolutionMethodsList;
	std::vector<std::string> PokemonListFormatted;

	std::vector<std::shared_ptr<std::string>> MethodFilterStrings;
	std::vector<std::shared_ptr<std::string>> FormFilterStrings;
	std::vector<std::shared_ptr<std::string>> ConditionFilterStrings;

	std::vector<std::string> EvolutionItemsListItems;
	std::vector<std::string> EvolutionStonesList; // item 93 - 98
	std::vector<std::string> KeyItemsList; // 350-369, but has their ID ajusted to be the secondary item ID

	float MaxMethodLabelLength = 0;
	float MaxFormLabelLength = 0;
	float MaxConditionLabelLength = 0;

	float MethodBoxSize = 0;

	float ConditionBoxSize = 0;

	float FormInputTextSize = 0;
};
