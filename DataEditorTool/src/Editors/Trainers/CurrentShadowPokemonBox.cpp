#include "include.h"
#include "Editors/Trainers/CurrentShadowPokemonBox.h"
#include "UI/UiComponent/StringComponent/ComboBox.h"

#include "CSV/StringTypes/EntryNameString.h"
#include "CSV/StringTypes/ParenthValueString.h"
#include "CSV/StringTypes/IntHexParenthValue.h"

CurrentShadowPokemonBox::CurrentShadowPokemonBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName
) : CSVIntHexComboBox(InName, InParent, InCSVFileName, InColumnName, "Shadow Pokemon", "Entry Name")
{

}

void CurrentShadowPokemonBox::UpdateEntriesList()
{
	// Reload the entries list from the column this pulls entries from.
	const auto& CSVDatabase = GoDCSV::CSVDatabase::Get();

	auto NewEntriesList = CSVDatabase->GetCSVFile(EntriesListCSVFileName)->GetStringColumn(EntriesListColumnName);
	auto PokemonIndexList = CSVDatabase->GetCSVFile(EntriesListCSVFileName)->GetStringColumn("Pokemon Index In Story Deck");

	if (EntriesListColumnName == "Entry Name")
	{
		// We need to convert from an EntryNameString to a ParenthValueString if
		// this was an Entry Name column.

		int32_t PokemonListIndex = 0;
		for (auto& Entry : NewEntriesList)
		{
			EntryNameString EntryName = EntryNameString(Entry);
			ParenthValueString PokemonIDString = ParenthValueString(PokemonIndexList.at(PokemonListIndex));

			Entry = EntryNameString(PokemonIDString.GetString(), EntryName.GetEntryNum()).ToParenthValueString().GetParenthValueString();
			PokemonListIndex++;
		}
	}

	ComboBoxComponent->SetEntriesList(NewEntriesList);
}