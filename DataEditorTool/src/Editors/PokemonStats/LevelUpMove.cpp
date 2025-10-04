#include "include.h"
#include "Editors/PokemonStats/LevelUpMove.h"
#include "Editors/PokemonStats/PokemonStatsLearnedMoves.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVComboBox.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntBox.h"
#include "UI/UiElement/UiSimpleElement/StaticElement/SimpleDragDropButton.h"
#include "UI/UiSize/UiSize.h"
#include "UI/UiSize/UiConstrainedSize.h"

LevelUpMove::LevelUpMove(
	const std::string& InName,
	PokemonStatsLearnedMoves* InParent,
	int32_t InLevelUpMoveNumber
) :
	UiSingleLineMultiElement(InName, InParent),
	ParentLearnedMoves(InParent),
	LevelUpMoveIndex(static_cast<int32_t>(InLevelUpMoveNumber - 1))
{
	const std::string CSVName = "Pokemon Stats";

	const std::string MoveComboBoxColumn = std::format("Level Up Moves {} Move", InLevelUpMoveNumber);
	const std::string LevelIntBoxColumn = std::format("Level Up Moves {} Level", InLevelUpMoveNumber);
	const std::string SwapMoves = std::format("##SwapMoves-{}", LevelUpMoveIndex);

	DragDrop = std::make_shared<SimpleDragDropButton<int32_t>>(SwapMoves, InParent, LevelUpMoveIndex, "LevelUpMovesSwap");

	MoveComboBox = std::make_shared<CSVComboBox>("##" + MoveComboBoxColumn, ParentLearnedMoves, CSVName, MoveComboBoxColumn, "Move", "Entry Name");

	LevelIntBox = std::make_shared<CSVIntBox>("##" + LevelIntBoxColumn, ParentLearnedMoves, CSVName, LevelIntBoxColumn, 1, 5);

	LevelIntBox->SetElementMinSize(3);
	LevelIntBox->SetIsFixedSize(true);

	LevelIntBox->SetBounds(0, 100);

	AddElement(DragDrop);
	AddElement(MoveComboBox);
	AddElement(LevelIntBox);
}

void LevelUpMove::Tick()
{
	// Set the drag/drop text before showing the level up moves data on this line
	DragDrop->SetDragDropPreviewText(std::format("Reorder Move {}", MoveComboBox->GetManagedValue()));
	const ImVec2 ButtonStartPos = ImGui::GetCursorPos();

	UiSingleLineMultiElement::Tick();

	// Render an invisible button on top of the level up moves as a dummy target for the 
	// drag/drop button
	ImGui::SetCursorPos(ButtonStartPos);
	std::string InvisButtonName = std::format("{}-SwapMoveInvis", GetInvisibleName());
	ImGui::InvisibleButton(
		InvisButtonName.c_str(),
		ImVec2(ConstrainedSize->GetConstrainedSize(), ImGui::GetFrameHeight()),
		0);

	//ImGui::DebugDrawItemRect();

	// Rotate elements based on the dragged element if a drag/drop was completed
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("LevelUpMovesSwap"))
		{
			IM_ASSERT(Payload->DataSize == sizeof(int32_t));
			const int32_t MovedElementIndex = *(const int32_t*)Payload->Data;
			const int32_t MoveToElementIndex = LevelUpMoveIndex;

			const auto& LevelUpMoves = ParentLearnedMoves->GetLevelUpMoves();
			std::vector<std::pair<std::string, int32_t>> LevelUpMovesData;
			LevelUpMovesData.reserve(LevelUpMoves.size());

			for (const auto LevelUpMove : LevelUpMoves)
			{
				LevelUpMovesData.push_back(
					{ LevelUpMove->MoveComboBox->GetManagedValue(), LevelUpMove->LevelIntBox->GetManagedValue() }
				);
			}

			if (MovedElementIndex != MoveToElementIndex)
			{
				if (MovedElementIndex < MoveToElementIndex)
				{
					// Case 1: Move was reordered to a higher slot, in this case we
					// rotate everything in between down (or to the right in the array)
					std::rotate(
						LevelUpMovesData.begin() + MovedElementIndex,
						LevelUpMovesData.begin() + MovedElementIndex + 1,
						LevelUpMovesData.begin() + MoveToElementIndex + 1
					);
				}

				if (MovedElementIndex > MoveToElementIndex)
				{
					// Case 2: Move was reordered to a lower slot, in this cas we
					// rotate everything in between up (or to the left in the array)
					std::rotate(
						LevelUpMovesData.begin() + MoveToElementIndex,
						LevelUpMovesData.begin() + MovedElementIndex,
						LevelUpMovesData.begin() + MovedElementIndex + 1
					);
				}

				// Update each Level Up Move to reflect the shift.
				for (int32_t Index = 0; Index < LevelUpMovesData.size(); Index++)
				{
					auto LevelUpToModify = ParentLearnedMoves->GetLevelUpMoveAtIndex(Index);
					LevelUpToModify->MoveComboBox->SetManagedValue(LevelUpMovesData.at(Index).first);
					LevelUpToModify->LevelIntBox->SetManagedValue(LevelUpMovesData.at(Index).second);
				}
			}
		}
		ImGui::EndDragDropTarget();
	}
}
