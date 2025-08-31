#pragma once

#include "CSV/CSVType/CSVType.h"

namespace GoDCSV
{
	class CSVFloat : public CSVType
	{

	public:

		CSVFloat(const std::string& InRawData);

		static CSVFloat CreateFromFloat(const float InIntValue);

		static CSVFloat CreateFromString(const std::string& InFloatString);

		float GetValue() const;

	private:

		float FloatValue = 0.f;

	};
}