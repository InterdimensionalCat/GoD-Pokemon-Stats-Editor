#include "include.h"
#include "UI/TabCSVState.h"

#include "UI/UiTab.h"
#include "UI/UiCSVElement.h"

TabCSVState::TabCSVState(UiTab* InParentTab) : ParentTab(InParentTab)
{

}

void TabCSVState::Tick()
{
	if (bShouldRefreshRow)
	{
		RefreshRow();
	}

	// TODO: Refactor this to work
	// the same way RefreshRow works
	if (bShouldRefreshTab)
	{
		ParentTab->Refresh();
		bShouldRefreshTab = false;
	}
}

void TabCSVState::RefreshRow()
{
	for (auto& Element : ElementsToUpdate)
	{
		if (Element->ShouldSyncRowToCSVState())
		{
			Element->SetCurrentRow(CurrentRow);
		}
	}

	RefreshTab();
	bShouldRefreshRow = false;
}

void TabCSVState::RefreshTab()
{
	bShouldRefreshTab = true;
}

void TabCSVState::AddElementToUpdate(std::shared_ptr<UiCSVElement> NewElement)
{
	ElementsToUpdate.push_back(NewElement);
	bShouldRefreshRow = true;
}

void TabCSVState::SetCurrentRow(const int32_t NewRowValue)
{
	CurrentRow = NewRowValue;
	bShouldRefreshRow = true;
}

int32_t TabCSVState::GetCurrentRow() const
{
	return CurrentRow;
}
