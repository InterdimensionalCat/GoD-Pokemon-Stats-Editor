#include "include.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiConstrainedSize.h"
#include "UI/UiComponent/UiComponent.h"

UiSingleElement::UiSingleElement(const std::string& InName,
	UiSection* InParent
) :
	UiElement(InName, InParent),
	Component(nullptr)
{

}

void UiSingleElement::Tick()
{
	// Display the component with its width set to the pre-calculated
	// constrained size.
	ImGui::PushItemWidth(ConstrainedSize->GetConstrainedSize());
	Component->DisplayComponent();
	ImGui::PopItemWidth();
}

std::shared_ptr<const UiSize> UiSingleElement::GetSizeConstraints() const
{
	return Component->GetSizeConstraints();
}

std::shared_ptr<const UiComponent> UiSingleElement::GetUiComponent() const
{
	return Component;
}

void UiSingleElement::SetSameLine(const bool bInSameLine)
{
	Component->SetSameLine(bInSameLine);
}

void UiSingleElement::SetDisabled(const bool bInDisabled)
{
	Component->SetDisabled(bInDisabled);
}

void UiSingleElement::SetUiComponent(std::shared_ptr<UiComponent> NewComponent)
{
	Component = NewComponent;
}