#pragma once

#include "CSV/CSVType/CSVType.h"

namespace GoDCSV
{
	class CSVString : public CSVType
	{

	public:

		CSVString(const std::string& InRawData);

		static CSVString CreateFromFloat(const float InIntValue);

		static CSVString CreateFromString(const std::string& InFloatString);

		float GetValue() const;

	};
}