#pragma once
#include "Command/Command.h"

class TabCSVState;

class ChangeRow : public Command {

public:

	ChangeRow(
		TabCSVState* InTabState,
		const int32_t InNewRow
	);

	void Execute() override;

	void Undo() override;

	void Redo() override;

	std::string GetName() const override;

	std::string ToString() const override;

protected: 

	TabCSVState* TabState;

	const int32_t NewRow;

	int32_t PrevRow;

};