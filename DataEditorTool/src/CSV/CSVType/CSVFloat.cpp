#include "include.h"
#include "CSV/CSVType/CSVFloat.h"

using namespace GoDCSV;

CSVFloat::CSVFloat(const std::string& InRawData) : CSVType(InRawData)
{
	FloatValue = std::stof(InRawData);
}

CSVFloat CSVFloat::CreateFromFloat(const float InFloatValue)
{
    // We want to store whole float values with 1 trailing zero
    // (EG: 1 should be "1.0" but we don't want to lose precision
    // with more specific numbers (3.14 should be "3.14") so
    // we need 2 cases.
    if (std::fmod(InFloatValue, 1.0) == 0.0) {
        return CSVFloat(std::format("{:.1f}", InFloatValue));
    }
    else {
        return CSVFloat(std::format("{}", InFloatValue));
    }
}

CSVFloat CSVFloat::CreateFromString(const std::string& InFloatString)
{
    return CSVFloat(InFloatString);
}
