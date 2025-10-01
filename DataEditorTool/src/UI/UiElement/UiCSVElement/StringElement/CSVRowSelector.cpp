#include "include.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVRowSelector.h"

#include "UI/UiComponent/StringComponent/ListBox.h"
#include "CSV/CSVDatabase.h"
#include "CSV/NewCSVData.h"
#include "UI/TabCSVState.h"

CSVRowSelector::CSVRowSelector
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName
) :
	UiCSVElement(InName, InParent, InCSVFileName, InColumnName),
	ListBoxComponent(std::make_shared<ListBox>(InName, this))
{
	SetUiComponent(ListBoxComponent);
	UpdateEntriesList();
}

void CSVRowSelector::Refresh()
{
	UpdateEntriesList();
}

void CSVRowSelector::UiComponentUpdated()
{
	GetTabState()->SetCurrentRow(GetSelectedEntry());
}

uint32_t CSVRowSelector::GetSelectedEntry() const
{
	return ListBoxComponent->GetSelectedEntry();
}

void CSVRowSelector::UpdateEntriesList()
{
	// Reload the entries list from the column this pulls entries from.
	const auto& CSVDatabase = GoDCSV::CSVDatabase::Get();

	auto NewEntriesList = CSVDatabase->GetCSVFile(GetCSVFileName())->GetStringColumn(GetColumnName());
	ListBoxComponent->SetEntriesList(NewEntriesList);
}