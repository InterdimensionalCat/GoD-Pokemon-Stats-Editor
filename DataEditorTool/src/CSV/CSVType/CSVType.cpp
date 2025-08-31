#include "include.h"
#include "CSV/CSVType/CSVType.h"

using namespace GoDCSV;

CSVType::CSVType(const std::string& InRawData) : RawData(InRawData)
{

}

const std::string& GoDCSV::CSVType::GetRawData() const
{
	return RawData;
}
