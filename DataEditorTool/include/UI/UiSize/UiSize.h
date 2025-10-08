/*****************************************************************//**
 * \file   UiSize.h
 * \brief  Class that handles the horizontal sizing of a UiElement
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

/**
 * \struct UiSizeBound
 * 
 * \brief  Horizontal size bounds of an element excluding its label.
 * 
 * A UiSizeBounds contains 3 variables it uses to calculate the
 * pixel size of a bound: 
 * 
 * 1) ContentSize: The size of the content string this bound should support,
 *	  for example, the int entry box of an IntBox, or the current item display of
 *	  of a ComboBox.
 * 2) InternalSpace: Any padding or extra space this size must take up
 *	  to support a content of the given length. Do not include
 *	  ItemInnerSpacing between the element and its label.
 * 3) ExtraSpace: A flat pixel amount of extra space the content region should
 *	  Support. Used for elements that don't have a content string, like buttons.
 */
struct UiSizeBound
{

public:

	/**
	 * Construct a UiSizeBound with the given content size,
	 * InternalSpace, and ExtraSpace.
	 * 
	 * \param InContentSize Size of content this bound should support.
	 * \param InInternalSpace Any padding or extra space this size must take up
	 * \param InExtraSpace Any additional space the content region should support, in pixels.
	 */
	UiSizeBound(
		const std::string& InContentSize,
		const float InInternalSpace,
		const float InExtraSpace
	);

	/**
	 * Size of content this bound should support.
	 */
	std::string ContentSize;

	/**
	 * Any padding or extra space this size must take up
	 * to support a content of the given length. Do not
	 * include ItemInnerSpacing between the element and
	 * its label.
	 */
	float InternalSpace = 0.f;

	/**
	 * Any additional space the content region should support,
	 * in pixels.
	 */
	 float ExtraSpace = 0.f;

	 /**
	  * Calculate the total pixel size of this UiSizeBound.
	  * The size of the bound is how big this element
	  * must be to fully display the content string,
	  * which is the size of the content string plus
	  * the internal space, and extra space.
	  */
	 float CalculateBound() const;

};

/**
 *\brief  Class that contains the (horizontal) size of a UiElement.
 * 
 * Contains a minimum and maximum size bound that is re-calculated
 * every time the Min/Max pixel bound is accessed. This is necessary
 * because font size changes will change the pixel size needed to display
 * content strings.
 */
class UiSize
{
public:

	/** Constructs a UiSize with no size constraints. Fixed size defaults to off. */
	UiSize();

	/** 
	 * Constructs a UiSize With the given Min/Max bound and label. Fixed size defaults to off.
	 * 
	 * \param InMin Minimum size bound for this UiSize.
	 * \param InMax Maximum size bound for this UiSize.
	 * \param InLabel Label this UiSize must account for.
	 */
	UiSize(
		const UiSizeBound& InMin,
		const UiSizeBound& InMax,
		const std::string& InLabel
	);

	/**
	 * Set a new minimum bound for this UiSize.
	 * 
	 * \param InMin New minimum bound for this UiSize.
	 */
	void SetMin(const UiSizeBound& InMin);

	/**
	 * Set a new maximum bound for this UiSize.
	 * 
	 * \param InMax New maximum bound for this UiSize.
	 */
	void SetMax(const UiSizeBound& InMax);

	/**
	 * Set this UiSize to be a fixed or variable size.
	 * 
	 * \param IsFixedSize True if this UiSize should be a fixed size.
	 */
	void SetIsFixedSize(const bool IsFixedSize);

	/**
	 * Set the label size this UiSize must account for.
	 * If set to a string that results in a calculated 
	 * size of 0, the label size and its InnerItemSpacing
	 * will not be accounted for in calculations.
	 * 
	 * \param InLabel New label for this UiSize.
	 */
	void SetLabel(const std::string& InLabel);

	/** 
	 * Get the label for this UiSize. 
	 *
	 * \return The label for this UiSize.
	 */
	std::string GetLabel() const;

	/** 
	 * Get the calculated label size, including the ItemInnerSpacing
	 * between the element and its label.
	 * 
	 * \return The calculated label size, including spacing.
	 */
	virtual float GetLabelSizeWithSpacing() const;

	/** 
	 * Get the calculated label size, excluding the ItemInnerSpacing
	 * between the element and its label.
	 * 
	 * \return The calculated label size, excluding spacing.
	 */
	virtual float GetLabelSizeWithoutSpacing() const;

	/** 
	 * Get the calculated Minimum bound of this UiSize (including the label size).
	 * 
	 * \return The calculated Minimum bound of this UiSize (including the label size).
	 */
	virtual float GetMinWithLabel() const;

	/** 
	 *Get the calculated Minimum bound of this UiSize (excluding the label size).
	 * 
	 * \return The calculated Minimum bound of this UiSize (excluding the label size).
	 */
	virtual float GetMinWithoutLabel() const;

	/** 
	 * Get the calculated Maximum bound of this UiSize (including the label size). 
	 * NOTE: this will return the Minimum bound if bIsFixedSize is true.
	 * 
	 * \return The calculated Maximum bound of this UiSize (including the label size).
	 * \note This will return the Minimum bound if bIsFixedSize is true.
	 */
	virtual float GetMaxWithLabel() const;

	/** 
	 * Get the calculated Maximum bound of this UiSize (excluding the label size). 
	 * NOTE: this will return the Minimum bound if bIsFixedSize is true.
	 * 
	 * \return The calculated Maximum bound of this UiSize (excluding the label size).
	 * \note This will return the Minimum bound if bIsFixedSize is true.
	 */
	virtual float GetMaxWithoutLabel() const;

	/** 
	 * Returns true of this is a fixed size UiSize.
	 *
	 * \return True if this is a fixed size UiSize.
	 */
	bool IsFixedSize() const;

private:

	/** The minimum size bound for this UiSize. */
	UiSizeBound MinBound;

	/** The maximum size bound for this UiSize. */
	UiSizeBound MaxBound;

	/** 
	 * The label this UiSize must account for. If the label's
	 * calculated text size is 0 (because its an empty string,
	 * or begins with "##", then label calculations will not
	 * factor in the InnerItemSpacing between elements and
	 * their labels.
	 */
	std::string Label;

	/**
	 * Is this a fixed size UiSize?
	 * If so, ignore the max size and 
	 * always use the min size.
	 */
	bool bIsFixedSize = false;

};
