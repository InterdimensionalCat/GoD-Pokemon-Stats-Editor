/*****************************************************************//**
 * \file   CSVType.h
 * \brief  
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

namespace GoDCSV
{
	class CSVType
	{
	public:

		CSVType(const std::string& InRawData);

		const std::string& GetRawData() const;

	private:

		std::string RawData;
	};
}
