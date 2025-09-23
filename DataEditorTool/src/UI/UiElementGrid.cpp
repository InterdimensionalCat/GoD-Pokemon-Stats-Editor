#include "include.h"
#include "UI/UiElementGrid.h"
#include "UI/UiSection.h"
#include "UI/UiTab.h"
#include "UI/TabCSVState.h"
#include "UI/UiCSVElement.h"
#include "UI/BasicUiElements/SectionDivider.h"

UiElementGrid::UiElementGrid(const std::string& InName, UiSection* InParent) : MultiUiElement(InName, InParent)
{

}

void UiElementGrid::Tick()
{
	// We probably need to recalc every tick
	// because the MultiElement's size will not
	// respond properly to font size changes
	// otherwise
	CalculateSizeConstraints();

	const float MaxElementSize = GetMaxSizeOfElements() + GetMaxLabelSizeOfElements();
	const auto& Style = ImGui::GetStyle();
	const float MaxElementSizeWithSpacing = MaxElementSize +
		(Style.ItemSpacing.x * 2) +
		Style.ItemInnerSpacing.x +
		(Style.FramePadding.x * 2);


	for (uint32_t i = 0; i < UiElements.size(); i++)
	{
		std::shared_ptr<UiElement> UiElement = UiElements.at(i);
		if (UiElement->IsSameLine())
		{
			if (bShouldAlignElements)
			{
				int32_t RowPosition = GetGridPosOfElement(UiElement);
				ImGui::SameLine((MaxElementSizeWithSpacing) * RowPosition);
			}
			else
			{
				ImGui::SameLine();
			}
		}

		// Draw the next UiElement with the correct constrained size.
		PushConstrainedSizeForElement(i);

		// Disable this element in ImGui before ticking if marked as disabled
		if (UiElement->IsDisabled())
		{
			ImGui::BeginDisabled();
			UiElement->Tick();

			// IsDisabled might change during Tick, so we must ensure this
			// gets called regardless of the value of IsDisabled after tick.
			ImGui::EndDisabled();
		}
		else
		{
			UiElement->Tick();
		}
		PopConstrainedSizeForElement(i);
	}
}

void UiElementGrid::PushConstrainedElementSize()
{
	MultiUiElement::PushConstrainedElementSize();

	// Now that the space available for this frame is
	// calculated, determine how many columns we can fit
	const float MaxElementSize = GetMaxSizeOfElements() + GetMaxLabelSizeOfElements();
	const auto& Style = ImGui::GetStyle();
	const float MaxElementSizeWithSpacing = MaxElementSize +
		(Style.ItemSpacing.x * 2) +
		Style.ItemInnerSpacing.x +
		(Style.FramePadding.x * 2);

	if (MaxElementSize > 0)
	{
		const float ColsPerSpaceFloat = ConstrainedSizeForThisFrame / MaxElementSizeWithSpacing;

		const int32_t ClampedColsPerSpace = std::clamp(
			static_cast<int32_t>(std::floor(ColsPerSpaceFloat)),
			MinColumns,
			MaxColumns);

		if (CurrentColumns != ClampedColsPerSpace)
		{
			CurrentColumns = ClampedColsPerSpace;

			for (auto Element : GridElements)
			{
				Element->SetSameLine(true);
			}

			//std::vector<int32_t> SectionDividerIndicies;
			//for (int32_t Index = 0; Index < SectionDividers.size(); Index++)
			//{
			//	auto SectionDividerIndexIt = std::find(UiElements.begin(), UiElements.end(), SectionDividers.at(Index));
			//	SectionDividerIndicies.push_back(std::distance(UiElements.begin(), SectionDividerIndexIt));
			//}

			//int32_t NumSectionDividers = 0;

			for (int32_t Index = 0; Index < GridElements.size(); Index++)
			{
				auto Element = GridElements.at(Index);

				//// If this element is a section divider, increase the
				//// section divider count and don't perform the checks below
				//if (NumSectionDividers < SectionDividerIndicies.size())
				//{
				//	if (SectionDividerIndicies.at(NumSectionDividers) == Index)
				//	{
				//		NumSectionDividers++;
				//		continue;
				//	}
				//}

				//// If this element is the next element after a section divider,
				//// it will always start a new row.
				//if (NumSectionDividers > 0)
				//{
				//	if (SectionDividerIndicies.at(NumSectionDividers - 1) == Index - 1)
				//	{
				//		Element->SetSameLine(false);
				//		continue;
				//	}
				//}
				//
				//// Ensure that line breaks happen at the correct rows,
				//// ignoring section dividers.
				//if ((Index - NumSectionDividers) % CurrentColumns == 0)
				//{
				//	Element->SetSameLine(false);
				//}

				if (GetGridPosOfElement(Element) == 0)
				{
					Element->SetSameLine(false);
				}
			}
		}
	}
	else
	{
		ICLogger::Error("GridElements elements size + label size unexpectedly zero.");
	}
}

