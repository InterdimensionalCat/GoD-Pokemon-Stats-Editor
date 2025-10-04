#include "include.h"
#include "UI/UiElement/UiSimpleElement/IntElement/SimpleIntBox.h"
#include "UI/UiComponent/IntComponent/IntBox.h"

SimpleIntBox::SimpleIntBox
(
	const std::string& InName,
	UiSection* InParent,
	const int InStepSize,
	const int InFastStepSize
) :
	UiSingleElement(InName, InParent),
	IntBoxComponent(std::make_shared<IntBox>(InName, this, InStepSize, InFastStepSize))
{
	SetUiComponent(IntBoxComponent);
}

void SimpleIntBox::UiComponentUpdated()
{
	// Implementation intentionally left blank.
}

void SimpleIntBox::SetElementMinSize(const uint32_t MinNumDigits)
{
	IntBoxComponent->SetElementMinSize(MinNumDigits);
}

void SimpleIntBox::SetElementMaxSize(const uint32_t MaxNumDigits)
{
	IntBoxComponent->SetElementMaxSize(MaxNumDigits);
}

void SimpleIntBox::SetBounds(const int NewMinValue, const int NewMaxValue)
{
	IntBoxComponent->SetBounds(NewMinValue, NewMaxValue);
}

void SimpleIntBox::SetIntBuffer(const int NewBufferValue)
{
	IntBoxComponent->SetIntBuffer(NewBufferValue);
}

int SimpleIntBox::GetMinValue() const
{
	return IntBoxComponent->GetMinValue();
}

int SimpleIntBox::GetMaxValue() const
{
	return IntBoxComponent->GetMaxValue();
}