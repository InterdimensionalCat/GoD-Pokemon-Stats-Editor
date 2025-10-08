/*****************************************************************//**
 * \file   IntHexParenthValue.h
 * \brief  Subclass of ParenthValueString that represents strings of the format "{Int} (0x{HEX})"
 * 
 * \author bthomas
 * \date   October 2025
 *********************************************************************/
#pragma once
#include "CSV/StringTypes/ParenthValueString.h"

/**
 * \brief  Subclass of ParenthValueString that represents strings of the format "{Int} (0x{HEX})"
 * 
 * This class can parse strings of the form "{Int} (0x{HEX})",
 * where {Int} is a base-10 integer and {HEX} is the same integer
 * represented as an uppercase hexadecimal number with a lowercase "0x" prefix.
 * It can also generate such strings from a given integer.
 * 
 * Example: An IntHexParenthValue constructed from the integer 31
 * would have a string value of "31 (0x1F)".
 */
class IntHexParenthValue : public ParenthValueString
{

public:

	/**
	 * Construct an IntHexParenthValue from the supplied integer. The
	 * String value will just be a string of the integer, the value
	 * will be an uppercase hex number with a lowercase prefix (0x instead of 0X)
	 * Example: An InIntValue of 31 would construct the string "31 (0x1F)"
	 * 
	 * \param InIntValue The integer to construct this IntHexParenthValue from.
	 */
	IntHexParenthValue(const int32_t InIntValue);

	/**
	 * Construct an IntHexParenthValue from a string of the format "{Int} (0x{HEX})."
	 * 
	 * \param InIntHexString The string to parse, must be of the form "{Int} (0x{HEX})"
	 */
	IntHexParenthValue(const std::string& InIntHexString);

	/**
	 * Set this IntHexParenthValue from the supplied integer.
	 * 
	 * \param InIntValue The integer to set this IntHexParenthValue from.
	 */
	void SetFromInt(const int32_t InIntValue);

	/**
	 * Returns the integer value of this IntHexParenthValue.
	 * 
	 * \return The integer value of this IntHexParenthValue.
	 */
	int32_t GetValueAsInt() const;
};