#include "include.h"
#include "Editors/Trainers/TrainersEditor.h"

#include "Editors/Trainers/TrainersEditorTrainersList.h"
#include "Editors/Trainers/TrainersEditorTrainerInfo.h"
#include "Editors/Trainers/TrainersEditorTrainerPokemon.h"

TrainersEditor::TrainersEditor(std::shared_ptr<ImGuiWindowClass> InTabDockspace) : UiTab("Story Trainers Editor", InTabDockspace)
{
	RequiredForEditCSVFileNames = { TrainerCSVFileName, TrainerPokemonCSVFileName };

	// TODO: allow for editing of Trainer AI data in the trainers editor.
	RequiredForViewingCSVFileNames = { TrainerAICSVFileName, "Pokemon Stats", "Pokemon AI Roles", "Nature" };

}

void TrainersEditor::Init()
{
	auto TrainersListSection = std::make_shared<TrainersEditorTrainersList>(this);
	auto TrainerInfoSection = std::make_shared<TrainersEditorTrainerInfo>(this);
	auto TrainerPokemonSection = std::make_shared<TrainersEditorTrainerPokemon>(this);

	AddSection(TrainersListSection);
	AddSection(TrainerInfoSection);
	AddSection(TrainerPokemonSection);

	UiTab::Init();
}

void TrainersEditor::LoadDefaultLayout()
{
	//auto TabDockspaceID = UiTabID;
	//ImGui::DockBuilderRemoveNode(TabDockspaceID);
	//ImGui::DockBuilderAddNode(TabDockspaceID, ImGuiDockNodeFlags_DockSpace);
	//ImGui::DockBuilderSetNodeSize(TabDockspaceID, ImGui::GetMainViewport()->Size);

	//ImGuiID DockLeft;

	//ImGui::DockBuilderSplitNode(
	//	TabDockspaceID,
	//	ImGuiDir_Left,
	//	0.185f, &DockLeft, &TabDockspaceID
	//);

	//// Learned moves goes in the center region.
	//ImGui::DockBuilderDockWindow("Pokemon Learnsets", TabDockspaceID);

	//// Species info goes in the top half of the left region.
	//ImGui::DockBuilderDockWindow("Learnsets Filters", DockLeft);
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