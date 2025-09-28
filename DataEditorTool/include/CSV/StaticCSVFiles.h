#pragma once

class ParenthValueString;

namespace GoDCSV
{
	class StaticCSVFiles
	{

		// TODO: Just make this a struct.
		using LoadedCSVData = std::pair<std::vector<std::string>, std::vector<json>>;

	public:

		static LoadedCSVData LoadLevelUpRateDatabase();

		static LoadedCSVData LoadGenderRatioDatabase();

		static LoadedCSVData LoadEvolutionMethodDatabase();

		static LoadedCSVData LoadEvolutionStoneDatabase();

		static LoadedCSVData LoadKeyItemDatabase();

		static LoadedCSVData CreateLoadedDataFromParenthValueList(const std::vector<ParenthValueString>& InEntries, const std::string& ValueColumnName);

	};
}

