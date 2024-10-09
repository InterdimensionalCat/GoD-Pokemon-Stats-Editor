// GoD-UI-Windows.cpp : Defines the entry point for the application.
//

#include "GoD-UI-Windows.h"

#include "UiSections/PokemonList.h"
#include "UiSections/UiSubsections/IdentificationInfo.h"
#include "UiSections/UiSubsections/TypeInfo.h"
#include "UiSections/UiSubsections/AbilityInfo.h"
#include "UiSections/UiSubsections/WildItemInfo.h"
#include "UiSections/BaseStats.h"
#include "UiSections/UiSubsections/EvYieldInfo.h"
#include "UiSections/UiSubsections/LevelUpMoves.h"
#include "UiSections/TeachableMoveInfo.h"
#include "UiSections/EvolutionInfo.h"
#include "UiSections/UiSubsections/MiscInfo.h"
#include "UiSections/UiSubsections/Egg Moves.h"

#include "UiSections/SpeciesInfo.h"
#include "UiSections/LearnedMoves.h"

#include "Settings/FontSettings.h"
#include "Settings/LayoutSettings.h"

#include "imgui/backends/ImGuiNotify.hpp"

// Hide console on windows release
#if debug_mode

#else
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

GoDUIWindowsInstance GoDUIWindowsInstance::instance;

void GoDUIWindowsInstance::ApplicationLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		// Poll events.
		glfwPollEvents();

		// update GUI and state
		Tick();

		// render the GUI
		Render();
	}
}

void GoDUIWindowsInstance::Tick()
{
	// Set Project Root shortcut (Ctrl+O)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_O, false) && (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{
		SetProjectRootPath();
	}

	// Set Project Root shortcut (Ctrl+S)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_S, false) && (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{
		if (bProjectRootPathSet)
		{
			Save();
		}
	}

	// Undo shortcut (Ctrl+Z)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Z, false) && (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{
		if (Command::CanUndo())
		{
			Command::Undo();
		}
	}

	// Redo shortcut (Ctrl+Y)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Y, false) && (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{
		if (Command::CanRedo())
		{
			Command::Redo();
		}
	}

	auto FontSettings = CurrentSettings->GetFontSettings();
	auto ActiveFont = FontSettings->GetActiveFontKey();

	bool bIncreaseEnabled = (ActiveFont.second < FontSettings->MaxFontSize) && ActiveFont.first != "Default";
	bool bDecreaseEnabled = (ActiveFont.second > FontSettings->MinFontSize) && ActiveFont.first != "Default";

	// Increase Font Size (Ctrl+=)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Equal, false) && (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{
		if (bIncreaseEnabled)
		{
			FontSettings->SetActiveFont(FontKey(ActiveFont.first, ActiveFont.second + 1));
		}
	}

	// Redo shortcut (Ctrl+-)
	if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Minus, false) && (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey::ImGuiKey_RightCtrl)))
	{
		if (bDecreaseEnabled)
		{
			FontSettings->SetActiveFont(FontKey(ActiveFont.first, ActiveFont.second - 1));
		}
	}

	auto LayoutSettings = CurrentSettings->GetLayoutSettings();

	if (LayoutSettings->GetLayoutChanged())
	{
		LayoutSettings->SetActivePresetLayout(LayoutSettings->GetActivePresetLayout(), LayoutSettings->IsActivePresetCustom());
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	ImGui::PushStyleColor(ImGuiCol_Text, CurrentSettings->GetFontSettings()->GetFontColor().Value);
	ImGui::PushFont(CurrentSettings->GetFontSettings()->GetCurrentFont());

	// Tick the unsaved progress blocker modal first
	UnsavedProgressBlocker->Tick();
	SwitchRootBlocker->Tick();

	if (CurrentSettings->GetLayoutSettings()->GetSaveModalActive())
	{
		CurrentSettings->GetLayoutSettings()->ShowSaveModal();
	}


	if (FontSettings->GetFontChanged())
	{
		OnFontChanged();
		FontSettings->SetFontChanged(false);
	}

	//ImGui::ShowDemoWindow(); // Show demo window! :)
	//ImGui::ShowExampleDockSpace()

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Set Root Folder", "Ctrl+O"))
			{
				SetProjectRootPath();
			}
			if (ImGui::MenuItem("Save Stats.CSV", "Ctrl+S", nullptr, bProjectRootPathSet))
			{
				Save();
			}
			if (ImGui::MenuItem("Close", "", nullptr, bProjectRootPathSet))
			{
				CloseCurrentRoot();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if(ImGui::MenuItem("Undo", "Ctrl+Z", nullptr, Command::CanUndo()))
			{
				Command::Undo();
			}

			if(ImGui::MenuItem("Redo", "Ctrl+Y", nullptr, Command::CanRedo()))
			{
				Command::Redo();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			CurrentSettings->GetFontSettings()->DisplayFontMenu();
			CurrentSettings->GetLayoutSettings()->DisplayLayoutMenu();
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	// Notifications style setup
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f); // Disable round borders
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f); // Disable borders

	// Notifications color setup
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.10f, 0.10f, 0.10f, 1.00f)); // Background color

	// Main rendering function
	ImGui::RenderNotifications();

	//——————————————————————————————— WARNING ———————————————————————————————
	// Argument MUST match the amount of ImGui::PushStyleVar() calls 
	ImGui::PopStyleVar(2);
	// Argument MUST match the amount of ImGui::PushStyleColor() calls 
	ImGui::PopStyleColor(1);

	// Dock entire viewport
	ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

	// Main window.
	//ImGuiViewport* viewport = ImGui::GetMainViewport();
	//ImGui::SetNextWindowPos(viewport->WorkPos);
	//ImGui::SetNextWindowSize(viewport->WorkSize);
	//ImGui::SetNextWindowViewport(viewport->ID);
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);


	//ImGuiWindowFlags MainWindowFlags = 0;
	//MainWindowFlags |= ImGuiWindowFlags_NoCollapse;
	//MainWindowFlags |= ImGuiWindowFlags_NoFocusOnAppearing;
	//MainWindowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
	//MainWindowFlags |= ImGuiWindowFlags_NoMove;
	//MainWindowFlags |= ImGuiWindowFlags_NoDecoration;
	//MainWindowFlags |= ImGuiWindowFlags_NoResize;
	//MainWindowFlags |= ImGuiWindowFlags_NoNav;
	//MainWindowFlags |= ImGuiWindowFlags_NoNavFocus;
	//MainWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

	//ImGui::Begin("Pokemon Stats Editor##mainwindow", nullptr, MainWindowFlags);
	//ImGui::End();
	//ImGui::PopStyleVar(1);

	if (bProjectRootPathSet)
	{
		for (auto& UiElement : UiElements)
		{
			UiElement->Tick();
		}
	}

	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void GoDUIWindowsInstance::Render()
{
	// clear framebuffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Swap buffers
	glfwSwapBuffers(window);
}

