#include "include.h"
#include "UI/UiElement/UiMultiElement/UiElementGrid.h"
#include "UI/UiSize/UiUnboundSummedSize.h"
#include "UI/UiSize/UiSyncedSize.h"
#include "UI/UiSection.h"
#include "UI/UiSize/UiConstrainedSizeWithLabel.h"

UiElementGrid::UiElementGrid(const std::string& InName, UiSection* InParent
) :
	UiMultiElement(InName, InParent),
	SizeConstraints(std::make_shared<UiUnboundSummedSize>())
{
	ConstrainedSize = std::make_shared<UiConstrainedSizeWithLabel>();
}

void UiElementGrid::CalculateConstrainedSize(const std::shared_ptr<const UiConstrainedSize>& ParentConstrainedSize, const std::shared_ptr<const UiSize>& ParentSizeConstraints)
{

	// First, update the Size Constraints, which is the synced size of all elements * MinColumns
	std::shared_ptr<UiSyncedSize> LargestElementSize = std::make_shared<UiSyncedSize>();

	for (auto& ElementGrid : ElementGrids)
	{
		for (const auto Element : ElementGrid)
		{
			LargestElementSize->AddSizeToConsider(Element->GetSizeConstraints());
		}
	}

	SizeConstraints->ClearSizesToConsider();
	for (int32_t Column = 0; Column < MinColumns; Column++)
	{
		SizeConstraints->AddSizeToConsider(LargestElementSize);
	}

	// Calculate this MultiElement's constrained size, this will be
	// used as the space available for each row.
	ConstrainedSize->CalculateFromSizeConstraints(
		ParentConstrainedSize->GetConstrainedSize(),
		SizeConstraints
	);

	const auto& Style = ImGui::GetStyle();

	// Determine how many rows we can display with the space available.
	int32_t UnclampedCurrentColumns = 0;
	std::shared_ptr<UiSummedSize> SizeOfColumn = std::make_shared<UiSummedSize>();

	SizeOfColumn->AddSizeToConsider(LargestElementSize);

	auto InitialMin = SizeOfColumn->GetMinWithLabel();
	auto InitialSize = ConstrainedSize->GetConstrainedSize();

	float SpaceBetweenItems = 0.f;

	while (SizeOfColumn->GetMinWithLabel() < ConstrainedSize->GetConstrainedSize() - SpaceBetweenItems &&
		UnclampedCurrentColumns < MaxColumns)
	{
		SizeOfColumn->AddSizeToConsider(LargestElementSize);
		UnclampedCurrentColumns++;
		if (UnclampedCurrentColumns > 1)
		{
			SpaceBetweenItems += Style.ItemSpacing.x;
		}
	}

	const int32_t ClampedCurrentColumns = std::clamp(UnclampedCurrentColumns, MinColumns, MaxColumns);

	if (CurrentColumns != ClampedCurrentColumns)
	{
		CurrentColumns = ClampedCurrentColumns;
		RecalculateGridPositions();
	}

	// Finally, calculate the constrained size for each child element.
	// Each will have an equal amount of space available, and will
	// use the largest element's size constraints.
	float NumElementsPerLine = static_cast<float>(CurrentColumns);
	ConstrainedSize->SetConstrainedSize(ConstrainedSize->GetConstrainedSize() / NumElementsPerLine);
	ConstrainedSize->SetConstrainedSize(ConstrainedSize->GetConstrainedSize() - SpaceBetweenItems / NumElementsPerLine);

	for (auto UiElement : UiElements)
	{
		UiElement->CalculateConstrainedSize(ConstrainedSize, LargestElementSize);
	}
}

void UiElementGrid::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	ICLogger::Warn("UiElementGrid::AddElement called without specifying grid enabled, defaulting to true.");
	AddElement(NewElement, true);
}

void UiElementGrid::AddElement(const std::shared_ptr<UiElement> NewElement, const bool bGridEnabled)
{
	UiMultiElement::AddElement(NewElement);

	// Add this element to the most recent grid.
	// If no grids exist yet, create a new one.
	// If this element is not grid enabled, create
	// a new grid for future elements.
	if (bGridEnabled)
	{
		if (ElementGrids.size() == 0)
		{
			ElementGrids.push_back(std::vector<std::shared_ptr<UiElement>>());
		}
		ElementGrids.back().push_back(NewElement);
	}
	else
	{
		ElementGrids.push_back(std::vector<std::shared_ptr<UiElement>>());
	}
}

void UiElementGrid::SetMinColumns(const int32_t NewMinColumns)
{
	MinColumns = NewMinColumns;
}

void UiElementGrid::SetMaxColumns(const int32_t NewMaxColumns)
{
	MaxColumns = NewMaxColumns;
}

void UiElementGrid::SetShouldAlignElements(const bool ShouldAlign)
{
	bShouldAlignElements = ShouldAlign;
}

std::shared_ptr<const UiSize> UiElementGrid::GetSizeConstraints() const
{
	return SizeConstraints;
}

int32_t UiElementGrid::GetGridPosOfElement(std::shared_ptr<UiElement> GridElementToFind) const
{

	for (auto ElementGrid : ElementGrids)
	{
		auto FoundElementIt = std::find(ElementGrid.begin(), ElementGrid.end(), GridElementToFind);
		if (FoundElementIt != ElementGrid.end())
		{
			return std::distance(FoundElementIt, ElementGrid.begin()) % CurrentColumns;
		}
	}

	ICLogger::Warn("Supplied UiElement was not found in grid elements, was a not grid enabled element supplied?");
	return 0;
}

void UiElementGrid::RecalculateGridPositions()
{
	for (auto ElementGrid : ElementGrids)
	{
		for (int32_t Index = 0; Index < ElementGrid.size(); Index++)
		{
			auto Element = ElementGrid.at(Index);
			if (Index % CurrentColumns == 0)
			{
				Element->SetSameLine(false);
			}
			else
			{
				if (bShouldAlignElements)
				{
					// Recalculate the largest element size
					std::shared_ptr<UiSyncedSize> LargestElementSize = std::make_shared<UiSyncedSize>();

					for (auto& ElementGrid : ElementGrids)
					{
						for (const auto Element : ElementGrid)
						{
							LargestElementSize->AddSizeToConsider(Element->GetSizeConstraints());
						}
					}

					// Set same line with an offset to ensure vertical alignment
					// This offset is the largest element size * this elements grid position
					const float GridPos = static_cast<float>(Index % CurrentColumns);
					const float MaxElementSizeWithItemSpacing =
						LargestElementSize->GetMinWithLabel() + ImGui::GetStyle().ItemSpacing.x;
					Element->SetSameLine(MaxElementSizeWithItemSpacing * GridPos);
				}
				else
				{
					Element->SetSameLine(true);
				}
			}
		}
	}
}