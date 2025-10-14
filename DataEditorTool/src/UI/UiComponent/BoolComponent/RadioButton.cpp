#include "include.h"
#include "UI/UiComponent/BoolComponent/RadioButton.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"

RadioButton::RadioButton
(
	const std::string& InName,
	UiSingleElement* InParent
) :
	UiComponent(InName, InParent)
{
	ComponentSize->SetIsFixedSize(true);
	SetMinContentSizeFromString("");
}

void RadioButton::DisplayComponent()
{
	// Show a RadioButton.
	if (ImGui::RadioButton(GetName().c_str(), bBoolBuffer))
	{
		bBoolBuffer = !bBoolBuffer;
		ComponentUpdated();
	}
}

float RadioButton::CalculateInternalSpace() const
{
	// Since RadioButtons are square, the size of a RadioButton
	// is the vertical frame padding * 2 plus the font height.
	// This is equivalent to GetFrameHeight().
	return ImGui::GetFrameHeight();
}

void RadioButton::SetBoolBuffer(const bool InBufferVal)
{
	bBoolBuffer = InBufferVal;
}

bool RadioButton::GetBoolBuffer() const
{
	return bBoolBuffer;
}