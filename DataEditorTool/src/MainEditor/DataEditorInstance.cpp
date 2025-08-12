#include "include.h"
#include "MainEditor/DataEditorInstance.h"

#include "MainEditor/MainEditorWindow.h"

std::shared_ptr<DataEditorInstance> DataEditorInstance::Instance = nullptr;

void DataEditorInstance::CreateInstance()
{
	Instance = std::make_shared<DataEditorInstance>();
}

void DataEditorInstance::DestroyInstance()
{
	Instance.reset();
}

std::shared_ptr<DataEditorInstance> DataEditorInstance::Get()
{
	return Instance;
}

void DataEditorInstance::Init()
{
	EditorWindow = std::make_shared<MainEditorWindow>();
	EditorWindow->Init();

	Running = true;
}

void DataEditorInstance::Stop()
{
	Running = false;
}

void DataEditorInstance::Exit()
{
	EditorWindow->Exit();
}

bool DataEditorInstance::IsRunning() const
{
	return Running;
}

void DataEditorInstance::PollEvents()
{
	EditorWindow->PollEvents();
}

void DataEditorInstance::Tick()
{
	EditorWindow->Tick();
}

void DataEditorInstance::Render()
{
	EditorWindow->Render();
}

void DataEditorInstance::ApplicationLoop()
{
	while (IsRunning())
	{
		// Update input.
		PollEvents();

		// Update gui and state, modify CSV data files based on user input.
		Tick();

		// Draw gui.
		Render();
	}

	Exit();
}

std::shared_ptr<MainEditorWindow> DataEditorInstance::GetMainEditorWindow()
{
	return EditorWindow;
}

