#include "include.h"
#include "UI/UiComponent/BoolComponent/CheckBox.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"

CheckBox::CheckBox
(
	const std::string& InName,
	UiSingleElement* InParent
) :
	UiComponent(InName, InParent)
{
	// Images will always be a fixed size.
	ComponentSize->SetIsFixedSize(true);
	SetMinContentSizeFromString("");
}

void CheckBox::DisplayComponent()
{
	// Show an checkbox.
	if (ImGui::Checkbox(GetName().c_str(), &bBoolBuffer))
	{
		ComponentUpdated();
	}
}

float CheckBox::CalculateInternalSpace() const
{
	// Since CheckBoxes are square, the size of a checkbox
	// is the vertical frame padding * 2 plus the font height.
	// This is equivalent to GetFrameHeight().
	return ImGui::GetFrameHeight();
}

void CheckBox::SetBoolBuffer(const bool InBufferVal)
{
	bBoolBuffer = InBufferVal;
}

bool CheckBox::GetBoolBuffer() const
{
	return bBoolBuffer;
}