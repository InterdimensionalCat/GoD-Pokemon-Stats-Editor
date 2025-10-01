#include "include.h"
#include "UI/UiComponent/StringComponent/TextBox.h"
#include "UI/UiElement/UiSingleElement.h"
#include "UI/UiSize/UiSize.h"

TextBox::TextBox
(
	const std::string& InName,
	UiSingleElement* InParent
) :
	UiComponent(InName, InParent)
{

}

void TextBox::DisplayComponent()
{
	// Show a text box with the text box buffer
	ImGui::InputText(GetName().c_str(), &TextBoxBuffer);

	// When the item is first deactivated after being active,
	// Notify the parent element that the value has changed.
	// NOTE: IsItemDeactivated() is only called once the frame after
	// an item goes from active to deactivated.
	if (ImGui::IsItemDeactivated())
	{
		ComponentUpdated();
	}
}

float TextBox::CalculateInternalSpace() const
{
	float InternalSize = 0.f;
	auto& Style = ImGui::GetStyle();

	// There is frame padding on either side of the box
	// text entry.
	InternalSize += Style.FramePadding.x * 2;

	return InternalSize;
}

void TextBox::SetTextBoxBuffer(const std::string& NewBufferValue)
{
	TextBoxBuffer = NewBufferValue;
}

std::string TextBox::GetTextBoxBuffer() const
{
	return TextBoxBuffer;
}