//void GoDUIWindowsInstance::Tick()
//{
//	// Keyboard Shortcuts
//
//	auto FontSettings = CurrentSettings->GetFontSettings();
//	auto ActiveFont = FontSettings->GetActiveFontKey();
//
//	bool bIncreaseEnabled = (ActiveFont.second < FontSettings->MaxFontSize) && ActiveFont.first != "Default";
//	bool bDecreaseEnabled = (ActiveFont.second > FontSettings->MinFontSize) && ActiveFont.first != "Default";
//
//	auto LayoutSettings = CurrentSettings->GetLayoutSettings();
//
//	if (LayoutSettings->GetLayoutChanged())
//	{
//		LayoutSettings->SetActivePresetLayout(LayoutSettings->GetActivePresetLayout(), LayoutSettings->IsActivePresetCustom());
//	}
//
//	// End keyboard shortcuts
//
//	// Blocker Modals
//
//	// Tick the unsaved progress blocker modal first
//	UnsavedProgressBlocker->Tick();
//	SwitchRootBlocker->Tick();
//
//	if (CurrentSettings->GetLayoutSettings()->GetSaveModalActive())
//	{
//		CurrentSettings->GetLayoutSettings()->ShowSaveModal();
//	}
//
//	// Font Settings
//
//	if (FontSettings->GetFontChanged())
//	{
//		OnFontChanged();
//		FontSettings->SetFontChanged(false);
//	}
//
//	// End Font Settings
//
//	//ImGui::ShowDemoWindow(); // Show demo window! :)
//	//ImGui::ShowExampleDockSpace()
//
//	// Main Menu Bar
//}
//
//void GoDUIWindowsInstance::SetProjectRootPath()
//{
//	bool bUnsavedProgress = false;
//
//	for (auto& section : UiElements)
//	{
//		if (section->GetUnsavedProgress())
//		{
//			bUnsavedProgress = true;
//		}
//	}
//
//	if (bUnsavedProgress && !SwitchRootBlocker->GetBypassModal())
//	{
//		SwitchRootBlocker->SetEnabled(true);
//		return;
//	}
//	else
//	{
//		SwitchRootBlocker->SetBypassModal(false);
//	}
//
//	NFD_Init();
//
//	// initialize NFD
//	NFD::Guard nfdGuard;
//
//	// auto-freeing memory
//	NFD::UniquePath outPath;
//
//	// show the dialog
//	nfdresult_t result = NFD::PickFolder(outPath);
//	if (result == NFD_OKAY) {
//		std::string PathStr(outPath.get());
//
//		ProjectRootPath = PathStr;
//		bProjectRootPathSet = true;
//		OnProjectRootPathSet();
//	}
//	else if (result == NFD_CANCEL) {
//		std::cout << "Open file dialogue cancelled.\n";
//	}
//	else {
//		std::cout << "Error: " << NFD::GetError() << "\n";
//	}
//
//	// NFD::Guard will automatically quit NFD.
//}
//
//void GoDUIWindowsInstance::CloseCurrentRoot()
//{
//
//	bool bUnsavedProgress = false;
//
//	for (auto& section : UiElements)
//	{
//		if (section->GetUnsavedProgress())
//		{
//			bUnsavedProgress = true;
//		}
//	}
//
//	if (bUnsavedProgress && !SwitchRootBlocker->GetBypassModal())
//	{
//		SwitchRootBlocker->SetEnabled(true);
//		return;
//	}
//	else
//	{
//		SwitchRootBlocker->SetBypassModal(false);
//	}
//
//	Command::ClearCommandQueue();
//	UiElements.clear();
//
//	ProjectRootPath = "";
//	bProjectRootPathSet = false;
//}
//
//void GoDUIWindowsInstance::Init()
//{
//	// Set up the unsaved progress blocker modal and window close callback
//	UnsavedProgressBlocker = std::make_shared<UnsavedProgressModal>(true, "Save progress before exiting?");
//	SwitchRootBlocker = std::make_shared<UnsavedProgressModal>(false, "Save progress before closing?");
//}
//
//void GoDUIWindowsInstance::CSVLoadFail(const std::string& FailedCSV)
//{
//	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
//	toast->setTitle("Set root directory failed");
//	auto ErrorMsg = FailedCSV.c_str();
//	std::cout << std::format("Error loading CSV file: {}\n", ErrorMsg);
//	toast->setContent("Error loading CSV file: %s", ErrorMsg);
//	ImGui::InsertNotification(*toast);
//}
//
//void GoDUIWindowsInstance::GeneralLoadFail(std::exception e)
//{
//	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
//	toast->setTitle("Set root directory failed");
//	std::cout << std::format("Error loading content, CSV data is likely malformed: {}\n", e.what());
//	toast->setContent("Error loading content, CSV data is likely malformed: %s", e.what());
//	ImGui::InsertNotification(*toast);
//}
//
//void GoDUIWindowsInstance::OnProjectRootPathSet()
//{
//	// Clear prev command queue
//	Command::ClearCommandQueue();
//	UiElements.clear();
//
//	// Load CSV files
//	StatsCSV = std::make_shared<PokemonStatsCSV>();
//	TypesCSV = std::make_shared<PokemonTypesCSV>();
//	AbilitiesCSV = std::make_shared<PokemonAbilitiesCSV>();
//	ItemsCSV = std::make_shared<PokemonItemsCSV>();
//	MovesCSV = std::make_shared<PokemonMovesCSV>();
//
//	if (!StatsCSV->Init())
//	{
//		ProjectRootPath = "";
//		bProjectRootPathSet = false;
//		CSVLoadFail("Pokemon Stats.csv");
//		return;
//	}
//
//	if (!TypesCSV->Init())
//	{
//		ProjectRootPath = "";
//		bProjectRootPathSet = false;
//		CSVLoadFail("Types.csv");
//		return;
//	}
//
//	if (!AbilitiesCSV->Init())
//	{
//		ProjectRootPath = "";
//		bProjectRootPathSet = false;
//		CSVLoadFail("Abilities.csv");
//		return;
//	}
//
//	if (!ItemsCSV->Init())
//	{
//		ProjectRootPath = "";
//		bProjectRootPathSet = false;
//		CSVLoadFail("Items.csv");
//		return;
//	}
//
//	if (!MovesCSV->Init())
//	{
//		ProjectRootPath = "";
//		bProjectRootPathSet = false;
//		CSVLoadFail("Moves.csv");
//		return;
//	}
//
//	// Init UI sections
//	UiElements.clear();
//	const ImGuiViewport* MainViewport = ImGui::GetMainViewport();
//
//	// Creating UI elements can fail if CSV files are ill formed.
//	try {
//
//		// Dimensions include 1px spacing on 1 side each
//		// List dimensions, 190 x 680
//		CurrentPokemonList = std::make_shared<PokemonList>("Pokemon List", ImVec2(10, 10), ImVec2(180, 670));
//		UiElements.push_back(CurrentPokemonList);
//
//		// First half dimensions 500 x 680
//		//UiElements.push_back(std::make_shared<IdentificationInfo>("Identification Info", ImVec2(200, 10), ImVec2(300, 180)));
//		UiElements.push_back(std::make_shared<SpeciesInfo>("Species Info", ImVec2(200, 10), ImVec2(300, 180)));
//		//UiElements.push_back(std::make_shared<TypeInfo>("Type Info", ImVec2(200, 200), ImVec2(300, 85)));
//		//UiElements.push_back(std::make_shared<AbilityInfo>("Ability Info", ImVec2(200, 295), ImVec2(300, 85)));
//		//UiElements.push_back(std::make_shared<WildItemInfo>("Wild Items Info", ImVec2(200, 390), ImVec2(300, 80)));
//		UiElements.push_back(std::make_shared<BaseStatsInfo>("Base Stats", ImVec2(510, 10), ImVec2(180, 180)));
//		//UiElements.push_back(std::make_shared<EVYieldInfo>("EV Yields", ImVec2(510, 200), ImVec2(180, 180)));
//		//UiElements.push_back(std::make_shared<MiscInfo>("Misc Info", ImVec2(200, 480), ImVec2(300, 200)));
//		//UiElements.push_back(std::make_shared<EggMovesInfo>("Egg Moves", ImVec2(510, 390), ImVec2(180, 290)));
//
//		// Second Half Dimensions: 790 x 680
//		UiElements.push_back(std::make_shared<LearnedMovesInfo>("Level Up Moves and Egg Moves", ImVec2(700, 10), ImVec2(320, 490)));
//		//UiElements.push_back(std::make_shared<LevelUpMovesInfo>("Level Up Moves", ImVec2(700, 10), ImVec2(320, 490)));
//		UiElements.push_back(std::make_shared<TeachableMoveInfo>("TMs, HMs, and Tutor Moves", ImVec2(1030, 10), ImVec2(450, 490)));
//		UiElements.push_back(std::make_shared<EvolutionInfo>("Evolution Info", ImVec2(700, 510), ImVec2(780, 170)));
//
//		// set up the inital UI state for each element, but do not update the underlying json data
//		OnCurrentPokemonUpdated(0, false);
//		CurrentSettings->GetFontSettings()->SetFontChanged(true);
//	}
//	catch (std::exception e)
//	{
//		UiElements.clear();
//		ProjectRootPath = "";
//		bProjectRootPathSet = false;
//		GeneralLoadFail(e);
//
//		return;
//	}
//
//
//	CurrentPokemonList->SetUnsavedProgress(false);
//	CurrentPokemonList->SetFocusedWindow();
//
//	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Success, 2000); // <-- content can also be passed here as above
//	toast->setTitle("Root directory set");
//	auto PathStr = ProjectRootPath.string();
//	toast->setContent("%s", PathStr.c_str());
//	ImGui::InsertNotification(*toast);
//
//	glfwMaximizeWindow(window);
//}
//
//void GoDUIWindowsInstance::OnFontChanged()
//{
//	for (auto& UiElement : UiElements)
//	{
//		UiElement->OnFontUpdated();
//	}
//}
//
//void GoDUIWindowsInstance::Exit()
//{
//	// Clear undo/redo command queue.
//	Command::ClearCommandQueue();
//
//	// Save settings
//	CurrentSettings->Exit();
//}
//
//bool GoDUIWindowsInstance::Save()
//{
//	std::string CSVSaveFailTitle = "CSV Save failed";
//	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
//	if (!std::filesystem::is_directory(GetProjectRootPath()) || !bProjectRootPathSet)
//	{
//		toast->setTitle(CSVSaveFailTitle.c_str());
//		std::string RootNotSetMsg = "Project root directory not set, nothing to save.";
//		std::cout << RootNotSetMsg << "\n";
//		toast->setContent(RootNotSetMsg.c_str());
//		ImGui::InsertNotification(*toast);
//		return false;
//	}
//	for (auto& Section : UiElements)
//	{
//		Section->SaveToPokemonStatsJson(StatsCSV->GetDataObject().at(Section->GetCurrentPokemonIndex()));
//	}
//
//	try
//	{
//		StatsCSV->SaveCSV();
//	}
//	catch (const std::exception& e)
//	{
//		toast->setTitle(CSVSaveFailTitle.c_str());
//		std::cout << e.what() << "\n";
//		toast->setContent("%s", e.what());
//		ImGui::InsertNotification(*toast);
//
//		return false;
//	}
//
//	for (auto& element : UiElements)
//	{
//		element->SetUnsavedProgress(false);
//	}
//
//	toast = std::make_shared<ImGuiToast>(ImGuiToastType::Success, 2000);
//	toast->setTitle("Save Successful");
//	std::cout << "Pokemon Stats.csv saved successfully" << "\n";
//	toast->setContent("%s", "Pokemon Stats.csv saved successfully");
//	ImGui::InsertNotification(*toast);
//
//	return true;
//}
//
//void GoDUIWindowsInstance::OnCurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
//{
//	for (auto& element : UiElements)
//	{
//		element->CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
//		element->SetUnsavedProgress(false);
//	}
//
//	CurrentPokemonList->SetUnsavedProgress(true);
//}
//
//std::filesystem::path GoDUIWindowsInstance::GetProjectRootPath()
//{
//	return ProjectRootPath;
//}


