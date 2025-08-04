#include "include.h"

#include "CSVData/Items.h"
#include "GoD-UI-Windows.h"

using namespace csv;

PokemonItemsCSV::PokemonItemsCSV()
{
	Path = GoDUIWindowsInstance::instance.GetProjectRootPath();

	Path /= "Reference";
	Path /= "CSV Data";
	Path /= "Item.csv";
}

std::vector<std::string> PokemonItemsCSV::GetItemsList()
{
	return ItemsList;
}

bool PokemonItemsCSV::Init()
{
	if (CSVData::Init())
	{
		// Create Items list.
		try
		{
			ItemsList = GetAllEntriesOfKey("Entry Name", true);
		}
		catch (std::exception e)
		{
			std::cout << "Error Generating Items list: " << e.what() << "\n";
			return false;
		}

		return true;
	}
	return false;
}
