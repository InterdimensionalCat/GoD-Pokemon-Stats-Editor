#include "include.h"
#include "CSV/CSVType/CSVInt.h"

using namespace GoDCSV;

CSVInt::CSVInt(const std::string& InRawData) : CSVType(InRawData)
{
	IntValue = (int32_t)std::stoi(InRawData);
}

CSVInt CSVInt::CreateFromInt(const int32_t InIntValue)
{
	return CSVInt(std::format("{}", InIntValue));
}

CSVInt CSVInt::CreateFromDegrees(const int32_t InDegrees)
{
	return CSVInt(std::format("{}°", InDegrees));
}

CSVInt CSVInt::CreateFromString(const std::string& InIntString)
{
	return CSVInt(InIntString);
}

int32_t CSVInt::GetValue() const
{
	return IntValue;
}