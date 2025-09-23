#include "include.h"
#include "UI/UiCSVElement.h"

#include "UI/UiTab.h"
#include "UI/UiSection.h"
#include "UI/TabCSVState.h"

UiCSVElement::UiCSVElement(const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName
) :
	UiElement(InName, InParent),
	TabState(InParent->GetParent()->GetTabCSVState()),
	CSVFileName(InCSVFileName),
	ColumnName(InColumnName)
{

}

void UiCSVElement::SetCurrentRow(const int32_t NewCurrentRow)
{
	CurrentRow = NewCurrentRow;
}

void UiCSVElement::SetShouldSyncRowToCSVState(const bool bShouldSync)
{
	bShouldSyncRowToCSVState = bShouldSync;
}

std::string UiCSVElement::GetCSVFileName() const
{
	return CSVFileName;
}

std::string UiCSVElement::GetColumnName() const
{
	return ColumnName;
}

int32_t UiCSVElement::GetCurrentRow() const
{
	return CurrentRow;
}

bool UiCSVElement::ShouldSyncRowToCSVState() const
{
	return bShouldSyncRowToCSVState;
}

std::shared_ptr<TabCSVState> UiCSVElement::GetTabState()
{
	return TabState;
}