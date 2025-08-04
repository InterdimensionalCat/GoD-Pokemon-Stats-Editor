#pragma once
#include "UiSection.h"
//#include <deque>

typedef unsigned int GLuint;

class SpeciesInfo : public UiSection {
public:

	SpeciesInfo(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize);

	void UpdateElement() override;

	void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave) override;

	void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson) override;

	virtual float CalculateMinNeededLineLength() const;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const override;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const override;

	void OnFontUpdated() override;

private:

	// Combination of:
    // Identification info
    // Type info
    // Ability info
    // Wild Item info
    // Misc info

	void InitPokefaceData();

	void HandlePokefaceLoadingException(const int32_t index, const std::exception& e);

	// Using a deque because memory addresses do not get invalidated when a deque is resized.
	static std::deque<GLuint> PokefaceData;

	GLuint CurrentPokefaceData = 0;

	float PokefaceImageSize = 100.f;

	std::string SpeciesLabel;

	float MinTextBoxSize = -1;
};
