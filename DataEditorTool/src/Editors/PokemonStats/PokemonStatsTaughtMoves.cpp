#include "include.h"
#include "Editors/PokemonStats/PokemonStatsTaughtMoves.h"
#include "Editors/PokemonStats/PokemonStatsEditor.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleSectionDivider.h"
#include "UI/UiElement/UiCSVElement/BoolElement/CSVCheckbox.h"
#include "UI/UiElement/UiMultiElement/UiElementGrid.h"

#include "CSV/CSVDatabase.h"
#include "CSV/CSVData.h"
#include "CSV/CSVHeader.h"

using namespace GoDCSV;

PokemonStatsTaughtMoves::PokemonStatsTaughtMoves(PokemonStatsEditor* InParent) : UiSection("TMs, HMs, and Tutor Moves", InParent)
{
	const std::string CSVName = "Pokemon Stats";

	// Add the TM, HM, and Tutor Move elements.
	auto TaughtMovesGrid = std::make_shared<UiElementGrid>("Taught Moves Grid", this);
	TaughtMovesGrid->SetShouldAlignElements(true);

	// Add the TM moves.
	auto TMSectionDivider = std::make_shared<SimpleSectionDivider>("TMs", this);
	TMSectionDivider->SetNumSpaceLengths(0);
	TaughtMovesGrid->AddElement(TMSectionDivider, false);

	auto TMMoveColumns = GetMoveColumns("TM");

	for (auto TMMove : TMMoveColumns)
	{
		TaughtMovesGrid->AddElement(
			std::make_shared<CSVCheckbox>(TMMove, this, CSVName),
			true
		);
	}

	// Add the HM moves.
	auto HMSectionDivider = std::make_shared<SimpleSectionDivider>("HMs", this);
	TaughtMovesGrid->AddElement(HMSectionDivider, false);

	auto HMMoveColumns = GetMoveColumns("HM");

	for (auto HMMove : HMMoveColumns)
	{
		TaughtMovesGrid->AddElement(
			std::make_shared<CSVCheckbox>(HMMove, this, CSVName),
			true
		);
	}

	// Add the Tutor moves.
	auto TutorSectionDivider = std::make_shared<SimpleSectionDivider>("Tutor Moves", this);
	TaughtMovesGrid->AddElement(TutorSectionDivider, false);

	auto TutorMoveColumns = GetMoveColumns("TutorMove");

	// Tutor moves are out of order in the CSV file, so we
	// need to sort them lexographically
	std::sort(TutorMoveColumns.begin(), TutorMoveColumns.end());

	for (auto TutorMove : TutorMoveColumns)
	{
		TaughtMovesGrid->AddElement(
			std::make_shared<CSVCheckbox>(TutorMove, this, CSVName),
			true
		);
	}

	AddElement(TaughtMovesGrid);

}

std::vector<std::string> PokemonStatsTaughtMoves::GetMoveColumns(const std::string& MoveColumnPrefix) const
{
	const std::string CSVName = "Pokemon Stats";
	const auto Database = CSVDatabase::Get();
	const auto PokemonStatsCSV = Database->GetCSVFile(CSVName);
	const auto CSVHeader = PokemonStatsCSV->GetHeaderRow();
	const auto& HeaderArray = CSVHeader->GetColumnNamesArray();

	std::vector<std::string> MoveColumns;

	for (auto& ColumnName : HeaderArray)
	{
		if (ColumnName.find(MoveColumnPrefix) == 0)
		{
			MoveColumns.push_back(ColumnName);
		}
	}

	return MoveColumns;
}
