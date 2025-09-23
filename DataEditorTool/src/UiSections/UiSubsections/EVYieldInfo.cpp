#include "include.h"

#include "UiSections/UiSubsections/EVYieldInfo.h"
#include "Command/ModifyValue.h"
#include "Util/ItemSizeUtils.h"
#include "GoD-UI-Windows.h"

EVYieldInfo::EVYieldInfo(OldUiSection* InParent, const std::string& InSubsectionName) : UiSubsection(InParent, InSubsectionName)
{
	FieldLabels.insert(std::pair("HP EV", "HP EV"));
	FieldLabels.insert(std::pair("Attack EV", "Attack EV"));
	FieldLabels.insert(std::pair("Defense EV", "Defense EV"));
	FieldLabels.insert(std::pair("Sp. Atk EV", "Sp. Atk EV"));
	FieldLabels.insert(std::pair("Sp. Def EV", "Sp. Def EV"));
	FieldLabels.insert(std::pair("Speed EV", "Speed EV"));
}

void EVYieldInfo::UpdateElement()
{
	//ImGui::PushItemWidth(80);
	const int32_t PrevHP = *HPEVYield;
	if (ImGui::InputInt("HP EV", HPEVYield.get()))
	{
		Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), HPEVYield, PrevHP, *HPEVYield));
	}

	//ImGui::PushItemWidth(80);
	const int32_t PrevAtk = *AttackEVYield;
	if (ImGui::InputInt("Attack EV", AttackEVYield.get()))
	{
		Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), AttackEVYield, PrevAtk, *AttackEVYield));
	}

	//ImGui::PushItemWidth(80);
	const int32_t PrevDef = *DefenseEVYield;
	if (ImGui::InputInt("Defense EV", DefenseEVYield.get()))
	{
		Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), DefenseEVYield, PrevDef, *DefenseEVYield));
	}

	//ImGui::PushItemWidth(80);
	const int32_t PrevSpA = *SpecialAttackEVYield;
	if (ImGui::InputInt("Sp. Atk EV", SpecialAttackEVYield.get()))
	{
		Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), SpecialAttackEVYield, PrevSpA, *SpecialAttackEVYield));
	}

	//ImGui::PushItemWidth(80);
	const int32_t PrevSpD = *SpecialDefenseEVYield;
	if (ImGui::InputInt("Sp. Def EV", SpecialDefenseEVYield.get()))
	{
		Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), SpecialDefenseEVYield, PrevSpD, *SpecialDefenseEVYield));
	}

	//ImGui::PushItemWidth(80);
	const int32_t PrevSpeed = *SpeedEVYield;
	if(ImGui::InputInt("Speed EV", SpeedEVYield.get()))
	{
		Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(Parent->shared_from_this(), SpeedEVYield, PrevSpeed, *SpeedEVYield));
	}
}

void EVYieldInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
	UiSubsection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
	*HPEVYield = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "EV Yields HP");
	*AttackEVYield = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "EV Yields Attack");
	*DefenseEVYield = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "EV Yields Defense");
	*SpecialAttackEVYield = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "EV Yields Sp.Atk");
	*SpecialDefenseEVYield = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "EV Yields Sp.Def");
	*SpeedEVYield = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "EV Yields Speed");
}

void EVYieldInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
	(*PokemonStatsJson)["EV Yields HP"] = std::format("{}", *HPEVYield);
	(*PokemonStatsJson)["EV Yields Attack"] = std::format("{}", *AttackEVYield);
	(*PokemonStatsJson)["EV Yields Defense"] = std::format("{}", *DefenseEVYield);
	(*PokemonStatsJson)["EV Yields Sp.Atk"] = std::format("{}", *SpecialAttackEVYield);
	(*PokemonStatsJson)["EV Yields Sp.Def"] = std::format("{}", *SpecialDefenseEVYield);
	(*PokemonStatsJson)["EV Yields Speed"] = std::format("{}", *SpeedEVYield);
}

float EVYieldInfo::CalculateLargestLabelLength() const
{
	return GetMaxTextSize(FieldLabels).first;
}

float EVYieldInfo::CalculateLargestElementLength() const
{
	float MaxTextboxTextSize = GetMaxTextSize<std::array<std::string, 1>>({ "999" }).first;

	auto& Style = ImGui::GetStyle();

	return MaxTextboxTextSize + (Style.FramePadding.x * 2);
}