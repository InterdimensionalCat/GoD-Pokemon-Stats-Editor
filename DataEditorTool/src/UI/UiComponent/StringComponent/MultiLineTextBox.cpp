#include "include.h"
#include "UI/UiComponent/StringComponent/MultiLineTextBox.h"

MultiLineTextBox::MultiLineTextBox
(
	const std::string& InName,
	UiSingleElement* InParent
) :
	TextBox(InName, InParent)
{

}

void MultiLineTextBox::DisplayComponent()
{
	// Show a text box with the text box buffer
	ImGui::InputTextMultiline(GetName().c_str(), &TextBoxBuffer, ImVec2(0, 0));
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