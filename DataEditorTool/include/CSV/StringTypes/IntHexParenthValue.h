#pragma once
#include "CSV/StringTypes/ParenthValueString.h"

class IntHexParenthValue : public ParenthValueString
{

public:

	/**
	 * Construct an IntHexParenthValue from the supplied integer. The
	 * String value will just be a string of the integer, the value
	 * will be an uppercase hex number with a lowercase prefix (0x instead of 0X)
	 * Example: An InIntValue of 31 would construct the string "31 (0x1F)"
	 */
	IntHexParenthValue(const int32_t InIntValue);

	/** Construct an IntHexParenthValue from a string of the format "{Int} (0x{HEX})" */
	IntHexParenthValue(const std::string& InIntHexString);

	void SetFromInt(const int32_t InIntValue);

	int32_t GetValueAsInt() const;
};