/*****************************************************************//**
 * \file   CSVField.h
 * \brief  CSV field contains a CSV Value with a template param, and
 * then the CSV field can get that template param through an any,
 * and convert that template param to the correct type with a
 * member function that takes a type template arg
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

namespace GoDCSV
{
	/**
	 * Non-templated CSV Field class. The only
	 * class that should inherit from this is
	 * TypedCSVField<T>. This abstraction is needed
	 * so that we can store a vector of CSVFields in
	 * CSVRow. Templated types with different
	 * template params cannot be stored in the same array
	 */
	class CSVField
	{
	public:

		CSVField(const std::string& InFieldData);

		/**
		 * Get the underlying data in its properly typed form.
		 * Will throw an std::bad_any_cast if the underlying
		 * data is not of the supplied type
		 */
		template <typename T>
		T Get() const
		{
			return std::any_cast<T>(GetTypedValue());
		}

		template <typename T>
		void Set(const T& NewValue)
		{
			SetTypedValue(std::any(NewValue));
		}

	protected:

		/**
		 * Subclasses (typed CSV data override this function,
		 * which sets the FieldData from an std::any of the
		 * underlying type (the same type as Set<T>())
		 */
		virtual void SetTypedValue(const std::any& NewValue) = 0;

		/**
		 * Subclasses (typed CSV Data) override this function, 
		 * which converts FieldData into an std::any of the
		 * underlying type (the same type as Get<T>())
		 */
		virtual const std::any GetTypedValue() const = 0;

		std::string FieldData;
	};
}