#include "include.h"
#include "Editors/Trainers/TrainersEditor.h"

#include "Editors/Trainers/TrainersEditorTrainersList.h"
#include "Editors/Trainers/TrainersEditorTrainerInfo.h"
#include "Editors/Trainers/TrainersEditorTrainerPokemon.h"
#include "Editors/Trainers/TrainersEditorBattle.h"

TrainersEditor::TrainersEditor(std::shared_ptr<ImGuiWindowClass> InTabDockspace) : UiTab("Story Trainers Editor", InTabDockspace)
{
	RequiredForEditCSVFileNames = { TrainerCSVFileName, TrainerPokemonCSVFileName, "Shadow Pokemon", "Battle" };

	// TODO: allow for editing of Trainer AI data in the trainers editor.
	RequiredForViewingCSVFileNames = { TrainerAICSVFileName, "Pokemon Stats", "Pokemon AI Roles", "Nature", "Trainer Class" };

}

void TrainersEditor::Init()
{
	auto TrainersListSection = std::make_shared<TrainersEditorTrainersList>(this);
	auto TrainerInfoSection = std::make_shared<TrainersEditorTrainerInfo>(this);
	auto TrainerPokemonSection = std::make_shared<TrainersEditorTrainerPokemon>(this);
	auto TrainerBattleSection = std::make_shared<TrainersEditorBattle>(this);

	AddSection(TrainersListSection);
	AddSection(TrainerInfoSection);
	AddSection(TrainerPokemonSection);
	AddSection(TrainerBattleSection);

	UiTab::Init();
}

void TrainersEditor::LoadDefaultLayout()
{
	auto TabDockspaceID = UiTabID;
	ImGui::DockBuilderRemoveNode(TabDockspaceID);
	ImGui::DockBuilderAddNode(TabDockspaceID, ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(TabDockspaceID, ImGui::GetMainViewport()->Size);

	ImGuiID DockLeft;
	ImGuiID DockDown;

	// Split the window into 2 regions,
	// center, left, right, up and down
	ImGui::DockBuilderSplitNode(
		TabDockspaceID,
		ImGuiDir_Down,
		0.19f, &DockDown, &TabDockspaceID
	);

	ImGui::DockBuilderSplitNode(
		TabDockspaceID,
		ImGuiDir_Left,
		0.1f, &DockLeft, &TabDockspaceID
	);

	ImGuiID BattleDockspaceID;

	// Split the down region into two regions, left and right
	ImGui::DockBuilderSplitNode(
		DockDown,
		ImGuiDir_Right,
		0.30f, &BattleDockspaceID, &DockDown
	);

	// Trainer Pokemon goes in the center region.
	ImGui::DockBuilderDockWindow("Trainer Pokemon", TabDockspaceID);

	// Trainers list goes in the left region.
	ImGui::DockBuilderDockWindow("Trainers List", DockLeft);

	// Trainer info goes in the bottom region.
	ImGui::DockBuilderDockWindow("Trainer Info", DockDown);

	// Battle info goes in the bottom region.
	ImGui::DockBuilderDockWindow("Battle Info", BattleDockspaceID);
}

std::string TrainersEditor::GetTrainerCSVFileName() const
{
	return TrainerCSVFileName;
}

std::string TrainersEditor::GetTrainerPokemonCSVFileName() const
{
	return TrainerPokemonCSVFileName;
}

std::string TrainersEditor::GetTrainerAICSVFileName() const
{
	return TrainerAICSVFileName;
}