#pragma once

#include "CSV/CSVType/CSVType.h"

namespace GoDCSV
{
	class CSVInt : public CSVType
	{

	public:

		CSVInt(const std::string& InRawData);

		static CSVInt CreateFromInt(const int32_t InIntValue);

		static CSVInt CreateFromDegrees(const int32_t InDegrees);

		static CSVInt CreateFromString(const std::string& InIntString);

		int32_t GetValue() const;

	private:

		int32_t IntValue = 0;

	};
}