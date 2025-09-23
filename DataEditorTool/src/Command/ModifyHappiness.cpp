#include "include.h"
#include "GoD-UI-Windows.h"

#include "Command/ModifyHappiness.h"


ModifyHappiness::ModifyHappiness(std::shared_ptr<OldUiSection> InModifiedSection, std::shared_ptr<std::string> InStringVal, std::shared_ptr<int32_t> InValue, const int32_t& InPrevValue, const int32_t& InNextValue) : ModifyValueCommand(InModifiedSection, InValue, InPrevValue, InNextValue), StringVal(InStringVal)
{
}

void ModifyHappiness::ExecuteCommand()
{
	ModifyValueCommand::ExecuteCommand();
	UpdateStringVal();
}

void ModifyHappiness::UndoCommand()
{
	ModifyValueCommand::UndoCommand();
	UpdateStringVal();
}

void ModifyHappiness::RedoCommand()
{
	ModifyValueCommand::RedoCommand();
	UpdateStringVal();
}

void ModifyHappiness::UpdateStringVal()
{
	*StringVal = std::format("{:x}", *Value);
	std::transform(StringVal->begin(), StringVal->end(), StringVal->begin(), ::toupper);
	*StringVal = std::format("{} (0x{})", *Value, *StringVal);
}
