#pragma once

class ParenthValueString;

class EntryNameString
{

public:

	/**
	 * Construct an EntryNameString with a string of the form "{EntryName} - {EntryNum}".
	 * The amount of whitespace between "{EntryName}" and '-' will be stored.
	 */
	EntryNameString(const std::string& InEntryNameString);

	/**
	 * Construct an EntryNameString with the supplied InEntryName and InEntryNum.
	 * The amount of whitespace between "}EntryName} and '-' can be specified.
	 */
	EntryNameString(const std::string& InEntryName, const std::string& InEntryNum, const int32_t InNumWhitespace = 1);

	void SetEntryName(const std::string& InEntryName);
	void SetEntryNum(const std::string& InEntryNum);

	std::string GetEntryName() const;
	std::string GetEntryNum() const;

	/**
	 * Returns a string of the form "{EntryName} - {EntryNum}".
	 * The amount of whitespace between "{EntryName}" and '-'
	 * will be whatever NumWhitespace is set to
	 */
	std::string GetEntryNameString() const;

	/**
	 * Converts this string to a ParenthValueString,
	 * or a string of the format "{String} ({Value})"
	 * 
	 * by default any quotes surrounding {EntryName}
	 * will be removed, but this can be disabled
	 * if needed
	 */
	ParenthValueString ToParenthValueString(const bool bRemoveQuotes = true) const;

private:

	std::string EntryName = "";

	std::string EntryNum = "";

	int32_t NumWhitespace = 1;
};
