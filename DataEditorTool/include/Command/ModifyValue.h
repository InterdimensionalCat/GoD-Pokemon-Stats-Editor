#pragma once
#include "Command.h"
//#include <format>

template<typename ValType>
class ModifyValueCommand : public Command {
public:

	ModifyValueCommand(std::shared_ptr<OldUiSection> InModifiedSection, std::shared_ptr<ValType> InValue, const ValType& InPrevValue, const ValType& InNextValue) : Command(InModifiedSection), Value(InValue), PrevValue(InPrevValue), NextValue(InNextValue)
	{
		FilterString = nullptr;
	}

	ModifyValueCommand(std::shared_ptr<OldUiSection> InModifiedSection, std::shared_ptr<ValType> InValue, const ValType& InPrevValue, const ValType& InNextValue, std::shared_ptr<std::string> InFilterString) : Command(InModifiedSection), Value(InValue), PrevValue(InPrevValue), NextValue(InNextValue), FilterString(InFilterString)
	{

	}

    void ExecuteCommand() override
	{
		(*Value) = NextValue;
	}

	
	void UndoCommand() override
	{
		(*Value) = PrevValue;
		if (FilterString.get() != nullptr)
		{
			(*FilterString) = "";
		}
	}

	
	void RedoCommand() override
	{
		(*Value) = NextValue;
		if (FilterString.get() != nullptr)
		{
			(*FilterString) = "";
		}
	}

	std::string GetCommandName() override
	{
		std::string TypeVal;
		if (typeid(ValType) == typeid(std::string))
		{
			TypeVal = "String";
		} 
		else if (typeid(ValType) == typeid(int32_t))
		{
			TypeVal = "Int";
		}
		else
		{
			TypeVal = typeid(ValType).name();
		}

		std::string ModifyValueString = std::format("Modify {} value", TypeVal);
		return ModifyValueString;
	}

protected:

	std::shared_ptr<ValType> Value;
	ValType PrevValue;
	ValType NextValue;

	std::shared_ptr<std::string> FilterString;
};