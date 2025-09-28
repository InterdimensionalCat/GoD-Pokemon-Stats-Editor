#include "include.h"
#include "CSV/CSVDatabase.h"
#include "CSV/NewCSVData.h"
#include "CSV/CSVLoader.h"
#include "CSV/StaticCSVFiles.h"

using namespace GoDCSV;

void CSVDatabase::OnProjectRootPathSet()
{

    // First clear the database in case a previous project root was set
    ClearDatabase();

	fs::path CSVFileDir = CSVLoader::GetCSVFileDir();

    if (!fs::exists(CSVFileDir)) 
    {
        throw std::runtime_error(std::format("CSV directory {} not found", CSVFileDir.string()));
    }

    for (const auto& File : fs::directory_iterator(CSVFileDir)) 
    {
        // Check that this file is actually a file, not a dir or OS specific thing.
        if (fs::is_regular_file(File.status()))
        {
            if (File.path().extension() == ".csv")
            {
                // If this is a file with the ".csv" extension, add it to the database
                std::string FileName = File.path().stem().string();
                ICLogger::Debug("Found CSV file: {}.csv", FileName);
                CSVDatabaseMap.emplace(FileName, std::make_shared<NewCSVData>(FileName));
            }
        }
    }

    LoadStaticDatabases();
}

void CSVDatabase::LoadStaticDatabases()
{
    // TODO: check for CSV files with this name in the root and use those instead

	// Load LevelUpRate database.
	const auto LevelUpRateData = StaticCSVFiles::LoadLevelUpRateDatabase();
	CSVDatabaseMap.emplace("LevelUpRate", std::make_shared<NewCSVData>("LevelUpRate"));
	CSVDatabaseMap.at("LevelUpRate")->InitFromLoadedData(LevelUpRateData);

	// Load GenderRatio database.
	const auto GenderRatioData = StaticCSVFiles::LoadGenderRatioDatabase();
	CSVDatabaseMap.emplace("GenderRatio", std::make_shared<NewCSVData>("GenderRatio"));
	CSVDatabaseMap.at("GenderRatio")->InitFromLoadedData(GenderRatioData);

	// Load EvolutionMethod database.
	const auto EvolutionMethodData = StaticCSVFiles::LoadEvolutionMethodDatabase();
	CSVDatabaseMap.emplace("EvolutionMethod", std::make_shared<NewCSVData>("EvolutionMethod"));
	CSVDatabaseMap.at("EvolutionMethod")->InitFromLoadedData(EvolutionMethodData);

	// Load EvolutionStone database.
	const auto EvolutionStoneData = StaticCSVFiles::LoadEvolutionStoneDatabase();
	CSVDatabaseMap.emplace("EvolutionStone", std::make_shared<NewCSVData>("EvolutionStone"));
	CSVDatabaseMap.at("EvolutionStone")->InitFromLoadedData(EvolutionStoneData);

	// Load KeyItem database.
	const auto KeyItemData = StaticCSVFiles::LoadKeyItemDatabase();
	CSVDatabaseMap.emplace("KeyItem", std::make_shared<NewCSVData>("KeyItem"));
	CSVDatabaseMap.at("KeyItem")->InitFromLoadedData(KeyItemData);
}

std::shared_ptr<GoDCSV::NewCSVData> CSVDatabase::GetCSVFile(const std::string& CSVFileName)
{
	return CSVDatabaseMap.at(CSVFileName);
}

bool CSVDatabase::RootContainsAllCSVFiles(const std::vector<std::string>& CSVFileNames) const
{
    bool bContainsAllFiles = true;
    for (const std::string& CSVFileName : CSVFileNames)
    {
        // Check that the database map contains every file in the supplied
        // filenames vector.
        bContainsAllFiles &= CSVDatabaseMap.contains(CSVFileName);

        if (!bContainsAllFiles)
        {
            break;
        }
    }

    return bContainsAllFiles;
}

std::vector<std::string> GoDCSV::CSVDatabase::GetAllModifiedCSVFileNames()
{
    std::vector<std::string> ModifiedCSVFileNames;
    for (auto& [Key, CSVFile] : CSVDatabaseMap)
    {
        if (CSVFile->HasCSVFileBeenModified())
        {
            ModifiedCSVFileNames.push_back(Key);
        }
    }

    return ModifiedCSVFileNames;
}

bool GoDCSV::CSVDatabase::AreAnyCSVFilesModified()
{

    for (auto& [Key, CSVFile] : CSVDatabaseMap)
    {
        if (CSVFile->HasCSVFileBeenModified())
        {
            return true;
        }
    }

    return false;
}

bool GoDCSV::CSVDatabase::IsCSVFileInDatabase(const std::string& CSVFileName) const
{
    return CSVDatabaseMap.find(CSVFileName) != CSVDatabaseMap.end();
}

