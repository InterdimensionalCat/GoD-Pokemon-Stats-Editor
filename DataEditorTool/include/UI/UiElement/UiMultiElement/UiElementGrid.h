/*****************************************************************//**
 * \file   UiElementGrid.h
 * \brief  UiMultiELement that arranges its child elements in a grid layout.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#include "UI/UiElement/UiMultiElement/UiMultiElement.h"

class UiUnboundSummedSize;

/**
 * \brief UiMultiElement that arranges its child elements in a grid layout.
 * 
 * A UiElementGrid arranges its child UiElements in a grid layout,
 * with a configurable number of columns. It calculates its size
 * constraints based on the largest element size multiplied by
 * the number of columns, dynamically updates the number of
 * columns to display based on the space available, never
 * going below MinColumns or above MaxColumns.
 */
class UiElementGrid : public UiMultiElement
{
public:

	/**
	 * Construct a UiElementGrid with the supplied name and parent section.
	 * 
	 * \param InName Name of this UiElementGrid.
	 * \param InParent Parent section of this UiElementGrid.
	 */
	UiElementGrid(const std::string& InName, UiSection* InParent);

	/**
	 * Calculate the constrained size of this UiElementSwitcher,
	 * and calculate the constrained size of all child UiElements.
	 *
	 * A UiElementGrid calculates its size constraints to be
	 * the size of the largest element * MinColumns, as this is
	 * the minimum size the grid needs to display its elements
	 * in the MinColumns configuration.
	 *
	 * This will be the pushed item width for this element.
	 *
	 * \param ParentConstrainedSize The constrained size of the parent UiElement.
	 * \param ParentSizeConstraints The size constraints of the parent UiElement.
	 */
	virtual void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	) override;

	/**
	 * Add a child UiElement to this UiElementGrid. This will
	 * assume the element is grid enabled, but will warn if
	 * called as the user is expected to specify this explicitly.
	 * 
	 * \param NewElement Element to add to this UiElementGrid.
	 * \note Should not be called for a UiElementGrid, use the 
	 * overload that takes in a bool for grid enabling instead.
	 */
	virtual void AddElement(const std::shared_ptr<UiElement> NewElement) override;

	/**
	 * Add a child UiElement to this UiElementGrid, specifying
	 * whether or not the element should be grid enabled.
	 * 
	 * Grid enabled elements will be placed in the grid layout,
	 * while non-grid enabled elements will break the grid and
	 * be placed on their own line.
	 * 
	 * \param NewElement Element to add to this UiElementGrid.
	 * \param bGridEnabled True if this element should be grid enabled.
	 */
	virtual void AddElement(const std::shared_ptr<UiElement> NewElement, const bool bGridEnabled);

	/**
	 * Set the minimum number of columns this UiElementGrid
	 * should display.
	 * 
	 * \param NewMinColumns New minimum number of columns.
	 */
	void SetMinColumns(const int32_t NewMinColumns);

	/**
	 * Set the maximum number of columns this UiElementGrid
	 * should display.
	 * 
	 * \param NewMaxColumns New maximum number of columns.
	 */
	void SetMaxColumns(const int32_t NewMaxColumns);

	/**
	 * Set whether or not elements on different rows
	 * should be guaranteed to vertically align.
	 * 
	 * \param ShouldAlign True if elements on different rows should align.
	 */
	void SetShouldAlignElements(const bool ShouldAlign);

	/**
	 * Get the size constraints for this UiElementGrid.
	 * 
	 * The size constraints for a UiElementGrid is
	 * the size of the largest element * MinColumns,
	 * which is a loose maximum bound for the size of a row.
	 */
	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

private:

	/**
	 * Recalculate the grid positions of all grid enabled elements
	 * based on the current number of columns.
	 */
	void RecalculateGridPositions();

	/**
	 * Get the grid position (index) of the supplied element
	 * in the current grid layout. If the element is not found
	 * or is not grid enabled, this will return -1.
	 * 
	 * \param GridElementToFind The element to find the grid position of.
	 * \return The grid position (index) of the supplied element, or -1 if not found or not grid enabled.
	 */
	int32_t GetGridPosOfElement(std::shared_ptr<UiElement> GridElementToFind) const;

	/** Minimum number of elements that should be on the same line. */
	int32_t MinColumns = 1;

	/** Maximum number of elements allowed on the same line */
	int32_t MaxColumns = std::numeric_limits<int32_t>().max();

	/** 
	 * Current number of elements on the same line, calculated based on
	 * the space available whenever CalculateSizeConstraints is called.
	 */
	int32_t CurrentColumns = 0;

	/**
	 * Each grid enabled element separated into its proper grid.
	 */
	std::vector<std::vector<std::shared_ptr<UiElement>>> ElementGrids;

	/**
	 * Should elements on different rows be guaranteed to
	 * vertically align.
	 */
	bool bShouldAlignElements = false;

	/**
	 * The size constraints of this UiElementGrid. This
	 * will be the size of the largest element * MinColumns,
	 * which is a loose maximum bound for the size of a row
	 * we determine the largest element size by calculating a
	 * synced size from every grid enabled element.
	 * 
	 * TODO: this does not take into account the possibility
	 * that a non-grid aligned element could be larger than
	 * the largest possible row size
	 */
	std::shared_ptr<UiUnboundSummedSize> SizeConstraints;
};