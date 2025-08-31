#include "include.h"
#include "CSV/CSVDatabase.h"
#include "CSV/NewCSVData.h"
#include "CSV/CSVLoader.h"

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

void CSVDatabase::LoadAllCSVFiles()
{
    for (auto& [Key, CSVFile] : CSVDatabaseMap)
    {
        CSVFile->Init();
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
