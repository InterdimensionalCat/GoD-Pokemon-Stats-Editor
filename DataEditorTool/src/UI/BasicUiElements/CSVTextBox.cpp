#include "include.h"
#include "UI/BasicUiElements/CSVTextBox.h"

CSVTextBox::CSVTextBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName,
	const std::string& InColumnName
) :
	BasicUiElement<std::string>(InName, InParent, InCSVFileName, InColumnName)
{
	// We don't need to set the text box buffer to
	// The managed value here because the whole tab
	// will refresh on the next tick after elements
	// are added.
}

CSVTextBox::CSVTextBox
(
	const std::string& InName,
	UiSection* InParent,
	const std::string& InCSVFileName
) :
	CSVTextBox(InName, InParent, InCSVFileName, InName)
{

}

void CSVTextBox::Refresh()
{
	BasicUiElement::Refresh();
	TextBoxBuffer = GetManagedValue();
}

void CSVTextBox::Tick()
{
	// Show a text box with the text box buffer
	ImGui::InputText(GetName().c_str(), &TextBoxBuffer);

	// When the item is first deactivated after being active,
	// Update the managed value to whatever is in the TextBoxBuffer
	// NOTE: IsItemDeactivated() is only called once the frame after
	// an item goes from active to deactivated.
	// NOTE 2: SetManagedValue will check if the new value matches the
	// previous value, and will not send a new command if the values
	// are equal.
	if (ImGui::IsItemDeactivated())
	{
		SetManagedValue(TextBoxBuffer);
	}
	// Should no longer need to update the buffer every frame,
	// Refresh will handle that
	//else if (!ImGui::IsItemActivated())
	//{
	//	TextBoxBuffer = GetManagedValue();
	//}
}