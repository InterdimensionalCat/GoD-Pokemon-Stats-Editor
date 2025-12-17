#include "include.h"
#include "UI/UiElement/UiCSVElement/StringElement/CSVIntHexComboBox.h"
#include "UI/UiComponent/StringComponent/ComboBox.h"

#include "CSV/StringTypes/EntryNameString.h"
#include "CSV/StringTypes/ParenthValueString.h"
#include "CSV/StringTypes/IntHexParenthValue.h"

CSVIntHexComboBox::CSVIntHexComboBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName,
	const std::string& InEntriesListCSVFileName,
	const std::string& InEntriesListColumnName
) :
	UiBasicCSVElement<std::string>(InName, InParent, InCSVFileName, InColumnName),
	ComboBoxComponent(std::make_shared<ComboBox>(InName, this)),
	EntriesListCSVFileName(InEntriesListCSVFileName),
	EntriesListColumnName(InEntriesListColumnName)
{
	SetUiComponent(ComboBoxComponent);
	UpdateEntriesList();
}

CSVIntHexComboBox::CSVIntHexComboBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InEntriesListCSVFileName,
	const std::string& InEntriesListColumnName
) :
	CSVIntHexComboBox(
		InName,
		InParent,
		InCSVFileName,
		InName,
		InEntriesListCSVFileName,
		InEntriesListColumnName)
{

}

void CSVIntHexComboBox::Refresh()
{
	// Reload the entries list from the column this pulls entries from.
	UpdateEntriesList();

	// Refresh the current value this combo box manages.
	UiBasicCSVElement::Refresh();
	IntHexParenthValue ManagedValueIntHex = IntHexParenthValue(GetManagedValue());
	int32_t ManagedIntVal = ManagedValueIntHex.GetValueAsInt();

	// Get all entries as ParenthValueStrings.
	const auto& EntriesList = ComboBoxComponent->GetEntriesList();

	std::vector<ParenthValueString> EntriesAsParenthValues;
	EntriesAsParenthValues.reserve(EntriesList.size());

	for (auto Entry : EntriesList)
	{
		EntriesAsParenthValues.push_back(ParenthValueString(Entry));
	}

	// Find the ParenthValueString whose value matches the int value of the managed value.
	auto EntryMatchingIntItr = std::find_if(
	EntriesAsParenthValues.begin(), 
	EntriesAsParenthValues.end(),
		[ManagedIntVal](const ParenthValueString& Entry)
		{
			return Entry.GetValue() == std::format("{}", ManagedIntVal);
		}
	);

	// If we found a matching entry, set it as the selected entry.
	if (EntryMatchingIntItr != EntriesAsParenthValues.end())
	{
		ComboBoxComponent->SetSelectedEntry(std::distance(EntriesAsParenthValues.begin(), EntryMatchingIntItr));
	}
	else
	{
		ICLogger::Warn
		(
			"CSVIntHexComboBox::Refresh failed to find the current value of Columm:{} Row:{} CSV:{}.csv in the entries list, value set to the first option",
			GetColumnName(),
			GetCurrentRow(),
			GetCSVFileName()
		);
		ComboBoxComponent->SetSelectedEntry(0);
	}
}

void CSVIntHexComboBox::UiComponentUpdated()
{
	const auto& EntriesList = ComboBoxComponent->GetEntriesList();

	std::vector<ParenthValueString> EntriesAsParenthValues;
	EntriesAsParenthValues.reserve(EntriesList.size());

	for (auto Entry : EntriesList)
	{
		EntriesAsParenthValues.push_back(ParenthValueString(Entry));
	}

	IntHexParenthValue NewValue = IntHexParenthValue(stoi(EntriesAsParenthValues.at(GetSelectedEntry()).GetValue()));
	SetManagedValue(NewValue.GetParenthValueString());
}

uint32_t CSVIntHexComboBox::GetSelectedEntry() const
{
	return ComboBoxComponent->GetSelectedEntry();
}

void CSVIntHexComboBox::UpdateEntriesList()
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
			Entry = EntryName.ToParenthValueString().GetParenthValueString();
		}
	}

	ComboBoxComponent->SetEntriesList(NewEntriesList);
}