void UiElementGrid::PushConstrainedSizeForElement(const uint32_t ElementIndex)
{
	auto CurrentElement = UiElements.at(ElementIndex);

	// Calculate the horizontal space available.
	const ImGuiStyle& Style = ImGui::GetStyle();
	float SpaceAvailable = ConstrainedSizeForThisFrame;

	if (CurrentElement->GetSize().GetSizeRule() == UiSizeRule_FixedSize)
	{
		ImGui::PushItemWidth(CurrentElement->GetSize().GetMin());
	}
	else
	{
		const int32_t NumElementsToScale = CurrentColumns;
		float WidthForThisElement = (SpaceAvailable / NumElementsToScale) - CalculateSpaceBetweenElements();
		WidthForThisElement = std::clamp(WidthForThisElement, CurrentElement->GetSize().GetMin(), CurrentElement->GetSize().GetMax());
		ImGui::PushItemWidth(WidthForThisElement);
	}
}

void UiElementGrid::PopConstrainedSizeForElement(const uint32_t ElementIndex)
{
	ImGui::PopItemWidth();
}

void UiElementGrid::AddCSVElement(const std::shared_ptr<UiCSVElement> NewElement)
{
	AddElement(NewElement);
	ParentSection->GetParent()->GetTabCSVState()->AddElementToUpdate(NewElement);
}

void UiElementGrid::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	UiElements.push_back(NewElement);
	GridElements.push_back(NewElement);

	// Recalculate the size constraints of this element.
	// Not needed because we calc this every frame anyway,
	// and for large grids this will likely get very slow
	// CalculateSizeConstraints();
}

void UiElementGrid::AddSectionDivider(const std::shared_ptr<SectionDivider> NewSectionDivider)
{
	UiElements.push_back(NewSectionDivider);
	SectionDividers.push_back(NewSectionDivider);
}

void UiElementGrid::CalculateSizeConstraints()
{
	float MaxSize = FLT_MAX;
	float MinSize = 0.f;

	for (int32_t OuterIndex = 0; OuterIndex < GridElements.size(); OuterIndex += MinColumns)
	{
		float MaxSizeThisLine = 0.f;
		float MinSizeThisLine = 0.f;

		for (int32_t InnerIndex = 0; InnerIndex < MinColumns; InnerIndex++)
		{
			if (OuterIndex + InnerIndex < GridElements.size())
			{
				const auto UiElement = GridElements.at(OuterIndex + InnerIndex);

				const auto ElementSize = UiElement->GetSize();
				const auto ElementMaxSize = ElementSize.GetMax();
				const auto ElementMinSize = ElementSize.GetMin();

				const auto UpperBound = std::numeric_limits<float>::max() - ElementMaxSize;
				const auto LowerBound = std::numeric_limits<float>::max() - ElementMinSize;

				// Ensure we don't go over FLT_MAX to prevent float overflow
				if (MaxSizeThisLine <= UpperBound)
				{
					MaxSizeThisLine += ElementSize.GetMax();
				}

				if (MinSizeThisLine <= LowerBound)
				{
					MinSizeThisLine += ElementSize.GetMin();
				}
			}
		}

		MaxSize = std::min(MaxSize, MaxSizeThisLine);
		MinSize = std::max(MinSize, MinSizeThisLine);
	}

	GetSize().SetMax(MaxSize);
	GetSize().SetMin(MinSize);
}

