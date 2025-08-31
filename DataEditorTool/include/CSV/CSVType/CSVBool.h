#pragma once

#include "CSV/CSVType/CSVType.h"

namespace GoDCSV
{
	class CSVBool : public CSVType
	{

	public:

		CSVBool(const std::string& InRawData);

		static CSVBool CreateFromBool(const bool InBoolValue);

		static CSVBool CreateFromString(const std::string& InBoolString);

		bool GetValue() const;

	private:

		bool BoolValue = false;

	};
}