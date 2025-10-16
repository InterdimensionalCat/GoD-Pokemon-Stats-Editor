#pragma once
#define IMGUI_USER_CONFIG "Contexts/CustomImConfig.h"

#include <exception>
#include <string>

/**
 * \brief Exception class for ImGui-related errors.
 * 
 * We override the default IM_ASSERT to throw this exception
 * instead of a C-style assert.
 */
class ImGuiException : public std::exception
{

public:

	explicit ImGuiException(const std::string& InMessage)
		: Message(InMessage) {}

	virtual const char* what() const noexcept override
	{
		return Message.c_str();
	}

private:

	std::string Message;
};

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)
#define LINE_STR STRINGIFY(__LINE__)
/** Redefine IM_ASSERT to throw an exception rather than calling assert(). */
#define IM_ASSERT(_EXPR)  do { if (!(_EXPR)) throw ImGuiException("ImGui Assertion failed: (" #_EXPR ") at: " __FILE__ ", line: " LINE_STR); } while (0)

#define IM_ASSERT_USER_ERROR(_EXPR,_MSG) do { if (!(_EXPR) && ImGui::ErrorLog(_MSG)) { throw ImGuiException("ImGui User Error Assertion failed: (" #_EXPR "), \"" _MSG "\" at: " __FILE__ ", line: " LINE_STR); } } while (0)
