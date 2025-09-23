#include "include.h"
#include "Editors/PokemonStats/PokemonStatsEditor.h"
#include "Editors/PokemonStats/PokemonStatsSpeciesInfo.h"
#include "Editors/PokemonStats/PokemonStatsPokemonList.h"
#include "Editors/PokemonStats/PokemonStatsLearnedMoves.h"
#include "Editors/PokemonStats/PokemonStatsTaughtMoves.h"
#include "Editors/PokemonStats/PokemonStatsBaseStats.h"

PokemonStatsEditor::PokemonStatsEditor(std::shared_ptr<ImGuiWindowClass> InTabDockspace) : UiTab("Pokemon Stats Editor", InTabDockspace)
{
	RequiredForEditCSVFileNames = { "Pokemon Stats" };
	RequiredForViewingCSVFileNames = { "Type", "Ability", "Item", "Move" };

}

void PokemonStatsEditor::Init()
{
	std::shared_ptr<PokemonStatsSpeciesInfo> SpeciesInfo   = std::make_shared<PokemonStatsSpeciesInfo>(this);
	std::shared_ptr<PokemonStatsPokemonList> PokemonList   = std::make_shared<PokemonStatsPokemonList>(this);
	std::shared_ptr<PokemonStatsLearnedMoves> LearnedMoves = std::make_shared<PokemonStatsLearnedMoves>(this);
	std::shared_ptr<PokemonStatsTaughtMoves> TaughtMoves  = std::make_shared<PokemonStatsTaughtMoves>(this);
	std::shared_ptr<PokemonStatsBaseStats> BaseStats = std::make_shared<PokemonStatsBaseStats>(this);

	AddSection(SpeciesInfo);
	AddSection(PokemonList);
	AddSection(LearnedMoves);
	AddSection(TaughtMoves);
	AddSection(BaseStats);
	UiTab::Init();
}
