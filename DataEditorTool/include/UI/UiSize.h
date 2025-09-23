/*****************************************************************//**
 * \file   UiSize.h
 * \brief  Class that handles the horiziontal sizing of a UiElement
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

enum class UiSizeRule : uint8_t
{
	/** Scale UI element normally (make element + label the max size, then cut of label if needed, then reduce size down to min if needed) */
	UiSizeRule_Normal,

	/** Scale UI element to whatever Min is set to at all times. */
	UiSizeRule_FixedSize
};

using enum UiSizeRule;

/**
 * Class that contains the (horizontal) size of a UiElement.
 *
 * This is complex enough to be its own struct since we need to store a
 * max and min element, as well as data to allow us to pass in a size
 * as a string length, but not actually calcluate the string length until we
 * need it.
 */
class UiSize
{
public:

	/** Constructs a UiSize with no size constraints. The default SizeRule is normal */
	UiSize();

	/** Constructs a UiSize with float min and max values. The default SizeRule is normal */
	UiSize(const float InMin, const float InMax);

	/** Set a minimum width constraint from a float width in pixels. */
	void SetMin(const float NewMin);

	/** Set a maximum width constraint from a float width in pixels. */
	void SetMax(const float NewMax);

	/**
	 * Set a minimum width constraint from a string.
	 * The constraint will be equal to the ImGui text size of the string.
	 */
	void SetMinFromString(const std::string& NewMinString);

	/**
	 * Set a minimum width constraint from a group of strings.
	 * The string with the longest character length will be used.
	 */
	void SetMinFromLongestString(const std::vector<std::string>& MaxStrings);

	/**
	 * Set a maximum width constraint from a string.
	 * The constraint will be equal to the ImGui text size of the string.
	 */
	void SetMaxFromString(const std::string& NewMaxString);

	/**
	 * Set a maximum width constraint from a group of strings.
	 * The string with the longest character length will be used.
	 */
	void SetMaxFromLongestString(const std::vector<std::string>& MaxStrings);

	/**
	 * Set a minimum width constraint by what string length you want to support.
	 * The constraint will be equal to the ImGui text size of a string of size
	 * NewMinStringLength filled with the '-' character, so a new min length of
	 * 3 will set the min string to "---".
	 */
	void SetMinFromStringLength(const uint32_t NewMinStringLength);

	/**
	 * Set a maximum width constraint by what string length you want to support.
	 * The constraint will be equal to the ImGui text size of a string of size
	 * NewMaxStringLength filled with the '-' character, so a new max length of
	 * 3 will set the max string to "---".
	 */
	void SetMaxFromStringLength(const uint32_t NewMaxStringLength);

	/**
	 * Set the padding space for this size. The padding space is the
	 * extra space an element takes up that needs to be accounted for
	 * when calculating the Min/Max. Almost all elements have FramePadding
	 * on either side, so this defaults to FramePadding * 2. But some
	 * elements have other parts that take up extra space, such as IntBoxes
	 * when the step buttons are enabled.
	 */
	void SetPaddingSpace(const float NewPaddingSpace);

	/** Set the size rule for this UiSize. */
	void SetSizeRule(const UiSizeRule NewSizeRule);

	/** Calculate the size this element should be within the size constraints of this UiSize. */
	float CalculateSizeFromSpaceAvailable(const float SpaceAvailable, const float LabelSize = 0.f, const uint32_t NumItemsPerLine = 1) const;

	/**
	 * Get the Min width for this UiSize, this will return different things depending
	 * on whether or not the min value was set by a string/string length or a float.
	 *	- If Min size was set by a float, it will return the float value it was set to,
	 *	  which is the min size in pixels
	 *	- If Min size was set by a string or string length, it will return the calculated text
	 *	  size of the min length string.
	 */
	float GetMin() const;

	/**
	 * Get the Max width for this UiSize, this will return different things depending
	 * on whether or not the max value was set by a string/string length or a float.
	 *	- If Max size was set by a float, it will return the float value it was set to,
	 *	  which is the max size in pixels
	 *	- If Max size was set by a string or string length, it will return the calculated text
	 *	  size of the max length string.
	 */
	float GetMax() const;

	/** Returns the current padding space used to calculate this size. */
	float GetPaddingSpace() const;

	/** Return the current size rule for this UiSize. */
	UiSizeRule GetSizeRule() const;

private:

	UiSizeRule SizeRule;

	std::variant<float, std::string> MinWidth;

	std::variant<float, std::string > MaxWidth;

	float PaddingSpace = 0.f;
};