std::vector<std::pair<std::string, std::string>> GoDCSV::CSVDatabase::SaveSelectedCSVFiles(const std::vector<std::string>& SelectedCSVFiles)
{
    std::vector<std::pair<std::string, std::string>> FailedFilesWithReasons;
    for (const std::string& FileName : SelectedCSVFiles)
    {
        try
        {
            // Can't save a CSV file that does not exist in the database.
            if (!CSVDatabaseMap.contains(FileName))
            {
                throw std::runtime_error(std::format("CSV file {}.csv does does not exist in this root", FileName));
            }

            // Attempt to save the CSV, this will throw if:
            // Saving fails
            // The CSV file is not loaded
            // The CSV file could not be found
            const auto FailureReason = CSVDatabaseMap.at(FileName)->Save();

            if (FailureReason != "")
            {
                throw std::runtime_error(FailureReason);
            }
        }
        catch (const std::exception& e)
        {
            // If saving a particular CSV file fails, then return that file name + why it failed.
            FailedFilesWithReasons.push_back({ FileName, e.what() });
        }
    }

    // This should be an empty vector. If it isn't, some CSV files failed to save.
    return FailedFilesWithReasons;
}

std::vector<std::pair<std::string, std::string>> GoDCSV::CSVDatabase::SaveAllModifiedCSVFiles()
{
    const auto ModifiedCSVFiles = GetAllModifiedCSVFileNames();
    return SaveSelectedCSVFiles(ModifiedCSVFiles);
}

void GoDCSV::CSVDatabase::ClearDatabase()
{
    CSVDatabaseMap.clear();
}

void GoDCSV::CSVDatabase::LoadCSVFile(const std::string& CSVFileName)
{
    auto CSVFile = CSVDatabaseMap.at(CSVFileName);

    if (!CSVFile->IsCSVFileLoaded())
    {
		try
		{
			CSVFile->Init();
		}
		catch (const std::exception& e)
		{
			ICLogger::PushErrorNotification(
				"CSV file loading failed", 6000, "Loading CSV file {}.csv has failed: {}",
				CSVFile->GetName(),
				e.what());
		}

		if (CSVFile->IsCSVFileLoaded())
		{
			// Show a notification that this CSV file loaded correctly.
			ICLogger::PushInfoNotification(
				std::format("{}.csv Loaded Successfully", CSVFile->GetName()),
				6000,
				"CSV file {}.csv loaded successfully",
				CSVFile->GetName()
			);
            // TODO: Remove this
			// ColumnDatabase::LoadEntryNameDatabase(std::format("{}-EntriesList", CSVFileName), CSVFileName);
		}
    }
    else
    {
        ICLogger::Warn("Attempted to load already loaded csv file {}.csv", CSVFileName);
    }
}

void CSVDatabase::LoadCSVFileFromData(const std::string& CSVFileName, std::pair<std::vector<std::string>, std::vector<json>> LoadedData)
{
    if (!IsCSVFileInDatabase(CSVFileName))
    {
		CSVDatabaseMap.emplace(CSVFileName, std::make_shared<NewCSVData>(CSVFileName));
        ICLogger::Debug("Static CSV File {}.csv not found in database, creating a new database entry for it", CSVFileName);
    }

	auto CSVFile = CSVDatabaseMap.at(CSVFileName);

	if (!CSVFile->IsCSVFileLoaded())
	{
		try
		{
			CSVFile->InitFromLoadedData(LoadedData);
		}
		catch (const std::exception& e)
		{
            ICLogger::Error("Loading Static CSV file {}.csv has failed: {}", CSVFile->GetName(), e.what());
		}

		if (CSVFile->IsCSVFileLoaded())
		{
			ICLogger::Info("Static CSV file {}.csv loaded successfully", CSVFile->GetName());
            // TODO: Remove this
			//ColumnDatabase::LoadEntryNameDatabase(std::format("{}-EntriesList", CSVFileName), CSVFileName);
		}
	}
	else
	{
		ICLogger::Warn("Attempted to load already loaded csv file {}.csv", CSVFileName);
	}
}

void CSVDatabase::LoadAllCSVFiles()
{
    for (auto& [Key, CSVFile] : CSVDatabaseMap)
    {
        LoadCSVFile(Key);
    }
}

void GoDCSV::CSVDatabase::SaveAllCSVFiles()
{
    for (auto& [Key, CSVFile] : CSVDatabaseMap)
    {
        CSVFile->Save();
    }
}

std::map<std::string, std::shared_ptr<NewCSVData>>& GoDCSV::CSVDatabase::GetDatabaseMap()
{
    return CSVDatabaseMap;
}

std::shared_ptr<CSVDatabase> CSVDatabase::Get()
{
    return DataEditorInstance::Get()->GetCSVDatabase();
}
