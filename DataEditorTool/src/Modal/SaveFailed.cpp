#include "include.h"
#include "Modal/SaveFailed.h"
#include "Modal/ModalManager.h"
#include "CSV/CSVDatabase.h"
#include "MainEditor/MainEditorWindow.h"

SaveFailed::SaveFailed(
	std::vector<std::pair<std::string, std::string>> InFailedCSVFiles,
	const std::function<void()>& InBypassModalCallback)
	: Modal(
		std::string("Warning: Save Failed##Some files failed to Save"),
		InBypassModalCallback
	),
	FailedCSVFiles(InFailedCSVFiles)
{

}

void SaveFailed::OnModalMadeActive()
{
	// Set up the button selection state array
	ButtonSelectionState.clear();
	ButtonSelectionState = std::deque<bool>(FailedCSVFiles.size(), true);

	bSelectAll = true;
}

void SaveFailed::DisplayModal()
{
	// Show the topmost message
	ImGui::Text(PopupTopMessage.c_str());
	ImGui::Dummy(ImVec2(0.f, ImGui::GetTextLineHeightWithSpacing()));

	ImGui::Text("The following CSV files failed to save:");
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

	float CSVMaxTextSizeX = -1.f;
	for (const auto [CSVFileName, CSVFileReason] : FailedCSVFiles)
	{
		CSVMaxTextSizeX = std::max(ImGui::CalcTextSize(std::format("{}.csv ", CSVFileName).c_str()).x, CSVMaxTextSizeX);
	}

	// Show a selector with each CSV file name
	if (ImGui::BeginChild(std::format("##Child_{}", PopupTopMessage).c_str(), ImVec2(0, 200), 0, ImGuiWindowFlags_HorizontalScrollbar))
	{
		int32_t ButtonStateIndex = 0;
		for (const auto [CSVFileName, CSVFileReason] : FailedCSVFiles)
		{
			const std::string RowIdentifierString = std::format("{}_{}", PopupTopMessage, CSVFileName);

			ImGui::Checkbox(std::format("##Checkbox_{}", RowIdentifierString).c_str(), &ButtonSelectionState.at(ButtonStateIndex));
			ButtonStateIndex++;

			ImGui::SameLine();
			const float CursorPosX = ImGui::GetCursorPosX();

			ImGui::Text(std::format("{}.csv", CSVFileName).c_str());

			ImGui::SameLine();
			ImGui::SetCursorPosX(CursorPosX + CSVMaxTextSizeX);

			ImGui::Text(std::format("| Reason: {}", CSVFileReason).c_str());
		}
		ImGui::EndChild();
	}

	ImGui::Separator();
	float ButtonSizeX = ImGui::CalcTextSize("Don't Save").x * 2.f;

	// Render the "Save" button
	const std::string SaveButtonText = std::format("Save##{}", PopupTopMessage);

	std::vector<std::pair<std::string, std::string>> NewFailedCSVFiles;

	if (ImGui::Button(SaveButtonText.c_str(), ImVec2(ButtonSizeX, 0)))
	{
		// Add all currently selected CSV files to an array so we can save them all at once
		std::vector<std::string> CSVFilesToSave;
		for (uint32_t Index = 0; Index < FailedCSVFiles.size(); Index++)
		{
			if (ButtonSelectionState.at(Index))
			{
				CSVFilesToSave.push_back(FailedCSVFiles.at(Index).first);
			}
		}

		// Attempt to save each modified CSV file, the return param is a list of the CSV files that failed to save
		NewFailedCSVFiles = GoDCSV::CSVDatabase::Get()->SaveSelectedCSVFiles(CSVFilesToSave);

		if (NewFailedCSVFiles.size() == 0)
		{
			SetModalStatus(OpenPopupStatus::ShouldBypass);
		}
	}

	// TODO: Create a "dump" button here that will dump the failed CSV files
	// to a log file so that users can manually recover their work if needed.

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

	if (NewFailedCSVFiles.size() != 0)
	{
		// Some CSV files failed to save, show Save Failed modal.
		auto ModalManager = MainEditorWindow::Get()->GetModalManager();

		std::shared_ptr<SaveFailed> Modal =
			std::make_shared<SaveFailed>(FailedCSVFiles, BypassModalCallback);

		ModalManager->SetCurrentlyActiveModal(Modal);
	}
}
