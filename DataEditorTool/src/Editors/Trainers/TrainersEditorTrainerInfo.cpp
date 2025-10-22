#include "include.h"
#include "Editors/Trainers/TrainersEditorTrainerInfo.h"

#include "Editors/Trainers/TrainersEditor.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVTextBox.h"

#include "CSV/CSVDatabase.h"
#include "CSV/CSVData.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntHexBox.h"
#include "UI/UiElement/UiMultiElement/UiChildWindow.h"
#include "UI/UiElement/UiMultiElement/UiSingleLineMultiElement.h"

TrainersEditorTrainerInfo::TrainersEditorTrainerInfo(TrainersEditor* InParent) : UiSection("Trainer Info", InParent)
{
	const std::string TrainerCSVFileName = InParent->GetTrainerCSVFileName();
	auto CSVDatabase = DataEditorInstance::Get()->GetCSVDatabase();
	auto TrainerCSV = CSVDatabase->GetCSVFile(TrainerCSVFileName);

	// Trainer Entry Name TextBox
	auto Trainer = std::make_shared<CSVTextBox>(
		"Trainer",
		this,
		TrainerCSVFileName,
		"Entry Name"
	);
	Trainer->SetMinFromLongestString(TrainerCSV->GetStringColumn("Entry Name"));

	// Trainer Name ID TextBox
	auto TrainerNameID = std::make_shared<CSVTextBox>(
		"Name ID",
		this,
		TrainerCSVFileName
	);
	TrainerNameID->SetMinFromLongestString(TrainerCSV->GetStringColumn("Name ID"));

	// Trainer Model ID TextBox
	auto TrainerModelID = std::make_shared<CSVTextBox>(
		"Model ID",
		this,
		TrainerCSVFileName
	);
	TrainerModelID->SetMinFromLongestString(TrainerCSV->GetStringColumn("Model ID"));
	TrainerModelID->SetDisabled(true);

	// Camera Effect ID IntHexBox. I believe this is the transition effect when this
	// trainer is battled, but not sure.
	auto CameraEffectID = std::make_shared<CSVIntHexBox>(
		"Camera Effect ID",
		this,
		TrainerCSVFileName,
		1,
		5
	);

	CameraEffectID->SetElementMinSize(3);

	// TODO: Make the battle text IDS wrapped multi-line text entries, or
	// move them to their own section, or both.

	// Pre Battle Text ID TextBox. This is the text shown after the battle loads,
	// but before the battle starts.
	auto PreBattleTextID = std::make_shared<CSVTextBox>(
		"Pre Battle Text ID",
		this,
		TrainerCSVFileName,
		"Pre Battle Text Id"
	);
	//PreBattleTextID->SetMinFromLongestString(TrainerCSV->GetStringColumn("Pre Battle Text Id"));

	// Victory Text ID TextBox. This is the text shown after the trainer defeats you.
	auto VictoryTextID = std::make_shared<CSVTextBox>(
		"Victory Text ID",
		this,
		TrainerCSVFileName,
		"Victory Text Id"
	);
	//VictoryTextID->SetMinFromLongestString(TrainerCSV->GetStringColumn("Victory Text Id"));

	// Loss Text ID TextBox. This is the text shown after the trainer is defeated.
	auto LossTextID = std::make_shared<CSVTextBox>(
		"Loss Text ID",
		this,
		TrainerCSVFileName,
		"Loss Text Id"
	);
	//LossTextID->SetMinFromLongestString(TrainerCSV->GetStringColumn("Loss Text Id"));

	AddElement(Trainer);
	AddElement(TrainerNameID);
	AddElement(TrainerModelID);
	AddElement(CameraEffectID);
	AddElement(PreBattleTextID);
	AddElement(VictoryTextID);
	AddElement(LossTextID);
}