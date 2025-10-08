/*****************************************************************//**
 * \file   ModifySingleCSVValue.h
 * \brief  Command to modify a single value in a CSV file.
 * 
 * \author bthomas
 * \date   October 2025
 *********************************************************************/
#pragma once
#include "Command/Command.h"

/** \brief  Command to modify a single value in a CSV file. */
class ModifySingleCSVValue : public Command {

	using CSVTypeVariant = std::variant<bool, float, int32_t, std::string>;

public:

	/**
	 * Construct a command to modify a single value in a CSV file.
	 * 
	 * The value at the specified Column/Row in the specified CSV file
	 * will be modified to match the supplied InNewValue when Execute() is called.
	 */
	ModifySingleCSVValue(
		const std::string InCSVFileName,
		const std::string InCSVFileColumn,
		const int32_t InCSVFileRow,
		const CSVTypeVariant& InNewValue
	);

	/** Execute this command, modifying the specified value in the CSV file. */
	void Execute() override;

	/** Undo this command, reverting the specified value in the CSV file to its previous value. */
	void Undo() override;

	/** Redo this command, re-applying the new value to the specified value in the CSV file. */
	void Redo() override;

	/** Get the name of this command. */
	std::string GetName() const override;

	/** Get a string representation of the changes this command performs. */
	std::string ToString() const override;

protected:

	/** Update PrevValue to the current value in the CSV file. */
	void UpdatePrevValue();

	/** The name of the CSV file this command modifies. */
	const std::string CSVFileName;

	/** The column name of the value this command modifies. */
	const std::string CSVFileColumn;

	/** The row index of the value this command modifies. */
	const int32_t CSVFileRow;

	/** The new value to set when this command is executed. */
	CSVTypeVariant NewValue;

	/** The previous value at the specified Column/Row before this command was executed. */
	CSVTypeVariant PrevValue;

};