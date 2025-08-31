#include "include.h"
#include "MainMenu/MainMenuSections/MainMenuSection.h"
#include "MainEditor/ProjectRoot.h"

MainMenuSection::MainMenuSection(const std::string& InSectionName, const uint32_t InSectionPriority) : 
	SectionName(InSectionName), SectionPriority(InSectionPriority)
{

}

void MainMenuSection::Tick()
{

}

void MainMenuSection::CheckShortcuts()
{

}

std::string MainMenuSection::GetSectionName() const
{
	return SectionName;
}

uint32_t MainMenuSection::GetSectionPriority() const
{
	return SectionPriority;
}

bool MainMenuSection::IsProjectRootPathSet() const
{
	return ProjectRoot::Get()->IsProjectRootSet();
}