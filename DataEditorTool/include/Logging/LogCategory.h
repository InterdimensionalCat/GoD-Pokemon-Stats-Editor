/*****************************************************************//**
 * \file   LogCategory.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once

class LogCategory
{
public:
	/**
	 * \brief Construct a new Log Category object
	 *
	 * \param InName The name of the log category.
	 */
	LogCategory(const std::string& InName);

	const std::string& GetName() const { return Name; }

private:

	const std::string Name;
};

#define IC_LOG_CATAGORY_STATIC(CategoryName) \
		static struct LogCategory##CategoryName : public LogCategory \
		{ \
			inline LogCategory##CategoryName() : LogCategory(#CategoryName) {} \
		} CategoryName;
