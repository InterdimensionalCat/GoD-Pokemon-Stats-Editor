#include "include.h"
#include "Editors/LearnedMoves/LearnedMovesEditor.h"

#include "Editors/LearnedMoves/LearnedMovesLearnsets.h"
#include "Editors/LearnedMoves/LearnedMovesLearnsetsFilters.h"
#include "MainEditor/MainEditorWindow.h"

LearnedMovesEditor::LearnedMovesEditor(std::shared_ptr<ImGuiWindowClass> InTabDockspace) : UiTab("Taught Moves Editor", InTabDockspace)
{
	RequiredForEditCSVFileNames = { "Pokemon Stats" };
	RequiredForViewingCSVFileNames = {};

}

void LearnedMovesEditor::Init()
{
	auto LearnedMovesSection = std::make_shared<LearnedMovesLearnsets>(this);
	LearnedMovesFiltersSection = std::make_shared<LearnedMovesLearnsetsFilters>(this);

	AddSection(LearnedMovesSection);
	AddSection(LearnedMovesFiltersSection);

	UiTab::Init();
}

void LearnedMovesEditor::LoadDefaultLayout()
{
	auto TabDockspaceID = UiTabID;
	ImGui::DockBuilderRemoveNode(TabDockspaceID);
	ImGui::DockBuilderAddNode(TabDockspaceID, ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(TabDockspaceID, ImGui::GetMainViewport()->Size);

	ImGuiID DockLeft;

	ImGui::DockBuilderSplitNode(
		TabDockspaceID,
		ImGuiDir_Left,
		0.185f, &DockLeft, &TabDockspaceID
	);

	// Learned moves goes in the center region.
	ImGui::DockBuilderDockWindow("Pokemon Learnsets", TabDockspaceID);

	// Species info goes in the top half of the left region.
	ImGui::DockBuilderDockWindow("Learnsets Filters", DockLeft);
}

std::shared_ptr<LearnedMovesLearnsetsFilters> LearnedMovesEditor::GetLearnedMovesFiltersSection()
{
	return LearnedMovesFiltersSection;
}