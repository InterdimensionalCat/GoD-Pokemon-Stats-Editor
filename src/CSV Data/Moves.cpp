#include "Moves.h"
#include "GoD-UI-Windows.h"
#include <filesystem>

using namespace csv;

PokemonMovesCSV::PokemonMovesCSV()
{
	Path = GoDUIWindowsInstance::instance.GetProjectRootPath();

	Path /= "Reference";
	Path /= "CSV Data";
	Path /= "Move.csv";
}

std::vector<std::string> PokemonMovesCSV::GetMovesList()
{
	return MovesList;
}

bool PokemonMovesCSV::Init()
{
	if (CSVData::Init())
	{
		// Create Moves list.
		try
		{
			MovesList = GetAllEntriesOfKey("Entry Name", true);
		}
		catch (std::exception e)
		{
			std::cout << "Error Generating Moves list: " << e.what() << "\n";
			return false;
		}

		return true;
	}
	return false;
}
