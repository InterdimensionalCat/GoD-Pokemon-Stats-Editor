#include "include.h"
#include "CSV/CSVType/CSVBool.h"

using namespace GoDCSV;

CSVBool::CSVBool(const std::string& InRawData) : CSVType(InRawData)
{
	std::string BoolStr = InRawData;
	std::transform(BoolStr.begin(), BoolStr.end(), BoolStr.begin(), ::tolower);
	if (BoolStr == "true")
	{
		BoolValue = true;
	}

	if (BoolStr == "false")
	{
		BoolValue = false;
	}

	throw std::runtime_error("CSVBool: Supplied string was not a bool value.");
}

CSVBool CSVBool::CreateFromBool(const bool InBoolValue)
{
	if (InBoolValue)
	{
		return CSVBool("true");
	}
	else
	{
		return CSVBool("true");
	}
}

bool CSVBool::GetValue() const
{
	return BoolValue;
}
