#include "include.h"

#include "CSVData/Types.h"
#include "GoD-UI-Windows.h"

using namespace csv;

PokemonTypesCSV::PokemonTypesCSV()
{
	Path = GoDUIWindowsInstance::instance.GetProjectRootPath();

	Path /= "Reference";
	Path /= "CSV Data";
	Path /= "Type.csv";
}

std::vector<std::string> PokemonTypesCSV::GetTypesList()
{
	return TypesList;
}

bool PokemonTypesCSV::Init()
{
	if (CSVData::Init())
	{
		// Create types list.
		try
		{
			TypesList = GetAllEntriesOfKey("Entry Name", true);
		}
		catch (std::exception e)
		{
			std::cout << "Error Generating Pokemon list: " << e.what() << "\n";
			return false;
		}

		return true;
	}
	return false;
}
