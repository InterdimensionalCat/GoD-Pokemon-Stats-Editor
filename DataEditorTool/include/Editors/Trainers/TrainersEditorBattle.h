/*****************************************************************//**
 * \file   TrainersEditorBattle.h
 * \brief
 *
 * \author Bennett Thomas
 * \date   December 2025
 *********************************************************************/
#pragma once

#include "UI/UiSection.h"

class TrainersEditor;
class UiCSVElement;

class TrainersEditorBattle : public UiSection
{

public:

	TrainersEditorBattle(TrainersEditor* InParent);

	virtual void Refresh() override;

	void SetCurrentRow(const int32_t InRow);

	void InitBattleInfo();

private:

	int32_t CurrentRow = 0;

	TrainersEditor* ParentEditor;

	std::vector<std::shared_ptr<UiCSVElement>> BattleElements;
};