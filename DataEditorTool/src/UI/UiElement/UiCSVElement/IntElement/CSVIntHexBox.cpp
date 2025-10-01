#include "include.h"
#include "UI/UiElement/UiCSVElement/IntElement/CSVIntHexBox.h"
#include "UI/UiComponent/IntComponent/IntBox.h"

#include "CSV/StringTypes/IntHexParenthValue.h"

CSVIntHexBox::CSVIntHexBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName,
	const int InStepSize,
	const int InFastStepSize
) :
	UiBasicCSVElement<std::string>(InName, InParent, InCSVFileName, InColumnName),
	IntBoxComponent(std::make_shared<IntBox>(InName, this, InStepSize, InFastStepSize))
{
	SetUiComponent(IntBoxComponent);
}

CSVIntHexBox::CSVIntHexBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const int InStepSize,
	const int InFastStepSize
) :
	CSVIntHexBox(InName, InParent, InCSVFileName, InName, InStepSize, InFastStepSize)
{

}

void CSVIntHexBox::Refresh()
{
	UiBasicCSVElement::Refresh();

	// The managed value for this UI type will be in the form
	// "{int} (0x{HEX})", for example, "31 (0x1F)". We need to
	// convert this into an int to set the buffer.
	const IntHexParenthValue IntHexString(GetManagedValue());
	IntBoxComponent->SetIntBuffer(static_cast<int>(IntHexString.GetValueAsInt()));
}

void CSVIntHexBox::UiComponentUpdated()
{
	// The managed value for this UI type is in the form
	// "{int} (0x{HEX})", for example, "31 (0x1F)". We need to
	// convert the buffer to this form before setting it.
	const IntHexParenthValue IntHexString(static_cast<int32_t>(IntBoxComponent->GetIntBuffer()));
	SetManagedValue(IntHexString.GetParenthValueString());
}

void CSVIntHexBox::SetElementMinSize(const uint32_t MinNumDigits)
{
	IntBoxComponent->SetElementMinSize(MinNumDigits);
}

void CSVIntHexBox::SetElementMaxSize(const uint32_t MaxNumDigits)
{
	IntBoxComponent->SetElementMaxSize(MaxNumDigits);
}

void CSVIntHexBox::SetBounds(const int NewMinValue, const int NewMaxValue)
{
	IntBoxComponent->SetBounds(NewMinValue, NewMaxValue);
}

int CSVIntHexBox::GetMinValue() const
{
	IntBoxComponent->GetMinValue();
}

int CSVIntHexBox::GetMaxValue() const
{
	IntBoxComponent->GetMaxValue();
}