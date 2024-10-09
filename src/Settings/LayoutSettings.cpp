#include "LayoutSettings.h"
#include "GoD-UI-Windows.h"

#include "imgui/backends/ImGuiNotify.hpp"
#include "imgui/misc/cpp/imgui_stdlib.h"

LayoutSettings::LayoutSettings()
{
	ResetLayoutSettings(false);
}

void LayoutSettings::Init(const nlohmann::json* LayoutSettings)
{
	// Attempt to load layout from layout settings
	try
	{
		// Find all available default and custom presets
		std::filesystem::path LayoutDirectory;
		if (GetDirectoryForLayout(LayoutDirectory, false))
		{

			for (const std::filesystem::path& File : std::filesystem::directory_iterator(LayoutDirectory))
			{
				if (File.extension() == ".ini" && File.filename() != "Default.ini")
				{
					AvailablePresetLayouts.push_back(File.filename().string());
				}
			}

			std::filesystem::path PathToDefault = LayoutDirectory / "Default.ini";

			std::sort(AvailablePresetLayouts.begin(), AvailablePresetLayouts.end(), 
				[] (const std::string& a, const std::string& b) 
				{
					auto AMod = a; 
					AMod.erase(AMod.find(".ini"), AMod.find("ini") + 4);

					auto BMod = b;
					BMod.erase(BMod.find(".ini"), BMod.find("ini") + 4);

					return AMod < BMod; 
				}
			);

			if (std::filesystem::exists(PathToDefault))
			{
				AvailablePresetLayouts.push_front(PathToDefault.filename().string());
			}
		}

		if (GetDirectoryForLayout(LayoutDirectory, true))
		{
			for (const std::filesystem::path& File : std::filesystem::directory_iterator(LayoutDirectory))
			{
				if (File.extension() == ".ini")
				{
					AvailableCustomLayouts.push_back(File.filename().string());
				}
			}

			std::sort(AvailableCustomLayouts.begin(), AvailableCustomLayouts.end(),
				[](const std::string& a, const std::string& b)
				{
					auto AMod = a;
					AMod.erase(AMod.find(".ini"), AMod.find("ini") + 4);

					auto BMod = b;
					BMod.erase(BMod.find(".ini"), BMod.find("ini") + 4);

					return AMod < BMod;
				}
			);
		}

		if (AvailablePresetLayouts.size() + AvailableCustomLayouts.size() == 0)
		{
			const std::string ErrorMsg = std::format("No custom or default preset layouts found: {}", LayoutDirectory.string());
			throw std::exception(ErrorMsg.c_str());
		}

		// Load default settings if no layout settings existed.
		if (LayoutSettings == nullptr)
		{
			ResetLayoutSettings(true);
			return;
		}

		// Attempt to load each layout setting
		bool bReloadPreset = false;
		bool bPresetCustom = false;
		std::string CurrentPreset = "Default.ini";

		try
		{
			if (LayoutSettings->find("Load Preset On Startup") == LayoutSettings->end()) {
				throw std::exception("Load Preset On Startup json object does not exist");
			}
			bReloadPreset = (*LayoutSettings)["Load Preset On Startup"];
		}
		catch (const std::exception& e)
		{
			auto ErrorMsg = std::format("Failed to find Setting: Load Preset On Startup, falling back to default: {}", e.what());
			PushLayoutSettingsErrorMsg("Layout setting not found", ErrorMsg);
		}

		// Load these two settings together, since if one isn't loaded correctly the other will be incorrect.
		try
		{
			if (LayoutSettings->find("Current Preset Custom") == LayoutSettings->end() ||
				LayoutSettings->find("Current Preset Layout") == LayoutSettings->end()) {
				throw std::exception("Current Preset Layout json object does not exist");
			}
			bool bPresetCustom = (*LayoutSettings)["Current Preset Custom"];
			std::string CurrentPreset = (*LayoutSettings)["Current Preset Layout"];
		}
		catch (const std::exception& e)
		{
			auto ErrorMsg = std::format("Failed to find Setting: Current Preset Layout, falling back to default: {}", e.what());
			PushLayoutSettingsErrorMsg("Layout setting not found", ErrorMsg);
		}

		if (!bReloadPreset)
		{
			// If we don't need to reload the preset on startup, then the already loaded ini settings should be kept
			CurrentPresetLayout = CurrentPreset;
			bCurrentPresetCustom = bPresetCustom;
			bLoadPresetOnStartup = bReloadPreset;
			return;
		}

		if (!GetDirectoryForLayout(LayoutDirectory, bPresetCustom))
		{
			const std::string ErrorMsg = std::format("Layout directory not found: {}", LayoutDirectory.string());
			throw std::exception(ErrorMsg.c_str());
		}

		if (!TryLoadLayout(LayoutDirectory, CurrentPreset))
		{
			const std::string ErrorMsg = std::format("Could not load Layout {}", CurrentPreset);
			throw std::exception(ErrorMsg.c_str());
		}

		CurrentPresetLayout = CurrentPreset;
		bCurrentPresetCustom = bPresetCustom;
		bLoadPresetOnStartup = bReloadPreset;

		std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Info, 2000);
		toast->setTitle("Layout changed");
		std::string Msg = std::format("Layout set to {}.", CurrentPresetLayout);
		std::cout << Msg << "\n";
		toast->setContent("%s", Msg.c_str());
		ImGui::InsertNotification(*toast);
	}
	catch (const std::exception& e)
	{
		auto ErrorMsg = std::format("Failed to load layout settings: {}", e.what());
		PushLayoutSettingsErrorMsg("Layout loading failed", ErrorMsg);
		//ResetLayoutSettings(true);
	}
}

