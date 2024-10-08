#pragma once
#include "ModifyValue.h"


class ModifyHappiness : public ModifyValueCommand<int32_t> {
public:
	ModifyHappiness(std::shared_ptr<UiSection> InModifiedSection, std::shared_ptr<std::string> InStringVal, std::shared_ptr<int32_t> InValue, const int32_t& InPrevValue, const int32_t& InNextValue);

	void ExecuteCommand() override;

	void UndoCommand() override;

	void RedoCommand() override;

private:

	void UpdateStringVal();

	std::shared_ptr<std::string> StringVal;
};