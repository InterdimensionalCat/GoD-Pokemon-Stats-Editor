/*****************************************************************//**
 * \file   TypedCSVField.h
 * \brief  
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

#include "CSV/CSVType/CSVType.h"
#include "CSV/CSVField/CSVField.h"
#include <concepts>

namespace GoDCSV
{
	template <typename T>
	class TypedCSVField : public CSVField
	{
		/** TypedCSVField will only work properly with CSVType template parameters */
		static_assert(std::derived_from<T, CSVType>, "T must inherit from CSVType.");

	public:

		TypedCSVField();

		virtual void SetTypedValue(const std::any& NewValue) override
		{
			FieldData = std::any_cast<T>(NewValue).GetRawData();
		}

	protected:

		virtual const std::any GetTypedValue() const override
		{
			return std::any(T(FieldData));
		}
	};
}
