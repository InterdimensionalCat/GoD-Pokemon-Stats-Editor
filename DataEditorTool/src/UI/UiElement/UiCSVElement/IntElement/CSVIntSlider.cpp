#include "include.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntSlider.h"
#include "UI/UiComponent/IntComponent/IntSlider.h"

CSVIntSlider::CSVIntSlider
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName,
	const int InMinValue,
	const int InMaxValue
) :
	UiBasicCSVElement<int32_t>(InName, InParent, InCSVFileName, InColumnName),
	IntSliderComponent(std::make_shared<IntSlider>(InName, this, InMinValue, InMaxValue))
{
	SetUiComponent(IntSliderComponent);
}

CSVIntSlider::CSVIntSlider
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const int InMinValue,
	const int InMaxValue
) :
	CSVIntSlider(InName, InParent, InCSVFileName, InName, InMinValue, InMaxValue)
{

}

void CSVIntSlider::Refresh()
{
	UiBasicCSVElement::Refresh();
	IntSliderComponent->SetIntBuffer(GetManagedValue());
}

void CSVIntSlider::UiComponentUpdated()
{
	SetManagedValue(IntSliderComponent->GetIntBuffer());
}

void CSVIntSlider::SetBounds(const int NewMinValue, const int NewMaxValue)
{
	IntSliderComponent->SetBounds(NewMinValue, NewMaxValue);
}

int CSVIntSlider::GetMinValue() const
{
	return IntSliderComponent->GetMinValue();
}

int CSVIntSlider::GetMaxValue() const
{
	return IntSliderComponent->GetMaxValue();
}