/*****************************************************************//**
 * \file   ParenthValueString.h
 * \brief  Class that parses and generates strings of the format "{String} ({Value})"
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

/**
 * \brief  Class that parses and generates strings of the format "{String} ({Value})"
 * 
 * This class can parse strings of the form "{String} ({Value})",
 * where {String} can be any string (including spaces), and
 * {Value} can be any string (including spaces, but not parentheses).
 * It can also generate such strings from a given String and Value.
 */
class ParenthValueString
{

public:

	/**
	 * Construct a default ParenthValueString with empty String and Value.
	 */
	ParenthValueString() = default;

	/**
	 * Construct a ParenthValueString from a string of the form "{String} ({Value})"
	 * 
	 * \param InParenthValue The string to parse, must be of the form "{String} ({Value})"
	 */
	ParenthValueString(const std::string& InParenthValue);

	/**
	 * Construct a ParenthValueString from the supplied InString and InVvalue.
	 * 
	 * \param InString The String portion of the ParenthValueString
	 * \param InValue The Value portion of the ParenthValueString
	 * \param InNumWhitespace The amount of whitespace between "{String}" and "("
	 */
	ParenthValueString(const std::string& InString, const std::string& InValue, int32_t InNumWhitespace = 1);

	/**
	 * Set the String portion of this ParenthValueString.
	 * 
	 * \param InNewString The new String portion of the ParenthValueString
	 */
	void SetString(const std::string& InNewString);

	/**
	 * Set the Value portion of this ParenthValueString.
	 * 
	 * \param InNewValue The new Value portion of the ParenthValueString
	 */
	void SetValue(const std::string& InNewValue);

	/**
	 * Returns the String portion of this ParenthValueString.
	 * 
	 * \return The String portion of this ParenthValueString
	 */
	std::string GetString() const;

	/**
	 * Returns the Value portion of this ParenthValueString.
	 * 
	 * \return The Value portion of this ParenthValueString
	 */
	std::string GetValue() const;

	/**
	 * Returns a string of the form "{String} ({Value})".
	 * 
	 * \return A string of the form "{String} ({Value})"
	 */
	std::string GetParenthValueString() const;

private:

	/** The string portion of this ParenthValueString. */
	std::string String = "";

	/** The value portion of this ParenthValueString. */
	std::string Value = "";

	/** The amount of whitespace between "{String}" and "(" */
	int32_t NumWhitespace = 1;

};
