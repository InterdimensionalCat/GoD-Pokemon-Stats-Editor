#pragma once

//#include <string>
//#include "imgui.h"
//#include "nlohmann/json.hpp"

class UiSubsection;

class UiSection : public std::enable_shared_from_this<UiSection> {
public:
	// Contains Name ID, species Name ID, 
	UiSection(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize);

	virtual void Tick();

	virtual void UpdateElement();

	virtual void CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave);

	virtual void SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson);

	int32_t GetCurrentPokemonIndex() const;

	void SetUnsavedProgress(const bool UnsavedProgress);

	bool GetUnsavedProgress() const;

	void SetFocusedWindow();

	virtual void OnFontUpdated();

	virtual float CalculateMinNeededLineLength() const;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const;

	float MinSubsectionFieldSize = -1.f;
	float LargestSubsectionLabelSize = -1.f;
	float MinNeededLength = -1.f;

protected:
	std::string WindowName;
	ImVec2 InitialPos;
	ImVec2 InitialSize;
	int32_t CurrentPokemonIndex;

	// Largest lable not including subsections.
	float LargestLabelLength = -1.f;

	// Largest line not including subsections.
	float LargestElementLength = -1.f;

	float MaxAllowedLength = FLT_MAX;

	bool bUnsavedProgress = false;

	bool bSetWindowFocused = false;

	std::vector<std::shared_ptr<UiSubsection>> Subsections;
};
