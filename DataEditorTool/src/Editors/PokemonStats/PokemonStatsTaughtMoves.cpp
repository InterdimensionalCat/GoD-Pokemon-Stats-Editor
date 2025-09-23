#include "include.h"
#include "Editors/PokemonStats/PokemonStatsTaughtMoves.h"
#include "Editors/PokemonStats/PokemonStatsEditor.h"
#include "UI/BasicUiElements/SectionDivider.h"
#include "UI/BasicUiElements/CSVCheckbox.h"
#include "UI/UiElementGrid.h"

#include "CSV/CSVDatabase.h"
#include "CSV/NewCSVData.h"
#include "CSV/CSVHeader.h"
#include "UI/BasicUiElements/SectionDivider.h"

using namespace GoDCSV;

PokemonStatsTaughtMoves::PokemonStatsTaughtMoves(PokemonStatsEditor* InParent) : UiSection("TMs, HMs, and Tutor Moves", InParent)
{
	const std::string CSVName = "Pokemon Stats";

	// Add the TM, HM, and Tutor Move elements.
	auto TaughtMovesGrid = std::make_shared<UiElementGrid>("Taught Moves Grid", this);
	TaughtMovesGrid->SetShouldAlignElements(true);

	// Add the TM moves.
	auto TMSectionDivider = std::make_shared<SectionDivider>("TMs", this);
	TMSectionDivider->SetNumSpaceLengths(0);
	TaughtMovesGrid->AddSectionDivider(TMSectionDivider);

	auto TMMoveColumns = GetMoveColumns("TM");

	for (auto TMMove : TMMoveColumns)
	{
		TaughtMovesGrid->AddCSVElement(
			std::make_shared<CSVCheckbox>(TMMove, this, CSVName)
		);
	}

	// Add the HM moves.
	auto HMSectionDivider = std::make_shared<SectionDivider>("HMs", this);
	TaughtMovesGrid->AddSectionDivider(HMSectionDivider);

	auto HMMoveColumns = GetMoveColumns("HM");

	for (auto HMMove : HMMoveColumns)
	{
		TaughtMovesGrid->AddCSVElement(
			std::make_shared<CSVCheckbox>(HMMove, this, CSVName)
		);
	}

	// Add the Tutor moves.
	auto TutorSectionDivider = std::make_shared<SectionDivider>("Tutor Moves", this);
	TaughtMovesGrid->AddSectionDivider(TutorSectionDivider);

	auto TutorMoveColumns = GetMoveColumns("TutorMove0");

	// Tutor moves are out of order in the CSV file, so we
	// need to sort them lexographically
	std::sort(TutorMoveColumns.begin(), TutorMoveColumns.end());

	for (auto TutorMove : TutorMoveColumns)
	{
		TaughtMovesGrid->AddCSVElement(
			std::make_shared<CSVCheckbox>(TutorMove, this, CSVName)
		);
	}

	AddElement(TaughtMovesGrid);

}

std::vector<std::string> PokemonStatsTaughtMoves::GetMoveColumns(const std::string& MoveColumnPrefix) const
{
	const std::string CSVName = "Pokemon Stats";
	const auto Database = CSVDatabase::Get();
	const auto PokemonStatsCSV = Database->GetCSVFile<NewCSVData>(CSVName);
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
