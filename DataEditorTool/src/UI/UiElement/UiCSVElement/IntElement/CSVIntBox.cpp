#include "include.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntBox.h"
#include "UI/UiComponent/IntComponent/IntBox.h"

CSVIntBox::CSVIntBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName,
	const int InStepSize,
	const int InFastStepSize
) :
	UiBasicCSVElement<int32_t>(InName, InParent, InCSVFileName, InColumnName),
	IntBoxComponent(std::make_shared<IntBox>(InName, this, InStepSize, InFastStepSize))
{
	SetUiComponent(IntBoxComponent);
}

CSVIntBox::CSVIntBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const int InStepSize,
	const int InFastStepSize
) :
	CSVIntBox(InName, InParent, InCSVFileName, InName, InStepSize, InFastStepSize)
{

}

void CSVIntBox::Refresh()
{
	UiBasicCSVElement::Refresh();
	IntBoxComponent->SetIntBuffer(GetManagedValue());
}

void CSVIntBox::UiComponentUpdated()
{
	SetManagedValue(IntBoxComponent->GetIntBuffer());
}

void CSVIntBox::SetElementMinSize(const uint32_t MinNumDigits)
{
	IntBoxComponent->SetElementMinSize(MinNumDigits);
}

void CSVIntBox::SetElementMaxSize(const uint32_t MaxNumDigits)
{
	IntBoxComponent->SetElementMaxSize(MaxNumDigits);
}

void CSVIntBox::SetBounds(const int NewMinValue, const int NewMaxValue)
{
	IntBoxComponent->SetBounds(NewMinValue, NewMaxValue);
}

int CSVIntBox::GetIntBuffer() const
{
	return IntBoxComponent->GetIntBuffer();
}

int CSVIntBox::GetMinValue() const
{
	return IntBoxComponent->GetMinValue();
}

int CSVIntBox::GetMaxValue() const
{
	return IntBoxComponent->GetMaxValue();
}