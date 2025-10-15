#include "include.h"
#include "Editors/LearnedMoves/LearnedMovesLearnsets.h"
#include "Editors/LearnedMoves/LearnedMovesEditor.h"
#include "Editors/LearnedMoves/LearnedMovesLearnsetsFilters.h"

#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"
#include "UI/UiElement/UiMultiElement/UiTable.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleImageBox.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVTextBox.h"
#include "UI/UiElement/UiCSVElement/BoolElement/CSVRadioButton.h"
#include "UI/UiElement/UiCSVElement/BoolElement/CSVCheckbox.h"
#include "UI/UiElement/UiSimpleElement/StringElement/SimpleTextBox.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleText.h"
#include "Pokeface/PokefaceData.h"

#include "CSV/CSVDatabase.h"
#include "CSV/CSVData.h"
#include "CSV/CSVHeader.h"

LearnedMovesLearnsets::LearnedMovesLearnsets(LearnedMovesEditor* InParent) :
	UiSection("Pokemon Learnsets", InParent),
	ParentEditor(InParent)
{
	const std::string CSVName = "Pokemon Stats";

	// Add a Learnset element for each Pokemon in the "Pokemon Stats" CSV file.
	const auto& CSVDatabase = GoDCSV::CSVDatabase::Get();
	auto NewEntriesList = CSVDatabase->GetCSVFile(CSVName)->GetStringColumn("Entry Name");

	LearnsetsTable = std::make_shared<UiTable>("Learnsets Table", this);

	// Set up column 1: Pokeface and Pokemon Name
	const auto& PokefaceDataIds = PokefaceData::GetPokefaceData();
	LearnsetsTable->AddNewColumn("Pokemon");
	for (int32_t RowIndex = 0; RowIndex < NewEntriesList.size(); ++RowIndex)
	{
		auto CurrentPokemonMultiElement = std::make_shared<UiSingleLineMultiElement>(
			std::format("##{}", NewEntriesList.at(RowIndex)),
			this
		);

		auto PokefaceName = std::format("##Learnsets-Pokeface-{}", RowIndex);
		auto PokefaceImage = std::make_shared<SimpleImageBox>(PokefaceName, this);
		PokefaceImage->SetImageSize(ImGui::GetFrameHeight());

		if (!PokefaceDataIds.empty())
		{
			PokefaceImage->SetTexture(PokefaceDataIds.at(RowIndex));
		}

		auto PokemonName = std::make_shared<CSVTextBox>(
			std::format("##Learnsets-PokemonName-{}", NewEntriesList.at(RowIndex)),
			this,
			"Pokemon Stats",
			"Entry Name"
		);

		PokemonName->SetCurrentRow(RowIndex);
		PokemonName->SetShouldSyncRowToCSVState(false);
		PokemonName->SetMinFromLongestString(GoDCSV::CSVDatabase::Get()->GetCSVFile("Pokemon Stats")->GetStringColumn("Entry Name"));
		PokemonName->SetIsFixedSize(true);
		PokemonName->SetDisabled(true);

		CurrentPokemonMultiElement->AddElement(PokefaceImage);
		CurrentPokemonMultiElement->AddElement(PokemonName);

		LearnsetsTable->AddElement(CurrentPokemonMultiElement);
	}

	// Set up a column for each TM, HM, and Tutor Move
	auto TMMoveColumns = GetMoveColumns("TM");

	for (auto& TMMove : TMMoveColumns)
	{
		LearnsetsTable->AddNewColumn(TMMove);
		for (int32_t RowIndex = 0; RowIndex < NewEntriesList.size(); ++RowIndex)
		{
			auto TMName = std::format("##{}Learnsets-{}", TMMove, RowIndex);
			auto TMMoveElement = std::make_shared<CSVCheckbox>(TMName, this, CSVName, TMMove);
			TMMoveElement->SetCurrentRow(RowIndex);
			TMMoveElement->SetShouldSyncRowToCSVState(false);
			LearnsetsTable->AddElement(TMMoveElement);
		}

	}

	auto HMMoveColumns = GetMoveColumns("HM");

	for (auto& HMMove : HMMoveColumns)
	{
		LearnsetsTable->AddNewColumn(HMMove);
		for (int32_t RowIndex = 0; RowIndex < NewEntriesList.size(); ++RowIndex)
		{
			auto HMName = std::format("##{}Learnsets-{}", HMMove, RowIndex);
			auto HMMoveElement = std::make_shared<CSVCheckbox>(HMName, this, CSVName, HMMove);
			HMMoveElement->SetCurrentRow(RowIndex);
			HMMoveElement->SetShouldSyncRowToCSVState(false);
			LearnsetsTable->AddElement(HMMoveElement);
		}

	}

	auto TutorMoveColumns = GetMoveColumns("TutorMove");

	// Tutor moves are out of order in the CSV file, so we
	// need to sort them lexographically
	std::sort(TutorMoveColumns.begin(), TutorMoveColumns.end());

	for (auto& TutorMove : TutorMoveColumns)
	{
		LearnsetsTable->AddNewColumn(TutorMove);
		for (int32_t RowIndex = 0; RowIndex < NewEntriesList.size(); ++RowIndex)
		{
			auto TutorName = std::format("##{}Learnsets-{}", TutorMove, RowIndex);
			auto TutorMoveElement = std::make_shared<CSVCheckbox>(TutorName, this, CSVName, TutorMove);
			TutorMoveElement->SetCurrentRow(RowIndex);
			TutorMoveElement->SetShouldSyncRowToCSVState(false);
			LearnsetsTable->AddElement(TutorMoveElement);
		}

	}

	AddElement(LearnsetsTable);
}

void LearnedMovesLearnsets::Refresh()
{
	UiSection::Refresh();
}

void LearnedMovesLearnsets::Tick()
{
	UiSection::Tick();

	auto LearnsetFilters = ParentEditor->GetLearnedMovesFiltersSection();

	LearnsetsTable->SetRowFilter(LearnsetFilters->GetPokemonFilterText());
	LearnsetsTable->SetColumnFilter(LearnsetFilters->GetMoveFilterText());
}

std::vector<std::string> LearnedMovesLearnsets::GetMoveColumns(const std::string& MoveColumnPrefix) const
{
	const std::string CSVName = "Pokemon Stats";
	const auto Database = GoDCSV::CSVDatabase::Get();
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