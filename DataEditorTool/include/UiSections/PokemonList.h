#pragma once
#include "UiSection.h"
//#include <vector>

class PokemonList : public OldUiSection
{
public:
	PokemonList(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize);

	void UpdateElement() override;

	void SetScrollToItem(const bool InScrollToItem);

	void SetCurrentlySelectedItem(const std::string& NewItemString);

	const std::vector<std::string>& GetPokemonListItems();

	virtual float CalculateMinNeededLineLength() const;

	// Min needed size of the largest label
	virtual float CalculateLargestLabelLength() const override;

	// Min needed size for the largest line of elements
	virtual float CalculateLargestElementLength() const override;

	void OnFontUpdated() override;

	std::string FilterString;
private:

	std::vector<std::string> PokemonListItems;

	std::string CurrentlySelectedItem = "None  - 0";

	bool bActivateTextBoxFromComboTyping = false;

	bool bScrollToItem = false;
};