void LayoutSettings::DisplayLayoutMenu()
{
	ImGui::SeparatorText("Layout Settings");

	if (ImGui::BeginMenu("Current Preset"))
	{
		ImGui::SeparatorText("Default Layouts");
		for (auto& AvailableLayout : AvailablePresetLayouts)
		{
			const bool bSelected = AvailableLayout == CurrentPresetLayout;
			if (ImGui::MenuItem(AvailableLayout.c_str(), nullptr, bSelected, !bSelected))
			{
				CurrentPresetLayout = AvailableLayout;
				bCurrentPresetCustom = false;

				SetLayoutChanged(true);
			}
		}

		ImGui::SeparatorText("Custom Layouts");
		for (auto& AvailableLayout : AvailableCustomLayouts)
		{
			const bool bSelected = (AvailableLayout == CurrentPresetLayout && bCurrentPresetCustom);
			std::string LayoutBoxName = AvailableLayout + "##Custom";
			if (ImGui::MenuItem(LayoutBoxName.c_str(), nullptr, bSelected, !bSelected))
			{
				CurrentPresetLayout = AvailableLayout;
				bCurrentPresetCustom = true;

				SetLayoutChanged(true);
			}
		}

		ImGui::EndMenu();
	}

	if (ImGui::MenuItem("Load Preset On Startup", "", bLoadPresetOnStartup, true))
	{
		bLoadPresetOnStartup = !bLoadPresetOnStartup;
	}

	if (ImGui::MenuItem("Reset layout", "", false, true))
	{
		ReloadActivePresetLayout();
	}

	if (ImGui::MenuItem("Save Current Layout", "", false, true))
	{
		SetSaveModalActive(true);
	}
}

void LayoutSettings::SetActivePresetLayout(const std::string& LayoutName, const bool IsCustomLayout)
{
	std::filesystem::path CurrentPresetDir;
	if (!GetDirectoryForLayout(CurrentPresetDir, IsCustomLayout))
	{
		auto ErrorMsg = std::format("Failed to load layout {}, directory was deleted.", LayoutName);
		PushLayoutSettingsErrorMsg("Layout loading failed", ErrorMsg);
	}

	if (TryLoadLayout(CurrentPresetDir, LayoutName))
	{
		CurrentPresetLayout = LayoutName;
		bCurrentPresetCustom = IsCustomLayout;

		std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Info, 2000);
		toast->setTitle("Layout changed");
		std::string Msg = std::format("Layout set to {}.", LayoutName);
		std::cout << Msg << "\n";
		toast->setContent("%s", Msg.c_str());
		ImGui::InsertNotification(*toast);
	}

	SetLayoutChanged(false);
}

