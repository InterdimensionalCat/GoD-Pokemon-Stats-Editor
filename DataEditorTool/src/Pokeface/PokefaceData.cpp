#include "include.h"
#include "Pokeface/PokefaceData.h"

#include "CSV/CSVDatabase.h"
#include "CSV/CSVData.h"
#include "Util/TextureLoader.h"

typedef unsigned int GLuint;

std::deque<GLuint> PokefaceData::PokefaceTextureIds;

bool PokefaceData::bPokefaceDataLoaded = false;

bool PokefaceData::bPokefaceDataLoadingFailed = false;

const std::deque<PokefaceData::GLuint>& PokefaceData::GetPokefaceData()
{
	if(bPokefaceDataLoaded == false && bPokefaceDataLoadingFailed == false)
	{
		InitPokefaceData();
	}

	return PokefaceTextureIds;
}

void PokefaceData::InitPokefaceData()
{
	// TODO: Allow Pokeface data to load if some Pokeface files are missing,
	// which will be needed to support custom Pokemon additions to the Pokemon Stats.csv file

	if (bPokefaceDataLoaded)
	{
		// Pokeface data is already loaded, no need to load it again.
		ICLogger::Info("Pokeface data already loaded, skipping load.");
		return;
	}

	try
	{
		ICLogger::Debug("Attempting to load Pokeface data.");
		PokefaceTextureIds.clear();
		// Attempt to find the Pokeface resource dir, which should be at
		// "{ToolPath}/Resources/PokeFace/"
		std::filesystem::path BasePath = std::filesystem::current_path();
		BasePath /= "Resources";
		BasePath /= "PokeFace";

		if (!std::filesystem::is_directory(BasePath))
		{
			// If the Pokeface directory is not found throw an error
			std::string ErrorMessage = std::format("{} is not a directory", BasePath.string());
			throw std::exception(ErrorMessage.c_str());
			return;
		}

		// Get the list of Pokemon, which we can convert into Pokeface data file names
		auto PokemonStatsCSV = GoDCSV::CSVDatabase::Get()->GetCSVFile("Pokemon Stats");
		auto PokemonList = PokemonStatsCSV->GetStringColumn("Entry Name");

		// Resize the PokefaceData list to be the same size as PokemonList, since
		// we will need to set texture ids to the index directly.
		PokefaceTextureIds = std::deque<GLuint>(PokemonList.size(), 0);

		// Attempt to load a Pokeface data file for each Pokemon list entry.
		for (uint32_t Index = 0; Index < PokemonList.size(); Index++)
		{
			// Get the PokeFace file name, it will be of the format
			// "face_{3 digit int}.png"
			// Example: "face_002.png" is Ivysaur's Pokeface.
			const std::string FileName = std::format("face_{:03}.png", Index);

			std::filesystem::path PathToFace = BasePath / FileName;
			if (!std::filesystem::exists(PathToFace))
			{
				// If the Pokeface file doesn't exist, throw an error and stop loading
				std::string ErrorMessage = std::format("Pokeface file {} not found", FileName);
				throw std::exception(ErrorMessage.c_str());
				return;
			}

			int Width = 0;
			int Height = 0;

			// Attempt to load the Pokeface image file, its Width/Height will be stored in the supplied
			// Width and height variables.
			bool Success = LoadTextureFromFile(PathToFace.string().c_str(), &PokefaceTextureIds.at(Index), &Width, &Height);
			if (Success)
			{
				ICLogger::Trace("Successfully loaded Pokeface image {}", FileName);
			}
			else
			{
				std::string ErrorMessage = std::format("Error loading Pokeface image {}, is this a valid image file?", FileName);
				throw std::exception(ErrorMessage.c_str());
				break;
			}
		}

		bPokefaceDataLoaded = true;
		ICLogger::Debug("Pokeface data loading successful!");
	}
	catch (const std::exception& e)
	{
		PokefaceTextureIds.clear();
		ICLogger::PushErrorNotification("Pokeface data will not be displayed", 10000, "Error Loading Pokeface data: {}", e.what());
		bPokefaceDataLoadingFailed = true;
	}
}