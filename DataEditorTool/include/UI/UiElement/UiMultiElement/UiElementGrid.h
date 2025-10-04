#pragma once

#include "UI/UiElement/UiMultiElement/UiMultiElement.h"

class UiUnboundSummedSize;

class UiElementGrid : public UiMultiElement
{
public:

	UiElementGrid(const std::string& InName, UiSection* InParent);

	virtual void CalculateConstrainedSize(
		const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize,
		const std::shared_ptr<const UiSize>& ParentSizeConstraints
	) override;

	virtual void AddElement(const std::shared_ptr<UiElement> NewElement) override;
	virtual void AddElement(const std::shared_ptr<UiElement> NewElement, const bool bGridEnabled);

	void SetMinColumns(const int32_t NewMinColumns);
	void SetMaxColumns(const int32_t NewMaxColumns);

	void SetShouldAlignElements(const bool ShouldAlign);

	virtual std::shared_ptr<const UiSize> GetSizeConstraints() const override;

private:

	void RecalculateGridPositions();

	//std::vector<std::vector<std::shared_ptr<UiElement>>> GetElementGrids() const;

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
	 * Contains a pointer key to every child element, both elements that
	 * should be in the grid and elements that should break the grid.
	 * 
	 * The bool value at each key indicates whether or not that element
	 * should be in the grid or break the grid.
	 */
	//std::map<std::shared_ptr<UiElement>, bool> ElementToGridEnabledMap;

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