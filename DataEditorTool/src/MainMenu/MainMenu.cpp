#include "include.h"
#include "MainMenu/MainMenu.h"
#include "MainMenu/MainMenuSections/MainMenuSection.h"

#include "MainMenu/MainMenuSections/MenuFile.h"
#include "MainMenu/MainMenuSections/MenuEdit.h"
#include "MainMenu/MainMenuSections/MenuView.h"
#include "MainMenu/MainMenuSections/MenuSettings.h"

MainMenu::MainMenu()
{
	AddSection(std::make_shared<MenuFile>());
	AddSection(std::make_shared<MenuEdit>());
	AddSection(std::make_shared<MenuView>());
	AddSection(std::make_shared<MenuSettings>());
}


void MainMenu::Tick()
{

	for (auto& Section : MenuSections)
	{
		// TODO: Make menu sections use ImGui's built in shortcuts feature
		// instead of checking manually.
		// See thread for a potential workaround that allows this:
		// https://github.com/ocornut/imgui/issues/456#issuecomment-2290384494
		Section->CheckShortcuts();
	}

	if (ImGui::BeginMainMenuBar())
	{
		// Sections will get ticked in order of priority, so
		// the lowest prio section will be displayed first.
		for (auto& Section : MenuSections)
		{
			if (ImGui::BeginMenu(Section->GetSectionName().c_str()))
			{
				Section->Tick();
				ImGui::EndMenu();
			}
		}

		ImGui::EndMainMenuBar();
	}
}

void MainMenu::AddSection(const std::shared_ptr<MainMenuSection>& InMenuSection)
{
	MenuSections.push_back(InMenuSection);

	// Sort after adding so elements are prioritized correctly.
	std::sort(MenuSections.begin(), MenuSections.end(), 
		[](const auto& lhs, const auto& rhs) 
		{
			return lhs->GetSectionPriority() < rhs->GetSectionPriority();
		}
	);
}
