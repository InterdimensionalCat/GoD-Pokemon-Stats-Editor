#include "include.h"
#include "UI/MultiLineUiElement.h"
#include "UI/UiSection.h"
#include "UI/UiTab.h"
#include "UI/TabCSVState.h"
#include "UI/UiCSVElement.h"

MultiLineUiElement::MultiLineUiElement(const std::string& InName, UiSection* InParent) : MultiUiElement(InName, InParent)
{

}

// TODO: ability to designate an index as the "move to second line if not enough space" point
// TODO: label calcs don't work correctly for MultiLine UI elements
void MultiLineUiElement::PushConstrainedSizeForElement(const uint32_t ElementIndex)
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

		for (const auto Element : UiElements)
		{
			if (Element->GetSize().GetSizeRule() == UiSizeRule::UiSizeRule_FixedSize)
			{
				SpaceAvailable -= (Element->GetSize().GetMin() + Element->GetLabelSize() + Style.ItemInnerSpacing.x);
			}
		}

		// Not sure exactly why, but the function below will correctly calculate
		// The width all elements should have if they should all be spaced equally:
		// (SpaceAvailable - (N-1) * S) / N
		// Where N is the number of elements and S is the space between elements
		const int32_t NumFixedElements = GetNumFixedSizeElements();
		const int32_t NumElementsToScale = UiElements.size() - NumFixedElements;
		float WidthForThisElement = (SpaceAvailable / NumElementsToScale) - CalculateSpaceBetweenElements();
		WidthForThisElement = std::clamp(WidthForThisElement, CurrentElement->GetSize().GetMin(), CurrentElement->GetSize().GetMax());
		ImGui::PushItemWidth(WidthForThisElement);
	}
}

void MultiLineUiElement::PopConstrainedSizeForElement(const uint32_t ElementIndex)
{
	ImGui::PopItemWidth();
}

void MultiLineUiElement::AddCSVElement(const std::shared_ptr<UiCSVElement> NewElement)
{
	AddElement(NewElement);
	ParentSection->GetParent()->GetTabCSVState()->AddElementToUpdate(NewElement);
}

void MultiLineUiElement::AddElement(const std::shared_ptr<UiElement> NewElement)
{
	UiElements.push_back(NewElement);

	std::shared_ptr<UiElement> AddedUiElement = UiElements.at(UiElements.size() - 1);

	// Set same line if this is not the first element in the multi-line.
	if ((UiElements.size() - 1) != 0)
	{
		AddedUiElement->SetSameLine(true);
	}
	else
	{
		AddedUiElement->SetSameLine(false);
	}

	const ImGuiStyle& Style = ImGui::GetStyle();

	// AddedUiElement->GetSize().SetPaddingSpace(300.f/*AddedUiElement->GetSize().GetPaddingSpace() + Style.ItemSpacing.x*/);

	// Recalculate the size constraints of this element.
	CalculateSizeConstraints();
}

float MultiLineUiElement::CalculateSpaceBetweenElements() const
{
	// Not sure exactly why, but the function below will correctly calculate
	// The width all elements should have if they should all be spaced equally:
	// (SpaceAvailable - (N-1) * S) / N
	// Where N is the number of elements and S is the space between elements
	const ImGuiStyle& Style = ImGui::GetStyle();
	const int32_t NumElements = UiElements.size();
	float TotalLabelSizesMinusEnd = 0.f;

	for (int32_t Index = 0; Index < NumElements - 1; Index++)
	{
		std::shared_ptr<UiElement> Element = UiElements.at(Index);
		TotalLabelSizesMinusEnd += Element->GetLabelSize() + Style.ItemInnerSpacing.x;
	}

	const float SpaceBetweenItems = Style.ItemSpacing.x * (NumElements - 1);

	return (TotalLabelSizesMinusEnd + SpaceBetweenItems) / (NumElements);
}

int32_t MultiLineUiElement::GetNumFixedSizeElements() const
{
	int32_t NumFixedSizeElements = 0;
	for (int32_t Index = 0; Index < UiElements.size(); Index++)
	{
		if (UiElements.at(Index)->GetSize().GetSizeRule() == UiSizeRule::UiSizeRule_FixedSize)
		{
			NumFixedSizeElements++;
		}
	}

	return NumFixedSizeElements;
}