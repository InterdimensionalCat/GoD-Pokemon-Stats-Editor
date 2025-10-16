#include "include.h"
#include "Editors/LearnedMoves/LearnedMovesLearnsetsFilters.h"
#include "Editors/LearnedMoves/LearnedMovesEditor.h"

#include "UI/UiElement/UiSimpleElement/StringElement/SimpleTextBox.h"

#include "CSV/CSVDatabase.h"
#include "CSV/CSVData.h"

LearnedMovesLearnsetsFilters::LearnedMovesLearnsetsFilters(LearnedMovesEditor* InParent) : UiSection("Learnsets Filters", InParent)
{
	const std::string CSVName = "Pokemon Stats";

	const auto& CSVDatabase = GoDCSV::CSVDatabase::Get();
	auto NewEntriesList = CSVDatabase->GetCSVFile(CSVName)->GetStringColumn("Entry Name");

	MoveFilterBox = std::make_shared<SimpleTextBox>("Filter Moves", this);
	MoveFilterBox->SetMinFromLongestString(NewEntriesList);
	MoveFilterBox->SetTextBoxBuffer("");

	PokemonFilterBox = std::make_shared<SimpleTextBox>("Filter Pokemon", this);
	PokemonFilterBox->SetMinFromLongestString(NewEntriesList);
	PokemonFilterBox->SetTextBoxBuffer("");

	AddElement(MoveFilterBox);
	AddElement(PokemonFilterBox);
}

void LearnedMovesLearnsetsFilters::Refresh()
{
	UiSection::Refresh();
}

std::string LearnedMovesLearnsetsFilters::GetMoveFilterText() const
{
	return MoveFilterBox->GetTextBoxBuffer();
}

std::string LearnedMovesLearnsetsFilters::GetPokemonFilterText() const
{
	return PokemonFilterBox->GetTextBoxBuffer();
}