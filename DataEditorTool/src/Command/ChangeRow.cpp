#include "include.h"
#include "Command/ChangeRow.h"

#include "UI/TabCSVState.h"

ChangeRow::ChangeRow(
	TabCSVState* InTabState,
	const int32_t InNewRow
) :
	TabState(InTabState),
	NewRow(InNewRow)
{
	PrevRow = TabState->GetCurrentRow();
}

void ChangeRow::Execute()
{
	TabState->SetCurrentRow(NewRow);
}

void ChangeRow::Undo()
{
	TabState->SetCurrentRow(PrevRow);
}

void ChangeRow::Redo()
{
	Execute();
}

std::string ChangeRow::GetName() const
{
	return "Change Row";
}

std::string ChangeRow::ToString() const
{
	return std::format("ChangeRow: {} -> {}", PrevRow, NewRow);
}