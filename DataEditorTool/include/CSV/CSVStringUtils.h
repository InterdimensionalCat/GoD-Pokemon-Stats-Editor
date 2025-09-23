//#pragma once
//
//namespace GoDCSV
//{
//	class CSVStringUtils
//	{
//
//	public:
//
//		CSVStringUtils() = default;
//
//		/** Create a string wth the format "{EntryName} - {NumString}" from the supplied strings. */
//		static std::string CreateEntryNameFromStrings(const std::string& EntryName, const std::string& NumString);
//
//		/** Create a string wth the format "{String} ({ValueString})" from the supplied strings. */
//		static std::string CreateParenthValueFromStrings(const std::string& String, const std::string& ValueString);
//
//		/**
//		 * Convert a string with the format "{EntryName} - {Num}" to a string with the format
//		 * "{String} ({Value})" where {EntryName} is the String and {Num} is the Value. If
//		 * the EntryName is quoted, trim those quotes from the converted name.
//		 * For example, the string ""BULBASAUR"  - 1" would become "BULBASAUR (1)"
//		 */
//		static std::string ConvertEntryNameToParenthValue(const std::string& EntryNameString);
//
//		/**
//		 * Convert a string with the format "{String} ({Value})" to a string with the format
//		 * "{EntryName} - {Num}" where {String} is the Entry Name and {Value} is the Num.
//		 * For example, the string "BULBASAUR (1)" would become "BULBASAUR - 1"
//		 */
//		static std::string ConvertParenthValueToEntryName(const std::string& ParenthValueString);
//
//		/**
//		 * Break up a string with the format "{String} ({Value})" into separate strings.
//		 * For example: the string ""SANDSLASH" (0x404)" would be broken up into
//		 * ""SANDSLASH"" and "0x404".
//		 */
//		static std::pair<std::string, std::string> BreakUpParenthValueString(const std::string& StringWithParenthValue);
//
//
//
//		/**
//		* Break up a string with the format "{EntryName} - {Num}" into separate strings.
//		* For example: the string ""BULBASAUR"  - 1" would be broken up into
//		* ""BULBASAUR"" and "1"
//		*/
//		static std::pair<std::string, std::string> BreakEntryNameString(const std::string& EntryNameString);
//	};
//}
