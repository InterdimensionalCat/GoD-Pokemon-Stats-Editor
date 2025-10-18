#include "include.h"
#include "Editors/Trainers/TrainersEditor.h"

TrainersEditor::TrainersEditor(std::shared_ptr<ImGuiWindowClass> InTabDockspace) : UiTab("Story Trainers Editor", InTabDockspace)
{
	RequiredForEditCSVFileNames = { TrainerCSVFileName, TrainerPokemonCSVFileName };

	// TODO: allow for editing of Trainer AI data in the trainers editor.
	RequiredForViewingCSVFileNames = { TrainerAICSVFileName };

}

void TrainersEditor::Init()
{
	//auto LearnedMovesSection = std::make_shared<LearnedMovesLearnsets>(this);
	//LearnedMovesFiltersSection = std::make_shared<LearnedMovesLearnsetsFilters>(this);

	//AddSection(LearnedMovesSection);
	//AddSection(LearnedMovesFiltersSection);

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