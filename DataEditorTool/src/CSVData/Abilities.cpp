#include "include.h"

#include "CSVData/Abilities.h"
#include "GoD-UI-Windows.h"

using namespace csv;

PokemonAbilitiesCSV::PokemonAbilitiesCSV()
{
	Path = GoDUIWindowsInstance::instance.GetProjectRootPath();

	Path /= "Reference";
	Path /= "CSV Data";
	Path /= "Ability.csv";
}

std::vector<std::string> PokemonAbilitiesCSV::GetAbilitiesList()
{
	return AbilitiesList;
}

bool PokemonAbilitiesCSV::Init()
{
	if (CSVData::Init())
	{
		// Create abilities list.
		try
		{
			AbilitiesList = GetAllEntriesOfKey("Entry Name", true);
		}
		catch (std::exception e)
		{
			std::cout << "Error Generating Abilities list: " << e.what() << "\n";
			return false;
		}

		return true;
	}
	return false;
}
