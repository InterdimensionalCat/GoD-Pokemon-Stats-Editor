#pragma once

/** Storage for a string with the format "{String} ({Value})". */
class ParenthValueString
{

public:

	ParenthValueString() = default;

	/**
	 * Construct a ParenthValueString from a string of the form "{String} ({Value})"
	 */
	ParenthValueString(const std::string& InParenthValue);

	/** Construct a ParenthValueString from the supplied InString and InVvalue. */
	ParenthValueString(const std::string& InString, const std::string& InValue);

	void SetString(const std::string& InNewString);
	void SetValue(const std::string& InNewValue);

	std::string GetString() const;
	std::string GetValue() const;

	/** Returns a string of the form "{String} ({Value})". */
	std::string GetParenthValueString() const;

private:

	std::string String = "";

	std::string Value = "";

};
