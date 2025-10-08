/*****************************************************************//**
 * \file   ChangeRow.h
 * \brief  Command to change a UiTab's current row in its TabCSVState.
 * 
 * \author Bennett Thomas
 * \date   October 2025
 *********************************************************************/
#pragma once
#include "Command/Command.h"

class TabCSVState;

/** \brief  Command to change a UiTab's current row in its TabCSVState. */
class ChangeRow : public Command {

public:

	/**
	 * Construct a ChangeRow command that will change the current row
	 * of the supplied TabCSVState to InNewRow when executed.
	 */
	ChangeRow(
		TabCSVState* InTabState,
		const int32_t InNewRow
	);

	/** Execute this command, changing the current row to NewRow. */
	void Execute() override;

	/** Undo this command, changing the current row back to PrevRow. */
	void Undo() override;

	/** Redo this command, changing the current row to NewRow again. */
	void Redo() override;

	/** Get the name of this command. */
	std::string GetName() const override;

	/** Get a string representation of the changes this command performs. */
	std::string ToString() const override;

protected: 

	/** The TabCSVState whose current row will be changed. */
	TabCSVState* TabState;

	/** The row to change to when this command is executed or redone. */
	const int32_t NewRow;

	/** The row to change back to when this command is undone. */
	int32_t PrevRow;

};