#pragma once

#include "UI/UiTab.h"

class PokemonStatsEditor : public UiTab
{

public:

	PokemonStatsEditor(std::shared_ptr<ImGuiWindowClass> InTabDockspace);

	virtual void Init() override;
};