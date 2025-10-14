#include "include.h"
#include "UI/UiElement/UiMultiElement/UiTable.h"

#include "UI/UiSize/UiSize.h"

UiTable::UiTable(const std::string& InName, UiSection* InParent) :
	UiMultiElement(InName, InParent)
{
	TableSize = std::make_shared<UiSize>();
}

void UiTable::Tick()
{
	static ImGuiTableFlags TableFlags =
		ImGuiTableFlags_SizingFixedFit |
		ImGuiTableFlags_ScrollX |
		ImGuiTableFlags_ScrollY |
		ImGuiTableFlags_BordersOuter |
		ImGuiTableFlags_BordersInnerH |
		ImGuiTableFlags_Hideable |
		ImGuiTableFlags_HighlightHoveredColumn;

	static ImGuiTableColumnFlags ColumnFlags =
		ImGuiTableColumnFlags_AngledHeader |
		ImGuiTableColumnFlags_WidthFixed;

	if (ImGui::BeginTable(GetName().c_str(), ColumnNames.size(), TableFlags, ImVec2(0.0f, 0.0f)))
	{
		auto CurrentTable = ImGui::GetCurrentTable();

		// Set up header columns.
		ImGui::TableSetupColumn(ColumnNames.at(0).c_str(), ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoReorder);

		for (int32_t Index = 1; Index < ColumnNames.size(); Index++)
		{
			ImGui::TableSetupColumn(ColumnNames.at(Index).c_str(), ColumnFlags);
		}

		ImGui::TableSetupScrollFreeze(1, 2);

		ImGui::TableAngledHeadersRow(); // Draw angled headers for all columns with the ImGuiTableColumnFlags_AngledHeader flag.
		ImGui::TableHeadersRow();       // Draw remaining headers and allow access to context-menu and other functions.
		
		// Display rows, but clip any rows that shouldn't be visible.
		ImGuiListClipper Clipper;
		Clipper.Begin(TableColumns.at(0).size(), ImGui::GetFrameHeightWithSpacing());

		while (Clipper.Step())
		{
			for (int32_t RowIndex = Clipper.DisplayStart; RowIndex < Clipper.DisplayEnd; RowIndex++)
			{
				ImGui::TableNextRow(0, ImGui::GetFrameHeightWithSpacing());
				ImGui::AlignTextToFramePadding();

				bool bHovered = false;

				auto RowRect = ImRect(CurrentTable->WorkRect.Min.x,
					CurrentTable->RowPosY1,
					CurrentTable->WorkRect.Max.x,
					CurrentTable->RowPosY2);

				RowRect.ClipWith(CurrentTable->BgClipRect);

				bHovered |= (ImGui::IsMouseHoveringRect(RowRect.Min, RowRect.Max, false));

				for (int32_t ColumnIndex = 0; ColumnIndex < TableColumns.size(); ColumnIndex++)
				{
					ImGui::TableSetColumnIndex(ColumnIndex);
					TableColumns.at(ColumnIndex).at(RowIndex)->Tick();
					if (bHovered && ColumnIndex == 0)
					{
						ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImGuiCol_HeaderHovered));
					}
				}
			}
		}

		ImGui::EndTable();
	}
}

std::shared_ptr<const UiSize> UiTable::GetSizeConstraints() const
{
	return TableSize;
}

void UiTable::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	TableColumns.back().push_back(NewElement);
	UiElements.push_back(NewElement);
}

void UiTable::AddNewColumn(const std::string& ColumnName)
{
	TableColumns.emplace_back();
	ColumnNames.push_back(ColumnName);
}