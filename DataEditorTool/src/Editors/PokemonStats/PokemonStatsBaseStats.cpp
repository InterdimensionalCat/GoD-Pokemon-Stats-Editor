#include "include.h"
#include "Editors/PokemonStats/PokemonStatsBaseStats.h"
#include "Editors/PokemonStats/PokemonStatsEditor.h"
#include "Editors/PokemonStats/BaseStatTotal.h"
#include "Editors/PokemonStats/BaseStat.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntBox.h"
#include "UI/UiElement/UiSimpleElement/IntElement/SimpleIntBox.h"



PokemonStatsBaseStats::PokemonStatsBaseStats(PokemonStatsEditor* InParent) : UiSection("Base Stats", InParent)
{
	const std::string CSVName = "Pokemon Stats";

	BaseStatElements[0] = std::make_shared<BaseStat>("     HP:", this, "Base Stats HP");
	BaseStatElements[1] = std::make_shared<BaseStat>(" Attack:", this, "Base Stats Attack");
	BaseStatElements[2] = std::make_shared<BaseStat>("Defense:", this, "Base Stats Defense");
	BaseStatElements[3] = std::make_shared<BaseStat>("Sp. Atk:", this, "Base Stats Sp.Atk");
	BaseStatElements[4] = std::make_shared<BaseStat>("Sp. Def:", this, "Base Stats Sp.Def");
	BaseStatElements[5] = std::make_shared<BaseStat>("  Speed:", this, "Base Stats Speed");
	CurrentBST     = std::make_shared<BaseStatTotal>("  Total:", this);
	for (auto& BaseStat : BaseStatElements)
	{
		AddElement(BaseStat);
	}

	AddElement(CurrentBST);
}

void PokemonStatsBaseStats::Tick()
{
	CalculateBaseStatTotal();
	UiSection::Tick();
}

void PokemonStatsBaseStats::CalculateBaseStatTotal()
{
	int32_t BaseStatTotalInt = 0;
	for (auto BaseStat : BaseStatElements)
	{
		BaseStatTotalInt += BaseStat->GetStatIntBox()->GetManagedValue();
	}
	CurrentBST->UpdateStatTotal(BaseStatTotalInt);

	// Resize this element to match the size of the stat int boxes above it.
	// auto FirstElementIntBox = BaseStatElements[0]->GetStatIntBox();
	CurrentBST->GetIntBox()->SetElementMinSize(3);
}
