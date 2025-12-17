#include "include.h"
#include "Editors/Trainers/TrainersEditorBattle.h"
#include "Editors/Trainers/TrainersEditor.h"
#include "UI/UiElement/UiCSVElement/UiCSVElement.h"

#include "UI/UiElement/UiCSVElement/StringElement/CSVComboBox.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVTextBox.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntHexBox.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVIntHexComboBox.h"

TrainersEditorBattle::TrainersEditorBattle(TrainersEditor* InParent) : UiSection("Battle Info", InParent)
{
    ParentEditor = InParent;

	InitBattleInfo();
}

void TrainersEditorBattle::Refresh()
{

	auto TrainersCSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile(
		ParentEditor->GetTrainerCSVFileName()
	);

    auto BattleCSVData = GoDCSV::CSVDatabase::Get()->GetCSVFile("Battle");

	auto CurrentTrainerRowIndex = ParentEditor->GetTabCSVState()->GetCurrentRow();

	auto PlayerTwoTrainerIDs = BattleCSVData->GetIntColumn("Players 2 Trainer ID");
	auto PlayerTwoDeckIDs = BattleCSVData->GetStringColumn("Players 2 Deck ID");

    int32_t NewRow = 0;

    // Returns "Trainer Pokemon DeckData_{}.bin"
    auto DeckDataFileName = ParentEditor->GetTrainerPokemonCSVFileName();

    // Remove the "Trainer Pokemon " from the string.
    DeckDataFileName.erase(0, 16);

    for (int32_t Index = 0; Index < PlayerTwoTrainerIDs.size(); Index++)
    {
		auto TrainerID = PlayerTwoTrainerIDs.at(Index);
        if (TrainerID == CurrentTrainerRowIndex && PlayerTwoDeckIDs.at(Index).contains(DeckDataFileName))
        {
			NewRow = Index;
            break;
        }
    }

	SetCurrentRow(NewRow);

	UiSection::Refresh();
}

void TrainersEditorBattle::SetCurrentRow(const int32_t InRow)
{
	CurrentRow = InRow;

	for (auto& Element : BattleElements)
	{
		Element->SetCurrentRow(InRow);
	}
}

void TrainersEditorBattle::InitBattleInfo()
{
    // Battle mode elements:
    // Battle Style (single or double) (combo box)
    // Battle Field ID (string) TODO: Make this a combo box later, however 
    // there are almost 40 different values that would need to be hard coded
    // BGM ID (combo box that converts selection to an IntHex value)

    auto BattleStyleElement = std::make_shared<CSVComboBox>(
        "Battle Style",
        this,
        "Battle",
        "Battle Style",
        "BattleStyle",
        "BattleStyle"
	);

	BattleElements.push_back(BattleStyleElement);
	AddElement(BattleStyleElement);

    auto BattleFieldID = std::make_shared<CSVTextBox>(
        "Battle Field ID",
        this,
        "Battle",
		"Battle Field ID"
    );

	BattleElements.push_back(BattleFieldID);
	AddElement(BattleFieldID);

    //auto BGMID = std::make_shared<CSVIntHexComboBox>(
    //    "BGM ID",
    //    this,
    //    "Battle",
    //    "BGM ID"
    //);

    auto BGMID = std::make_shared<CSVIntHexComboBox>(
        "BGM ID",
        this,
        "Battle",
        "BGM ID",
		"BGMID",
        "BGMID"
    );

	BattleElements.push_back(BGMID);
	AddElement(BGMID);

  //  auto BGMID = std::make_shared<CSVComboBox>(
  //      "BGM ID",
  //      this,
  //      "Battle",
  //      "BGM ID",
  //      "BGMID",
		//"BGMID"
}