void GoDUIWindowsInstance::SetProjectRootPath()
{
	bool bUnsavedProgress = false;

	for (auto& section : UiElements)
	{
		if (section->GetUnsavedProgress())
		{
			bUnsavedProgress = true;
		}
	}

	if (bUnsavedProgress && !SwitchRootBlocker->GetBypassModal())
	{
		SwitchRootBlocker->SetEnabled(true);
		return;
	}
	else
	{
		SwitchRootBlocker->SetBypassModal(false);
	}

	NFD_Init();

	// initialize NFD
	NFD::Guard nfdGuard;

	// auto-freeing memory
	NFD::UniquePath outPath;

	// show the dialog
	nfdresult_t result = NFD::PickFolder(outPath);
	if (result == NFD_OKAY) {
		std::string PathStr(outPath.get());

		ProjectRootPath = PathStr;
		bProjectRootPathSet = true;
		OnProjectRootPathSet();
	}
	else if (result == NFD_CANCEL) {
		std::cout << "Open file dialogue cancelled.\n";
	}
	else {
		std::cout << "Error: " << NFD::GetError() << "\n";
	}

	// NFD::Guard will automatically quit NFD.
}

void GoDUIWindowsInstance::CloseCurrentRoot()
{

	bool bUnsavedProgress = false;

	for (auto& section : UiElements)
	{
		if (section->GetUnsavedProgress())
		{
			bUnsavedProgress = true;
		}
	}

	if (bUnsavedProgress && !SwitchRootBlocker->GetBypassModal())
	{
		SwitchRootBlocker->SetEnabled(true);
		return;
	}
	else
	{
		SwitchRootBlocker->SetBypassModal(false);
	}

	Command::ClearCommandQueue();
	UiElements.clear();

	ProjectRootPath = "";
	bProjectRootPathSet = false;
}

