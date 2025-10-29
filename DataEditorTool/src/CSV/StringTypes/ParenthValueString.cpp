#include "include.h"
#include "CSV/StringTypes/ParenthValueString.h"

ParenthValueString::ParenthValueString(const std::string& InParenthValue)
{
	// Find the last occurances of '(' and ')', between these characters should
	// be the value string
	size_t LastOpenParenth = InParenthValue.rfind('(');
	size_t LastClosedParenth = InParenthValue.rfind(')');

	// If either '(' or ')' was not found, or if ')' was before '(' then this
	// string is not in ParenthValue format.
	if (LastOpenParenth == std::string::npos ||
		LastClosedParenth == std::string::npos ||
		LastClosedParenth < LastOpenParenth)
	{
		ICLogger::Error("ParenthValueString failed to construct, supplied string {} is not in ParenthValue form", InParenthValue);
	}
	else
	{
		// Get the substring inside '(' and ')', not including either character. 
		// This is the value string. For example, the string
		// ""SANDSLASH" (0x404)" will have a value substring of "0x404"
		// Substr includes the beginning character, but not the end character, so
		// we need to start one character after the position of '('
		size_t PosAfterOpenParenth = (LastOpenParenth + 1);
		size_t ValueSubstringSize = LastClosedParenth - PosAfterOpenParenth;
		Value = InParenthValue.substr(PosAfterOpenParenth, ValueSubstringSize);

		// The string field will then be everything before the pos of '(',
		// However we need to trim the whitespace between the String and the value
		String = InParenthValue.substr(0, LastOpenParenth);
		size_t LastCharBeforeWhitespace = String.find_last_not_of(' ');

		// If any whitespace was found, remove it
		if (LastCharBeforeWhitespace != std::string::npos)
		{
			NumWhitespace = (String.length() - 1) - LastCharBeforeWhitespace;
			String.erase(LastCharBeforeWhitespace + 1);
		}
	}
}

ParenthValueString::ParenthValueString(const std::string& InString, const std::string& InValue, int32_t InNumWhitespace) :
	String(InString),
	Value(InValue),
	NumWhitespace(InNumWhitespace)
{

}

void ParenthValueString::SetString(const std::string& InNewString)
{
	String = InNewString;
}

void ParenthValueString::SetValue(const std::string& InNewValue)
{
	Value = InNewValue;
}

std::string ParenthValueString::GetString() const
{
	return String;
}

std::string ParenthValueString::GetValue() const
{
	return Value;
}

std::string ParenthValueString::GetParenthValueString() const
{
	const std::string WhitespaceString = std::string(NumWhitespace, ' ');
	return std::format("{}{}({})", String, WhitespaceString, Value);
}