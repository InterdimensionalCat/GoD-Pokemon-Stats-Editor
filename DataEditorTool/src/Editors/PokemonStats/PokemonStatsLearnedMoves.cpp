#include "include.h"
#include "Editors/PokemonStats/PokemonStatsLearnedMoves.h"
#include "Editors/PokemonStats/PokemonStatsEditor.h"
#include "Editors/PokemonStats/LevelUpMove.h"
#include "UI/BasicUiElements/SectionDivider.h"
#include "UI/BasicUiElements/CSVComboBox.h"
#include "UI/MultiLineUiElement.h"
#include "UI/UiElementGrid.h"

PokemonStatsLearnedMoves::PokemonStatsLearnedMoves(PokemonStatsEditor* InParent) : UiSection("Learned Moves", InParent)
{
	const std::string CSVName = "Pokemon Stats";

	// Add the level up moves elements.

	auto LevelUpMovesSectionDivider = std::make_shared<SectionDivider>("Level Up Moves", this);
	LevelUpMovesSectionDivider->SetNumSpaceLengths(0);
	AddElement(LevelUpMovesSectionDivider);

	// TODO: make this no longer a hard coded value, get all the rows and
	// check how many level up move rows there are
	for (int32_t MoveNum = 1; MoveNum < 20; MoveNum++)
	{
		auto MoveElement = std::make_shared<LevelUpMove>(std::format("##LevelUpMove-{}", MoveNum), this, MoveNum);
		AddElement(MoveElement);
		LevelUpMoves.push_back(MoveElement);
	}

	// Add the egg moves elements.

	AddElement(std::make_shared<SectionDivider>("Egg Moves", this));

	// TODO: Calculate the number of egg moves in the CSV file instead of using a hard coded value.
	const int32_t NumMoves = 9;

	auto EggMovesGrid = std::make_shared<UiElementGrid>("Egg Moves Grid", this);

	for (int32_t MoveNum = 1; MoveNum < NumMoves; MoveNum++)
	{
		const std::string MoveComboBoxColumn = std::format("Egg Moves {}", MoveNum);
		EggMovesGrid->AddCSVElement(
			std::make_shared<CSVComboBox>("##" + MoveComboBoxColumn, this, CSVName, MoveComboBoxColumn, "Move")
		);
	}

	EggMovesGrid->SetMaxColumns(2);

	AddElement(EggMovesGrid);

	//for (int32_t MoveNum = 1; MoveNum < NumMoves; MoveNum+=2)
	//{
	//	auto EggMovesMultiLine = std::make_shared<MultiLineUiElement>(std::format("Egg Moves {} MultiLine", MoveNum), this);
	//	const std::string MoveComboBoxColumnOne = std::format("Egg Moves {}", MoveNum);
	//	EggMovesMultiLine->AddCSVElement(
	//		std::make_shared<CSVComboBox>("##" + MoveComboBoxColumnOne, this, CSVName, MoveComboBoxColumnOne, "Move")
	//	);

	//	if (MoveNum + 1 < NumMoves)
	//	{
	//		const std::string MoveComboBoxColumnTwo = std::format("Egg Moves {}", MoveNum + 1);
	//		EggMovesMultiLine->AddCSVElement(
	//			std::make_shared<CSVComboBox>("##" + MoveComboBoxColumnTwo, this, CSVName, MoveComboBoxColumnTwo, "Move")
	//		);
	//	}

	//	AddElement(EggMovesMultiLine);
	//}
}

std::shared_ptr<LevelUpMove> PokemonStatsLearnedMoves::GetLevelUpMoveAtIndex(const int32_t Index)
{
	return LevelUpMoves.at(Index);
}

const std::vector<std::shared_ptr<LevelUpMove>>& PokemonStatsLearnedMoves::GetLevelUpMoves() const
{
	return LevelUpMoves;
}