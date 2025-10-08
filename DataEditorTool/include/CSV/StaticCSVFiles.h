/*****************************************************************//**
 * \file   StaticCSVFiles.h
 * \brief  Class containing functions to load static, pre-defined CSV files
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

class ParenthValueString;

namespace GoDCSV
{
	/** \brief  Class containing functions to load static, pre-defined CSV files */
	class StaticCSVFiles
	{

		// TODO: Just make this a struct.
		using LoadedCSVData = std::pair<std::vector<std::string>, std::vector<json>>;

	public:

		/**
		 * Load the hard-coded LevelUpRate database.
		 */
		static LoadedCSVData LoadLevelUpRateDatabase();

		/**
		 * Load the hard-coded GenderRatio database.
		 */
		static LoadedCSVData LoadGenderRatioDatabase();

		/**
		 * Load the hard-coded EvolutionMethod database.
		 */
		static LoadedCSVData LoadEvolutionMethodDatabase();

		/**
		 * Load the hard-coded EvolutionStone database.
		 */
		static LoadedCSVData LoadEvolutionStoneDatabase();

		/**
		 * Load the hard-coded KeyItem database.
		 */
		static LoadedCSVData LoadKeyItemDatabase();

	private:

		/**
		 * Create a LoadedCSVData object from a list of ParenthValueStrings.
		 * The ValueColumnName parameter specifies the name of the column
		 * that will contain the each ParenthValueString. The ParenthValueString
		 * will also be converted to an EntryNameString and placed in the
		 * "Entry Name" column.
		 */
		static LoadedCSVData CreateLoadedDataFromParenthValueList(const std::vector<ParenthValueString>& InEntries, const std::string& ValueColumnName);

	};
}

