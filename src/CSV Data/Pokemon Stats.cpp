#include "Pokemon Stats.h"
#include "GoD-UI-Windows.h"
#include <filesystem>

using namespace csv;

PokemonStatsCSV::PokemonStatsCSV()
{
	Path = GoDUIWindowsInstance::instance.GetProjectRootPath();

	Path /= "Reference";
	Path /= "CSV Data";
	Path /= "Pokemon Stats.csv";
}

std::vector<std::string> PokemonStatsCSV::GetPokemonList()
{
	return PokemonList;
}

bool PokemonStatsCSV::CanPokemonLearn(uint32_t index, const std::string& key)
{
	// Although the TM/Tutor/HM headers can vary, they will always contain a substr. of TM0X, TMXX, HM0X, TutorMove0X, or TutorMoveXX
	auto RealKey = std::find_if(HeaderArray.begin(), HeaderArray.end(), [key] (const std::string& elt)
		{ return elt.find(key) != std::string::npos; }
	);
	return GetboolAtKeyAndIndex(index, *RealKey);
}

bool PokemonStatsCSV::Init()
{
	if (CSVData::Init())
	{
		// Create pokemon list.
		try
		{
			PokemonList = GetAllEntriesOfKey("Entry Name", false);
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

void PokemonStatsCSV::SaveCSV()
{
	std::filesystem::path Path = GoDUIWindowsInstance::instance.GetProjectRootPath();

	Path /= "Reference";
	Path /= "CSV Data";
	Path /= "Pokemon Stats.csv";

	std::ofstream CSVStream(Path);
	DelimWriter<std::ofstream, ',', '~', true> CSVWriter(CSVStream);

	if (CSVStream.fail())
	{
		throw std::exception("Error saving Pokemon Stats.csv file, do you have permission to write to this file?");
	}

	// First write the header array
	CSVWriter << HeaderArray;

	// Then write in each row
	for (int32_t i = 0; i < DataObject.size(); i++)
	{
		// The json data is stored in alphabetical order, not in key order, so we need to 
		// iterate through individual fields to put it back in order using the header array.
		std::shared_ptr<json> RowJsonData = DataObject.at(i);

		std::vector<std::string> RowFields;
		RowFields.reserve(HeaderArray.size());

		for (int32_t j = 0; j < HeaderArray.size(); j++)
		{
			const std::string FieldValueAtKey = (*RowJsonData)[HeaderArray.at(j)];
			//std::cout << FieldValueAtKey << "\n";
			RowFields.push_back(FieldValueAtKey);
		}

		CSVWriter << RowFields;
	}
}
