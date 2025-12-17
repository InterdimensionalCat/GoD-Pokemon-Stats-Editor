#include "include.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVComboBox.h"
#include "UI/UiComponent/StringComponent/ComboBox.h"

#include "CSV/StringTypes/EntryNameString.h"
#include "CSV/StringTypes/ParenthValueString.h"

CSVComboBox::CSVComboBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName,
	const std::string& InEntriesListCSVFileName,
	const std::string& InEntriesListColumnName
) :
	UiBasicCSVElement<std::string>(
		InName,
		InParent,
		InCSVFileName,
		InColumnName
	),
	ComboBoxComponent(std::make_shared<ComboBox>(InName, this)),
	EntriesListCSVFileName(InEntriesListCSVFileName),
	EntriesListColumnName(InEntriesListColumnName)
{
	SetUiComponent(ComboBoxComponent);
	UpdateEntriesList();
}

CSVComboBox::CSVComboBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InEntriesListCSVFileName,
	const std::string& InEntriesListColumnName
) :
	CSVComboBox(
		InName,
		InParent,
		InCSVFileName,
		InName,
		InEntriesListCSVFileName,
		InEntriesListColumnName
	)
{

}

void CSVComboBox::Refresh()
{
	// Reload the entries list from the column this pulls entries from.
	UpdateEntriesList();

	// Refresh the current value this combo box manages.
	UiBasicCSVElement::Refresh();
	auto ComboBoxStringVal = GetManagedValue();
	ParenthValueString ComboBoxStringParenthValue(ComboBoxStringVal);

	const auto& EntriesList = ComboBoxComponent->GetEntriesList();

	std::vector<ParenthValueString> EntriesAsParenthValues;

	for (auto& Entry : EntriesList)
	{
		EntriesAsParenthValues.push_back(ParenthValueString(Entry));
	}

	// Ensure the Selected entry index is up to date
	auto SelectedEntryItr = std::find_if(EntriesAsParenthValues.begin(), EntriesAsParenthValues.end(), [ComboBoxStringParenthValue](const ParenthValueString& Elt) {
		return Elt.GetValue() == ComboBoxStringParenthValue.GetValue();
		});

	if (SelectedEntryItr != EntriesAsParenthValues.end())
	{
		ComboBoxComponent->SetSelectedEntry(std::distance(EntriesAsParenthValues.begin(), SelectedEntryItr));
	}
	else
	{
		ICLogger::Warn
		(
			"CSVComboBox Refresh failed to find the current value of Columm:{} Row:{} CSV:{}.csv in the entries list, value set to the first option",
			GetColumnName(),
			GetCurrentRow(),
			GetCSVFileName()
		);

		ComboBoxComponent->SetSelectedEntry(0);
	}
}

void CSVComboBox::UiComponentUpdated()
{
	SetManagedValue(ComboBoxComponent->GetEntriesList().at(GetSelectedEntry()));
}

void CSVComboBox::SetSizeConstraintsDisabled(const bool bInDisableSizeConstraints)
{
	bDisableSizeConstraints = bInDisableSizeConstraints;
	UpdateEntriesList();
}

void CSVComboBox::SetStartWithCapitalLetter(const bool InStartWithCapitalLetter)
{
	ComboBoxComponent->SetStartWithCapitalLetter(InStartWithCapitalLetter);
}

void CSVComboBox::SetEntriesNumWhitespace(const int32_t InNumWhitespace)
{
	EntriesNumWhitespace = InNumWhitespace;
	UpdateEntriesList();
}

uint32_t CSVComboBox::GetSelectedEntry() const
{
	return ComboBoxComponent->GetSelectedEntry();
}

void CSVComboBox::UpdateEntriesList()
{
	// Reload the entries list from the column this pulls entries from.
	const auto& CSVDatabase = GoDCSV::CSVDatabase::Get();

	auto NewEntriesList = CSVDatabase->GetCSVFile(EntriesListCSVFileName)->GetStringColumn(EntriesListColumnName);

	if (EntriesListColumnName == "Entry Name")
	{
		// We need to convert from an EntryNameString to a ParenthValueString if
		// this was an Entry Name column.

		for (auto& Entry : NewEntriesList)
		{
			EntryNameString EntryName = EntryNameString(Entry);
			Entry = EntryName.ToParenthValueString(true, EntriesNumWhitespace).GetParenthValueString();
		}
	}

	ComboBoxComponent->SetEntriesList(NewEntriesList);

	if (bDisableSizeConstraints)
	{
		ComboBoxComponent->SetMinContentSizeFromStringLength(0);
	}
}