void LayoutSettings::ReloadActivePresetLayout()
{
	SetLayoutChanged(true);
}

std::string LayoutSettings::GetActivePresetLayout() const
{
	return CurrentPresetLayout;
}

bool LayoutSettings::IsActivePresetCustom()
{
	return bCurrentPresetCustom;
}

std::deque<std::string> LayoutSettings::GetPresetLayoutsAvailable()
{
	return AvailablePresetLayouts;
}

std::deque<std::string> LayoutSettings::GetCustomLayoutsAvailable()
{
	return AvailableCustomLayouts;
}

bool LayoutSettings::TryLoadLayout(const std::filesystem::path& Directory, const std::string& LayoutFileName)
{
	try
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::ClearIniSettings();

		std::filesystem::path LayoutFilePath = Directory / LayoutFileName;

		if (!std::filesystem::exists(LayoutFilePath))
		{
			std::string ErrorMsg = std::format("Layout not found: {}", LayoutFilePath.string());
			throw std::exception(ErrorMsg.c_str());
		}

		ImGui::LoadIniSettingsFromDisk(LayoutFilePath.string().c_str());
		return true;
	}
	catch (const std::exception& e)
	{
		auto ErrorMsg = std::format("Failed to load layout {}: {}", LayoutFileName, e.what());
		PushLayoutSettingsErrorMsg("Layout loading failed", ErrorMsg);
		return false;
	}
}

void LayoutSettings::ResetLayoutSettings(const bool ReloadElements)
{
	bLoadPresetOnStartup = false;
	bCurrentPresetCustom = false;
	CurrentPresetLayout = "Default.ini";

	if (ReloadElements)
	{
		SetLayoutChanged(true);

		std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Info, 2000);
		std::string Msg;
		toast->setTitle("Layout changed");
		Msg = "Layout set to Default.";

		std::cout << Msg << "\n";
		toast->setContent("%s", Msg.c_str());
		ImGui::InsertNotification(*toast);
	}
}

void LayoutSettings::SaveLayoutSettings(nlohmann::json& LayoutSettings)
{
	LayoutSettings["Load Preset On Startup"] = bLoadPresetOnStartup;
	LayoutSettings["Current Preset Custom"] = bCurrentPresetCustom;
	LayoutSettings["Current Preset Layout"] = CurrentPresetLayout;
}

void LayoutSettings::PushLayoutSettingsErrorMsg(const std::string& ErrorTitle, const std::string& ErrorMsg)
{
	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
	toast->setTitle(ErrorTitle.c_str());
	std::cout << ErrorMsg << "\n";
	toast->setContent("%s", ErrorMsg.c_str());
	ImGui::InsertNotification(*toast);
}

void LayoutSettings::SetLayoutChanged(const bool InChanged)
{
	bLayoutChanged = InChanged;
}

bool LayoutSettings::GetLayoutChanged() const
{
	return bLayoutChanged;
}

bool LayoutSettings::GetDirectoryForLayout(std::filesystem::path& OutPath, const bool GetCustomDir) const
{
	OutPath = std::filesystem::current_path();
	OutPath /= "Resources";
	OutPath /= "Layouts";

	if (!GetCustomDir)
	{
		OutPath /= "Default Layouts";
	}
	else
	{
		OutPath /= "Custom Layouts";
	}

	if (!std::filesystem::is_directory(OutPath))
	{
		return false;
	}

	return true;
}

