#pragma once

#include "MainMenu/MainMenuSections/MainMenuSection.h"

class MenuEdit : public MainMenuSection
{
public:

	MenuEdit();

	virtual void Tick() override;

	virtual void CheckShortcuts() override;

private:

	bool CanUndoLastCommand();

	bool CanRedoLastCommand();

	void UndoLastCommand();

	void RedoLastCommand();
};