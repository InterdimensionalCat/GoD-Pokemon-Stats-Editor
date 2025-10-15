#include "include.h"
#include "Editors/LearnedMoves/Learnset.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleImageBox.h"
#include "Pokeface/PokefaceData.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVTextBox.h"
#include "UI/UiElement/UiCSVElement/BoolElement/CSVRadioButton.h"

#include "CSV/CSVDatabase.h"
#include "CSV/CSVData.h"
#include "CSV/CSVHeader.h"

Learnset::Learnset(
	const std::string& InName,
	UiSection* InParent,
	int32_t InCurrentRow
) :
	UiSingleLineMultiElement(InName, InParent),
	CurrentRow(InCurrentRow)
{
	const std::string CSVName = "Pokemon Stats";

	auto PokefaceName = std::format("##Learnsets-Pokeface-{}", InCurrentRow);
	PokefaceImage = std::make_shared<SimpleImageBox>(PokefaceName, InParent);
	PokefaceImage->SetImageSize(ImGui::GetFrameHeight());

	PokemonName = std::make_shared<CSVTextBox>(
		std::format("##Learnsets-PokemonName-{}", InCurrentRow),
		InParent,
		"Pokemon Stats",
		"Entry Name"
	);

	PokemonName->SetCurrentRow(InCurrentRow);
	PokemonName->SetShouldSyncRowToCSVState(false);
	PokemonName->SetMinFromLongestString(GoDCSV::CSVDatabase::Get()->GetCSVFile("Pokemon Stats")->GetStringColumn("Entry Name"));
	PokemonName->SetIsFixedSize(true);

	AddElement(PokefaceImage);
	AddElement(PokemonName);

	// Add the TM, HM, and Tutor Move elements.
	auto TMMoveColumns = GetMoveColumns("TM");

	for (auto TMMove : TMMoveColumns)
	{
		auto TMNName = std::format("##{}Learnsets-{}", TMMove, InCurrentRow);
		auto TMMoveElement = std::make_shared<CSVRadioButton>(TMNName, InParent, CSVName, TMMove);
		TMMoveElement->SetCurrentRow(InCurrentRow);
		TMMoveElement->SetShouldSyncRowToCSVState(false);
		AddElement(TMMoveElement);
	}

	auto HMMoveColumns = GetMoveColumns("HM");

	for (auto HMMove : HMMoveColumns)
	{
		auto HMNName = std::format("##{}Learnsets-{}", HMMove, InCurrentRow);
		auto HMMoveElement = std::make_shared<CSVRadioButton>(HMNName, InParent, CSVName, HMMove);
		HMMoveElement->SetCurrentRow(InCurrentRow);
		HMMoveElement->SetShouldSyncRowToCSVState(false);
		AddElement(HMMoveElement);
	}

	auto TutorMoveColumns = GetMoveColumns("TutorMove");

	// Tutor moves are out of order in the CSV file, so we
	// need to sort them lexographically
	std::sort(TutorMoveColumns.begin(), TutorMoveColumns.end());

	for (auto TutorMove : TutorMoveColumns)
	{
		auto TutorMoveName = std::format("##{}Learnsets-{}", TutorMove, InCurrentRow);
		auto TutorMoveElement = std::make_shared<CSVRadioButton>(TutorMoveName, InParent, CSVName, TutorMove);
		TutorMoveElement->SetCurrentRow(InCurrentRow);
		TutorMoveElement->SetShouldSyncRowToCSVState(false);
		AddElement(TutorMoveElement);
	}
}

void Learnset::Refresh()
{
	UiSingleLineMultiElement::Refresh();

	PokefaceImage->SetImageSize(ImGui::GetFrameHeight());

	// Update the Pokeface image based on the current row.
	const auto& PokefaceDataIds = PokefaceData::GetPokefaceData();

	if (!PokefaceDataIds.empty())
	{
		PokefaceImage->SetTexture(PokefaceDataIds.at(CurrentRow));
	}
}

std::vector<std::string> Learnset::GetMoveColumns(const std::string& MoveColumnPrefix) const
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