float UiElementGrid::GetLabelSize()
{
	float TotalLabelSize = 0.f;

	for (int32_t OuterIndex = 0; OuterIndex < GridElements.size(); OuterIndex += MinColumns)
	{
		float LabelSizeThisLine = 0.f;
		for (int32_t InnerIndex = 0; InnerIndex < MinColumns; InnerIndex++)
		{
			if (OuterIndex + InnerIndex < GridElements.size())
			{
				const auto UiElement = GridElements.at(OuterIndex + InnerIndex);

				LabelSizeThisLine += UiElement->GetLabelSize();
			}
		}

		LabelSizeThisLine = std::max(TotalLabelSize, LabelSizeThisLine);
	}

	return TotalLabelSize;
}

float UiElementGrid::GetMaxLabelSizeOfElements() const
{
	auto MaxElementIt = std::max_element(GridElements.begin(), GridElements.end(),
		[](const auto& Lhs, const auto& Rhs)
		{
			return Lhs->GetLabelSize() < Rhs->GetLabelSize();
		}
	);
	return (*MaxElementIt)->GetLabelSize();
}

float UiElementGrid::GetMaxSizeOfElements() const
{
	auto MaxElementIt = std::max_element(GridElements.begin(), GridElements.end(),
		[](const auto& Lhs, const auto& Rhs)
		{
			return Lhs->GetSize().GetMin() < Rhs->GetSize().GetMin();
		}
	);
	return (*MaxElementIt)->GetSize().GetMin();
}

float UiElementGrid::CalculateSpaceBetweenElements() const
{
	// Not sure exactly why, but the function below will correctly calculate
	// The width all elements should have if they should all be spaced equally:
	// (SpaceAvailable - (N-1) * S) / N
	// Where N is the number of elements and S is the space between elements
	const ImGuiStyle& Style = ImGui::GetStyle();
	const int32_t NumElements = CurrentColumns;
	float TotalLabelSizesMinusEnd = 0.f;

	for (int32_t Index = 0; Index < NumElements - 1; Index++)
	{
		std::shared_ptr<UiElement> Element = GridElements.at(Index);
		TotalLabelSizesMinusEnd += Element->GetLabelSize() + Style.ItemInnerSpacing.x;
	}

	const float SpaceBetweenItems = Style.ItemSpacing.x * (NumElements - 1);

	return (TotalLabelSizesMinusEnd + SpaceBetweenItems) / (NumElements);
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

int32_t UiElementGrid::GetGridPosOfElement(std::shared_ptr<UiElement> GridElementToFind) const
{
	std::vector<int32_t> SectionDividerIndicies;
	for (int32_t Index = 0; Index < SectionDividers.size(); Index++)
	{
		auto SectionDividerIndexIt = std::find(UiElements.begin(), UiElements.end(), SectionDividers.at(Index));
		SectionDividerIndicies.push_back(std::distance(UiElements.begin(), SectionDividerIndexIt));
	}

	int32_t NumSectionDividers = 0;
	int32_t LastSectionDividerIndex = 0;

	for (int32_t Index = 0; Index < UiElements.size(); Index++)
	{
		auto Element = UiElements.at(Index);
		if (NumSectionDividers < SectionDividerIndicies.size())
		{
			if (SectionDividerIndicies.at(NumSectionDividers) == Index)
			{
				LastSectionDividerIndex = Index;
				NumSectionDividers++;
			}
		}

		if (Element == GridElementToFind)
		{
			if (NumSectionDividers > 0)
			{
				int32_t GridIndex = Index - LastSectionDividerIndex - 1;
				return GridIndex % CurrentColumns;
			}
			else
			{
				return Index % CurrentColumns;
			}
		}
	}

	ICLogger::Warn("Supplied UiElement was not found in grid elements, was a section divider supplied?");
	return 0;

	//auto FoundIt = std::find(GridElements.begin(), GridElements.end(), GridElementToFind);
	//if (FoundIt != GridElements.end())
	//{
	//	return std::distance(GridElements.begin(), FoundIt);
	//}
	//else
	//{
	//	ICLogger::Warn("Supplied UiElement was not found in grid elements, was a section divider supplied?");
	//	return 0;
	//}
}