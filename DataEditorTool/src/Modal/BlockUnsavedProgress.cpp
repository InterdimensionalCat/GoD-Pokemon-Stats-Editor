#include "include.h"
#include "Modal/BlockUnsavedProgress.h"
#include "Modal/SaveFailed.h"
#include "Modal/ModalManager.h"
#include "CSV/CSVDatabase.h"
#include "MainEditor/MainEditorWindow.h"

BlockUnsavedProgress::BlockUnsavedProgress(
	const std::string& InPopupTopMessage, 
	const std::function<void()>& InBypassModalCallback) 
	: Modal(
		std::string("Warning: Unsaved Progress##") + InPopupTopMessage, 
		InBypassModalCallback
	),
	PopupTopMessage(InPopupTopMessage)
{

}

void BlockUnsavedProgress::OnModalMadeActive()
{
	// Get a list of all modified CSV files
	ModifiedCSVFiles = GoDCSV::CSVDatabase::Get()->GetAllModifiedCSVFileNames();

	// Set up the button selection state array
	ButtonSelectionState.clear();
	ButtonSelectionState = std::deque<bool>(ModifiedCSVFiles.size(), true);

	bSelectAll = true;
}

void BlockUnsavedProgress::DisplayModal()
{
	// Show the topmost message
	ImGui::Text(PopupTopMessage.c_str());
	ImGui::Dummy(ImVec2(0.f, ImGui::GetTextLineHeightWithSpacing()));

	ImGui::Text("The following CSV files have been modified:");
	ImGui::Separator();
	ImGui::Dummy(ImVec2(0.f, ImGui::GetTextLineHeightWithSpacing()));

	// Show a check/uncheck all button
	const bool bPrevSelectAll = bSelectAll;
	ImGui::Checkbox(std::format("##Checkbox_All_{}", PopupTopMessage).c_str(), &bSelectAll);
	ImGui::SameLine();

	ImGui::Text("Select/Deselect all");

	// If the value of the select all box changes, update each button selection state to match
	if (bPrevSelectAll != bSelectAll)
	{
		for (bool& ButtonState : ButtonSelectionState)
		{
			ButtonState = bSelectAll;
		}
	}

	ImGui::Separator();
	ImGui::Dummy(ImVec2(0.f, ImGui::GetTextLineHeightWithSpacing()));

	float ChildSizeY = ImGui::CalcTextSize("Pokemon Stats.csv").y * 7.f;

	// Show a selector with each CSV file name
	if(ImGui::BeginChild(std::format("##Child_{}", PopupTopMessage).c_str(), ImVec2(0, 200)))
	{
		int32_t ButtonStateIndex = 0;
		for (const auto CSVFileName : ModifiedCSVFiles)
		{
			const std::string RowIdentifierString = std::format("{}_{}", PopupTopMessage, CSVFileName);

			ImGui::Checkbox(std::format("##Checkbox_{}", RowIdentifierString).c_str(), &ButtonSelectionState.at(ButtonStateIndex));
			ButtonStateIndex++;

			ImGui::SameLine();

			ImGui::Text(std::format("{}.csv", CSVFileName).c_str());
		}
		ImGui::EndChild();
	}

	ImGui::Separator();
	float ButtonSizeX = ImGui::CalcTextSize("Don't Save").x * 2.f;

	// Render the "Save" button
	const std::string SaveButtonText = std::format("Save##{}", PopupTopMessage);

	std::vector<std::pair<std::string, std::string>> FailedCSVFiles;

	if (ImGui::Button(SaveButtonText.c_str(), ImVec2(ButtonSizeX, 0))) 
	{
		// Add all currently selected CSV files to an array so we can save them all at once
		std::vector<std::string> CSVFilesToSave;
		for (uint32_t Index = 0; Index < ModifiedCSVFiles.size(); Index++)
		{
			if (ButtonSelectionState.at(Index))
			{
				CSVFilesToSave.push_back(ModifiedCSVFiles.at(Index));
			}
		}

		// Attempt to save each modified CSV file, the return param is a list of the CSV files that failed to save
		FailedCSVFiles = GoDCSV::CSVDatabase::Get()->SaveSelectedCSVFiles(CSVFilesToSave);

		if (FailedCSVFiles.size() == 0)
		{
			// All selected CSV files saved successfully.
			SetModalStatus(OpenPopupStatus::ShouldBypass);
		}
	}

	// Render the "Don't Save" button
	ImGui::SameLine();
	const std::string DontSaveButtonText = std::format("Don't Save##{}", PopupTopMessage);

	if (ImGui::Button(DontSaveButtonText.c_str(), ImVec2(ButtonSizeX, 0)))
	{
		// Just bypass the modal without doing anything.
		SetModalStatus(OpenPopupStatus::ShouldBypass);
	}

	// Render the "Cancel" button
	ImGui::SetItemDefaultFocus();
	ImGui::SameLine();
	const std::string CancelButtonText = std::format("Cancel##{}", PopupTopMessage);

	if (ImGui::Button(CancelButtonText.c_str(), ImVec2(ButtonSizeX, 0)))
	{
		// Just close the modal without doing anything.
		// Setting the status to close vs bypass will not trigger
		// the bypass callback
		SetModalStatus(OpenPopupStatus::ShouldClose);
	}

	//ImGui::SetItemDefaultFocus();
	//ImGui::SameLine();
	//std::string CancelText = bCloseWindow ? "Cancel##0" : "Cancel##1";
	//if (ImGui::Button(CancelText.c_str(), ImVec2(BothButtonSize / 2.f, 0))) {
	//	ImGui::CloseCurrentPopup();
	//}

	if (FailedCSVFiles.size() != 0)
	{
		// Some CSV files failed to save, show Save Failed modal.
		auto ModalManager = MainEditorWindow::Get()->GetModalManager();

		std::shared_ptr<SaveFailed> Modal =
			std::make_shared<SaveFailed>(FailedCSVFiles, BypassModalCallback);

		ModalManager->SetCurrentlyActiveModal(Modal);
	}
}
