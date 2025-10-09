#include "include.h"
#include "CSV/StringTypes/IntHexParenthValue.h"

IntHexParenthValue::IntHexParenthValue(const int32_t InIntValue)
	: ParenthValueString(std::format("{}", InIntValue), std::format("0x{:X}", InIntValue))
{

}

IntHexParenthValue::IntHexParenthValue(const std::string& InIntHexString)
	: ParenthValueString(InIntHexString)
{

}

void IntHexParenthValue::SetFromInt(const int32_t InIntValue)
{
	SetString(std::format("{}", InIntValue));
	SetValue(std::format("0x{:X}", InIntValue));
}

int32_t IntHexParenthValue::GetValueAsInt() const
{
	// First try and convert the value to an int.
	// it is a nex number so we need to stoi with base 16
	int32_t ReturnVal = 0;
	try
	{
		ReturnVal = std::stoi(GetValue(), nullptr, 16);
	}
	catch (const std::exception& e)
	{
		ICLogger::Warn("IntHex value field {} not a valid hex number, attempting to convert the String", GetValue());
		// If that does not work, try to stoi the String,
		// which should be a number in base 10.
		try 
		{
			ReturnVal = std::stoi(GetString());
		}
		catch (const std::exception& e)
		{
			// If that doesn't work either, then this IntHexParenthValue is not valid
			ICLogger::Error("IntHex string field {} also not a valid number, IntHex is invalid", GetString());
			return ReturnVal;
		}
	}

	return ReturnVal;
}