void GoDUIWindowsInstance::Init()
{
	// Init GLFW
	if (!glfwInit())
	{
		// Initialization failed, throw error
		throw std::exception("GLFW Initialization failed!");
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;         // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;			  // Enable docking

	// Load settings.
	CurrentSettings = std::make_shared<AppSettings>();
	CurrentSettings->Init();

	// create glfw window
	window = glfwCreateWindow(1600, 900, "GoD Pokemon Stats Editor", NULL, NULL);

	//glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_TRUE);

	if (!window)
	{
		// Window or OpenGL context creation failed
		throw std::exception("GLFW Window creation failed!");
	}

	// Get current OpenGL context
	glfwMakeContextCurrent(window);

	// Load GLAD
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Setup Platform/Renderer backends for ImGUI
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	// Set up the unsaved progress blocker modal and window close callback
	UnsavedProgressBlocker = std::make_shared<UnsavedProgressModal>(true, "Save progress before exiting?");
	SwitchRootBlocker = std::make_shared<UnsavedProgressModal>(false, "Save progress before closing?");
	glfwSetWindowCloseCallback(window, GoDUIWindowsInstance::WindowCloseCallback);
}

void GoDUIWindowsInstance::CSVLoadFail(const std::string& FailedCSV)
{
	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
	toast->setTitle("Set root directory failed");
	auto ErrorMsg = FailedCSV.c_str();
	std::cout << std::format("Error loading CSV file: {}\n", ErrorMsg);
	toast->setContent("Error loading CSV file: %s", ErrorMsg);
	ImGui::InsertNotification(*toast);
}

void GoDUIWindowsInstance::GeneralLoadFail(std::exception e)
{
	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
	toast->setTitle("Set root directory failed");
	std::cout << std::format("Error loading content, CSV data is likely malformed: {}\n", e.what());
	toast->setContent("Error loading content, CSV data is likely malformed: %s", e.what());
	ImGui::InsertNotification(*toast);
}

void GoDUIWindowsInstance::OnProjectRootPathSet()
{
	// Clear prev command queue
	Command::ClearCommandQueue();
	UiElements.clear();

	// Load CSV files
	StatsCSV = std::make_shared<PokemonStatsCSV>();
	TypesCSV = std::make_shared<PokemonTypesCSV>();
	AbilitiesCSV = std::make_shared<PokemonAbilitiesCSV>();
	ItemsCSV = std::make_shared<PokemonItemsCSV>();
	MovesCSV = std::make_shared<PokemonMovesCSV>();

	if (!StatsCSV->Init())
	{
		ProjectRootPath = "";
		bProjectRootPathSet = false;
		CSVLoadFail("Pokemon Stats.csv");
		return;
	}

	if (!TypesCSV->Init())
	{
		ProjectRootPath = "";
		bProjectRootPathSet = false;
		CSVLoadFail("Types.csv");
		return;
	}

	if (!AbilitiesCSV->Init())
	{
		ProjectRootPath = "";
		bProjectRootPathSet = false;
		CSVLoadFail("Abilities.csv");
		return;
	}

	if (!ItemsCSV->Init())
	{
		ProjectRootPath = "";
		bProjectRootPathSet = false;
		CSVLoadFail("Items.csv");
		return;
	}

	if (!MovesCSV->Init())
	{
		ProjectRootPath = "";
		bProjectRootPathSet = false;
		CSVLoadFail("Moves.csv");
		return;
	}

	// Init UI sections
	UiElements.clear();
	const ImGuiViewport* MainViewport = ImGui::GetMainViewport();

	// Creating UI elements can fail if CSV files are ill formed.
	try {

		// Dimensions include 1px spacing on 1 side each
		// List dimensions, 190 x 680
		CurrentPokemonList = std::make_shared<PokemonList>("Pokemon List", ImVec2(10, 10), ImVec2(180, 670));
		UiElements.push_back(CurrentPokemonList);

		// First half dimensions 500 x 680
		//UiElements.push_back(std::make_shared<IdentificationInfo>("Identification Info", ImVec2(200, 10), ImVec2(300, 180)));
		UiElements.push_back(std::make_shared<SpeciesInfo>("Species Info", ImVec2(200, 10), ImVec2(300, 180)));
		//UiElements.push_back(std::make_shared<TypeInfo>("Type Info", ImVec2(200, 200), ImVec2(300, 85)));
		//UiElements.push_back(std::make_shared<AbilityInfo>("Ability Info", ImVec2(200, 295), ImVec2(300, 85)));
		//UiElements.push_back(std::make_shared<WildItemInfo>("Wild Items Info", ImVec2(200, 390), ImVec2(300, 80)));
		UiElements.push_back(std::make_shared<BaseStatsInfo>("Base Stats", ImVec2(510, 10), ImVec2(180, 180)));
		//UiElements.push_back(std::make_shared<EVYieldInfo>("EV Yields", ImVec2(510, 200), ImVec2(180, 180)));
		//UiElements.push_back(std::make_shared<MiscInfo>("Misc Info", ImVec2(200, 480), ImVec2(300, 200)));
		//UiElements.push_back(std::make_shared<EggMovesInfo>("Egg Moves", ImVec2(510, 390), ImVec2(180, 290)));

		// Second Half Dimensions: 790 x 680
		UiElements.push_back(std::make_shared<LearnedMovesInfo>("Level Up Moves and Egg Moves", ImVec2(700, 10), ImVec2(320, 490)));
		//UiElements.push_back(std::make_shared<LevelUpMovesInfo>("Level Up Moves", ImVec2(700, 10), ImVec2(320, 490)));
		UiElements.push_back(std::make_shared<TeachableMoveInfo>("TMs, HMs, and Tutor Moves", ImVec2(1030, 10), ImVec2(450, 490)));
		UiElements.push_back(std::make_shared<EvolutionInfo>("Evolution Info", ImVec2(700, 510), ImVec2(780, 170)));

		// set up the inital UI state for each element, but do not update the underlying json data
		OnCurrentPokemonUpdated(0, false);
		CurrentSettings->GetFontSettings()->SetFontChanged(true);
	}
	catch (std::exception e)
	{
		UiElements.clear();
		ProjectRootPath = "";
		bProjectRootPathSet = false;
		GeneralLoadFail(e);

		return;
	}


	CurrentPokemonList->SetUnsavedProgress(false);
	CurrentPokemonList->SetFocusedWindow();

	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Success, 2000); // <-- content can also be passed here as above
	toast->setTitle("Root directory set");
	auto PathStr = ProjectRootPath.string();
	toast->setContent("%s", PathStr.c_str());
	ImGui::InsertNotification(*toast);

	glfwMaximizeWindow(window);
}

