#include "include.h"
#include "Editors/LearnedMoves/LearnedMovesEditor.h"

#include "Editors/LearnedMoves/LearnedMovesLearnsets.h"
#include "MainEditor/MainEditorWindow.h"

LearnedMovesEditor::LearnedMovesEditor(std::shared_ptr<ImGuiWindowClass> InTabDockspace) : UiTab("Learned Moves Editor", InTabDockspace)
{
	RequiredForEditCSVFileNames = { "Pokemon Stats" };
	RequiredForViewingCSVFileNames = {};

}

void LearnedMovesEditor::Init()
{
	auto LearnedMovesSection = std::make_shared<LearnedMovesLearnsets>(this);
	//std::shared_ptr<PokemonStatsSpeciesInfo> SpeciesInfo = std::make_shared<PokemonStatsSpeciesInfo>(this);
	//std::shared_ptr<PokemonStatsPokemonList> PokemonList = std::make_shared<PokemonStatsPokemonList>(this);
	//std::shared_ptr<PokemonStatsLearnedMoves> LearnedMoves = std::make_shared<PokemonStatsLearnedMoves>(this);
	//std::shared_ptr<PokemonStatsTaughtMoves> TaughtMoves = std::make_shared<PokemonStatsTaughtMoves>(this);
	//std::shared_ptr<PokemonStatsBaseStats> BaseStats = std::make_shared<PokemonStatsBaseStats>(this);
	//std::shared_ptr<PokemonStatsEvolutionInfo> EvolutionInfo = std::make_shared<PokemonStatsEvolutionInfo>(this);

	AddSection(LearnedMovesSection);
	//AddSection(SpeciesInfo);
	//AddSection(PokemonList);
	//AddSection(LearnedMoves);
	//AddSection(TaughtMoves);
	//AddSection(BaseStats);
	//AddSection(EvolutionInfo);
	UiTab::Init();
}

void LearnedMovesEditor::LoadDefaultLayout()
{
	//auto TabDockspaceID = UiTabID;
	//ImGui::DockBuilderRemoveNode(TabDockspaceID);
	//ImGui::DockBuilderAddNode(TabDockspaceID, ImGuiDockNodeFlags_DockSpace);
	//ImGui::DockBuilderSetNodeSize(TabDockspaceID, ImGui::GetMainViewport()->Size);

	//ImGuiID DockLeft;
	//ImGuiID DockRight;
	//ImGuiID DockUp;
	//ImGuiID DockDown;

	//// Split the window into 5 regions,
	//// center, left, right, up and down
	//ImGui::DockBuilderSplitNode(
	//	TabDockspaceID,
	//	ImGuiDir_Down,
	//	0.13f, &DockDown, &TabDockspaceID
	//);

	//ImGui::DockBuilderSplitNode(
	//	TabDockspaceID,
	//	ImGuiDir_Left,
	//	0.185f, &DockLeft, &TabDockspaceID
	//);

	//ImGui::DockBuilderSplitNode(
	//	TabDockspaceID,
	//	ImGuiDir_Right,
	//	0.31f, &DockRight, &TabDockspaceID
	//);

	//ImGui::DockBuilderSplitNode(
	//	TabDockspaceID,
	//	ImGuiDir_Up,
	//	0.20f, &DockUp, &TabDockspaceID
	//);

	//ImGuiID ListDockspaceID;

	//// Split the left region into two regions, top and bottom
	//ImGui::DockBuilderSplitNode(
	//	DockLeft,
	//	ImGuiDir_Down,
	//	0.5f, &ListDockspaceID, &DockLeft
	//);

	//// TODO: window names are hard coded, consider
	//// using GetName() on all sections to get these values.

	//// Learned moves goes in the center region.
	//ImGui::DockBuilderDockWindow("Learned Moves", TabDockspaceID);

	//// Evolution info goes in the bottom region, below the level up moves.
	//// We dock this first so that it docks above the left/right regions.
	//ImGui::DockBuilderDockWindow("Evolution Info", DockDown);

	//// Species info goes in the top half of the left region.
	//ImGui::DockBuilderDockWindow("Species Info", DockLeft);

	//// Taught moves goes in the right region.
	//ImGui::DockBuilderDockWindow("TMs, HMs, and Tutor Moves", DockRight);

	//// Base stats goes in the top region, but is below the left/right regions
	//// because we docked it after them.
	//ImGui::DockBuilderDockWindow("Base Stats", DockUp);

	//// The Pok�mon list goes in the bottom half of the left region.
	//ImGui::DockBuilderDockWindow("Pok�mon List", ListDockspaceID);

	//ImGui::DockBuilderFinish(TabDockspaceID);
}