bool LayoutSettings::SaveNewPreset(const std::string& PresetName)
{
	try
	{
		std::filesystem::path CustomPresetPath;
		if (!GetDirectoryForLayout(CustomPresetPath, true))
		{
			std::filesystem::create_directories(CustomPresetPath);
		}

		std::filesystem::path NewPresetPath = CustomPresetPath / PresetName;

		ImGui::SaveIniSettingsToDisk(NewPresetPath.string().c_str());

		CurrentPresetLayout = PresetName;
		bCurrentPresetCustom = true;

		AvailableCustomLayouts.push_back(PresetName);

		return true;
	}
	catch (const std::exception& e)
	{
		auto ErrorMsg = std::format("Failed to save layout {}: {}", PresetName, e.what());
		PushLayoutSettingsErrorMsg("Layout loading failed", ErrorMsg);

		return false;
	}
}

void LayoutSettings::SetSaveModalActive(const bool ModalActive)
{
	if (ModalActive)
	{
		SaveModalPromptText = "Custom Layout";
		bShouldOpenSaveModal = true;
	}

	bSaveModalActive = ModalActive;
}

bool LayoutSettings::GetSaveModalActive() const
{
	return bSaveModalActive;
}

void LayoutSettings::ShowSaveModal()
{
	std::string SavePopupMsg = "Save new custom layout";

	if (bShouldOpenSaveModal)
	{
		ImGui::OpenPopup(SavePopupMsg.c_str());
		bShouldOpenSaveModal = false;
	}

	// Always center this window when appearing
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	bool SaveModalOpen = true;
	if (ImGui::BeginPopupModal(SavePopupMsg.c_str(), &SaveModalOpen, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("New preset name");
		ImGui::InputText("##Preset Name-layout", &SaveModalPromptText);
		float BothButtonSize = ImGui::GetItemRectSize().x;

		ImGui::Separator();

		bool bCloseParentModal = false;
		bool LayoutOverwriteOpen = true;
		if (ImGui::BeginPopupModal("Custom layout already exists", &LayoutOverwriteOpen, ImGuiWindowFlags_AlwaysAutoResize))
		{
			std::string OverwriteText = std::format("Overwrite custom layout: {}?", SaveModalPromptText);

			ImGui::Text(OverwriteText.c_str());
			float BothButtonConfirmSize = ImGui::GetItemRectSize().x;

			ImGui::Separator();

			std::string SaveTextConfirm = "Save##layout-confirm";

			if (ImGui::Button(SaveTextConfirm.c_str(), ImVec2(BothButtonConfirmSize / 2.f, 0))) {

				bool bSaveSuccessful = SaveNewPreset(SaveModalPromptText + ".ini");
				if (bSaveSuccessful)
				{
					bCloseParentModal = true;
				}
			}

			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			std::string CancelText = "Cancel##layout-confirm";
			if (ImGui::Button(CancelText.c_str(), ImVec2(BothButtonConfirmSize / 2.f, 0))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		if (bCloseParentModal)
		{
			SetSaveModalActive(false);
			ImGui::CloseCurrentPopup();
		}

		std::string SaveText = "Save##layout";

		if (ImGui::Button(SaveText.c_str(), ImVec2(BothButtonSize / 2.f, 0))) {

			// Show an overwrite popup if inputted file name exists
			try
			{
				std::filesystem::path SaveDir;
				if (!GetDirectoryForLayout(SaveDir, true))
				{
					throw std::exception("Directory not found");
				}
				std::filesystem::path PathToPreset = SaveDir / (std::string)(SaveModalPromptText + ".ini");

				if (std::filesystem::exists(PathToPreset))
				{
					ImGui::OpenPopup("Custom layout already exists");
				}
				else
				{
					bool bSaveSuccessful = SaveNewPreset(SaveModalPromptText + ".ini");
					if (bSaveSuccessful)
					{
						SetSaveModalActive(false);
						ImGui::CloseCurrentPopup();
					}
				}
			}
			catch (const std::exception& e)
			{

			}
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		std::string CancelText = "Cancel##layout";
		if (ImGui::Button(CancelText.c_str(), ImVec2(BothButtonSize / 2.f, 0))) {
			SetSaveModalActive(false);
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}
