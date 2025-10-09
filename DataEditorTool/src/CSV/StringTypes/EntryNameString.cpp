#include "include.h"
#include "CSV/StringTypes/EntryNameString.h"
#include "CSV/StringTypes/ParenthValueString.h"

EntryNameString::EntryNameString(const std::string& InEntryNameString)
{
	// Find the last occurance of '-', as this is what separates the
	// EntryName and EntryValue strings.
	const size_t LastDash = InEntryNameString.rfind('-');

	// If '-' was not found or its the first/last character in the string, 
	// then this string is not in EntryName format
	if (LastDash == std::string::npos || 
		LastDash >= InEntryNameString.length() - 1 ||
		LastDash == 0)
	{
		ICLogger::Error("EntryName failed to construct, supplied string {} is not in EntryName form", InEntryNameString);
	}
	else
	{
		// Get the substring before '-', this is the EntryName string. 
		// For example, the string ""BULBASAUR"  - 1" will have an 
		// Entryname substring of ""BULBASAUR""

		// Substr includes the beginning character, but not the end character, so
		// the substring from the beginning of this string with a length of the pos
		// of LastDash will get us the EntryName string
		EntryName = InEntryNameString.substr(0, LastDash);

		// Get the substring after '-', this is the EntryNum string.
		// For example, the string ""BULBASAUR"  - 1" will have an
		// EntryNum substring of "1"

		// The length of the EntryNum string will be the length of the original string
		// Minus the pos of the first character in the substring, the first character
		// we want is one after the pos of '-', so we subtract one and LastDash from
		// the string length.
		const size_t EntryNumLength = (InEntryNameString.length() - 1) - LastDash;
		EntryNum = InEntryNameString.substr(LastDash + 1, EntryNumLength);

		// Both the EntryName and EntryValue will have whitspace at the end/beginning, respectively
		// We want to remove that whitespace and save the whitespace between the
		// EntryName substring and '-'
		const size_t LastCharBeforeEntryNameWhitespace = EntryName.find_last_not_of(' ');
		
		if (LastCharBeforeEntryNameWhitespace != std::string::npos)
		{
			// Set NumWhitespace equal to the amount of trailing whitespace in
			// the EntryName string
			NumWhitespace = (EntryName.length() - 1) - LastCharBeforeEntryNameWhitespace;
			EntryName.erase(LastCharBeforeEntryNameWhitespace + 1);
		}

		const size_t FirstCharAfterEntryNumWhitespace = EntryNum.find_first_not_of(' ');

		if (FirstCharAfterEntryNumWhitespace != 0)
		{
			EntryNum.erase(0, FirstCharAfterEntryNumWhitespace);
		}
	}
}

EntryNameString::EntryNameString(
	const std::string& InEntryName, 
	const std::string& InEntryNum, 
	const int32_t InNumWhitespace
) :
	EntryName(InEntryName), 
	EntryNum(InEntryNum), 
	NumWhitespace(InNumWhitespace)
{

}

void EntryNameString::SetEntryName(const std::string& InEntryName)
{
	EntryName = InEntryName;
}

void EntryNameString::SetEntryNum(const std::string& InEntryNum)
{
	EntryNum = InEntryNum;
}

std::string EntryNameString::GetEntryName() const
{
	return EntryName;
}

std::string EntryNameString::GetEntryNum() const
{
	return EntryNum;
}

std::string EntryNameString::GetEntryNameString() const
{
	const std::string WhitespaceString = std::string(NumWhitespace, ' ');
	return std::format("{}{}- {}", EntryName, WhitespaceString, EntryNum);
}

ParenthValueString EntryNameString::ToParenthValueString(const bool bRemoveQuotes) const
{
	if (bRemoveQuotes)
	{
		std::string EntryNameNoQuotes = EntryName;

		// Remove all occurances of '"' in the EntryName string
		EntryNameNoQuotes.erase(
			std::remove(EntryNameNoQuotes.begin(), EntryNameNoQuotes.end(), '"'), 
			EntryNameNoQuotes.end());

		return ParenthValueString(EntryNameNoQuotes, EntryNum);
	}
	else
	{
		return ParenthValueString(EntryName, EntryNum);
	}
}