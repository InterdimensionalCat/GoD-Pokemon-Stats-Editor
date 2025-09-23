#pragma once
#include "UI/MultiUiElement.h"

class UiCSVElement;
class SectionDivider;

class UiElementGrid : public MultiUiElement
{
public:

	UiElementGrid(const std::string& InName, UiSection* InParent);

	virtual void Tick() override;

	virtual void PushConstrainedElementSize() override;

	virtual void PushConstrainedSizeForElement(const uint32_t ElementIndex) override;

	virtual void PopConstrainedSizeForElement(const uint32_t ElementIndex) override;

	virtual void AddCSVElement(const std::shared_ptr<UiCSVElement> NewElement) override;
	virtual void AddElement(const std::shared_ptr<UiElement> NewElement) override;
	virtual void AddSectionDivider(const std::shared_ptr<SectionDivider> NewSectionDivider);

	/**
	 * For an Element Grid, the Min size is only the summation of the
	 * largest line of elements at MinColumns, not the summation of all elements
	 */
	virtual void CalculateSizeConstraints();

	virtual float GetLabelSize() override;

	float GetMaxLabelSizeOfElements() const;

	float GetMaxSizeOfElements() const;

	virtual float CalculateSpaceBetweenElements() const;

	void SetMinColumns(const int32_t NewMinColumns);
	void SetMaxColumns(const int32_t NewMaxColumns);

	void SetShouldAlignElements(const bool ShouldAlign);

private:

	int32_t GetGridPosOfElement(std::shared_ptr<UiElement> GridElementToFind) const;
	
	/** Minimum number of elements that should be on the same line. */
	int32_t MinColumns = 1;

	int32_t CurrentColumns = 1;

	/** Maximum number of elements allowed on the same line */
	int32_t MaxColumns = std::numeric_limits<int32_t>().max();

	std::vector<std::shared_ptr<SectionDivider>> SectionDividers;

	std::vector <std::shared_ptr<UiElement>> GridElements;

	/**
	 * Should elements on different rows be guarunteed to
	 * vertically align.
	 */
	bool bShouldAlignElements = false;
};
