#pragma once
#include "Command/Command.h"

class ModifySingleCSVValue : public Command {

	using CSVTypeVariant = std::variant<bool, float, int32_t, std::string>;

public:

	ModifySingleCSVValue(
		const std::string InCSVFileName,
		const std::string InCSVFileColumn,
		const int32_t InCSVFileRow,
		const CSVTypeVariant& InNewValue
	);

	void Execute() override;

	void Undo() override;

	void Redo() override;

	std::string GetName() const override;

	std::string ToString() const override;

protected:

	void UpdatePrevValue();

	const std::string CSVFileName;
	const std::string CSVFileColumn;
	const int32_t CSVFileRow;

	CSVTypeVariant NewValue;

	CSVTypeVariant PrevValue;

};