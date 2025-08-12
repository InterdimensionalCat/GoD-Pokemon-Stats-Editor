#pragma once

class MainMenuSection
{
public:

	MainMenuSection(const std::string& InSectionName, const uint32_t InSectionPriority);

	virtual void Tick();

	virtual void CheckShortcuts();

	std::string GetSectionName() const;

	uint32_t GetSectionPriority() const;

	bool IsProjectRootPathSet() const;

private:

	std::string SectionName;

	//TODO: Keybinds and keybind strs

	/** Used to sort sections for displaying. */
	uint32_t SectionPriority = 0;
};
