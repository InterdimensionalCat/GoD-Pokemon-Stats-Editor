/*****************************************************************//**
 * \file   EntryNameString.h
 * \brief  Class that parses and generates strings of the format "{EntryName} - {EntryNum}"
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

class ParenthValueString;

/**
 * \brief  Class that parses and generates strings of the format "{EntryName} - {EntryNum}"
 * 
 * This class can parse strings of the form "{EntryName} - {EntryNum}",
 * where the amount of whitespace between "{EntryName}" and '-' is variable.
 * It can also generate such strings from a given EntryName and EntryNum,
 * with a specified amount of whitespace.
 */
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

	/** Set the EntryName to the supplied value. */
	void SetEntryName(const std::string& InEntryName);

	/** Set the EntryNum to the supplied value. */
	void SetEntryNum(const std::string& InEntryNum);

	/** Returns the EntryName portion of the EntryNameString */
	std::string GetEntryName() const;

	/** Returns the EntryNum portion of the EntryNameString */
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

	/** The EntryName portion of the EntryNameString */
	std::string EntryName = "";

	/** The EntryNum portion of the EntryNameString */
	std::string EntryNum = "";

	/** The amount of whitespace between "{EntryName}" and '-' */
	int32_t NumWhitespace = 1;
};