void GoDUIWindowsInstance::OnFontChanged()
{
	for (auto& UiElement : UiElements)
	{
		UiElement->OnFontUpdated();
	}
}

void GoDUIWindowsInstance::Exit()
{
	// Clear undo/redo command queue.
	Command::ClearCommandQueue();

	// Save settings
	CurrentSettings->Exit();

	// Shut down ImGUI backends
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	// Destory ImGUI context
	ImGui::DestroyContext();

	// Destroy GLFW window
	glfwDestroyWindow(window);

	// Exit GLFW
	glfwTerminate();
}

bool GoDUIWindowsInstance::Save()
{
	std::string CSVSaveFailTitle = "CSV Save failed";
	std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
	if (!std::filesystem::is_directory(GetProjectRootPath()) || !bProjectRootPathSet)
	{
		toast->setTitle(CSVSaveFailTitle.c_str());
		std::string RootNotSetMsg = "Project root directory not set, nothing to save.";
		std::cout << RootNotSetMsg << "\n";
		toast->setContent(RootNotSetMsg.c_str());
		ImGui::InsertNotification(*toast);
		return false;
	}
	for (auto& Section : UiElements)
	{
		Section->SaveToPokemonStatsJson(StatsCSV->GetDataObject().at(Section->GetCurrentPokemonIndex()));
	}

	try
	{
		StatsCSV->SaveCSV();
	}
	catch (const std::exception& e)
	{
		toast->setTitle(CSVSaveFailTitle.c_str());
		std::cout << e.what() << "\n";
		toast->setContent("%s", e.what());
		ImGui::InsertNotification(*toast);

		return false;
	}

	for (auto& element : UiElements)
	{
		element->SetUnsavedProgress(false);
	}

	toast = std::make_shared<ImGuiToast>(ImGuiToastType::Success, 2000);
	toast->setTitle("Save Successful");
	std::cout << "Pokemon Stats.csv saved successfully" << "\n";
	toast->setContent("%s", "Pokemon Stats.csv saved successfully");
	ImGui::InsertNotification(*toast);

	return true;
}

void GoDUIWindowsInstance::OnCurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
	for (auto& element : UiElements)
	{
		element->CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
		element->SetUnsavedProgress(false);
	}

	CurrentPokemonList->SetUnsavedProgress(true);
}

void GoDUIWindowsInstance::WindowCloseCallback(GLFWwindow* window)
{
	auto& instance = GoDUIWindowsInstance::instance;

	bool bUnsavedProgress = false;

	for (auto& section : instance.UiElements)
	{
		if (section->GetUnsavedProgress())
		{
			bUnsavedProgress = true;
		}
	}

	if (bUnsavedProgress && !instance.UnsavedProgressBlocker->GetBypassModal())
	{
		instance.UnsavedProgressBlocker->SetEnabled(true);
		glfwSetWindowShouldClose(window, GLFW_FALSE);
	}
	else 
	{
		instance.UnsavedProgressBlocker->SetBypassModal(false);
	}
}

std::filesystem::path GoDUIWindowsInstance::GetProjectRootPath()
{
	return ProjectRootPath;
}

int main()
{
	// Set the Game Files path
	//GoDUIWindowsInstance::instance.SetProjectRootPath();

	// init all needed contexts
	GoDUIWindowsInstance::instance.Init();

	// Main loop
	GoDUIWindowsInstance::instance.ApplicationLoop();

	// Exit upon window being closed
	GoDUIWindowsInstance::instance.Exit();

	return 0;
}