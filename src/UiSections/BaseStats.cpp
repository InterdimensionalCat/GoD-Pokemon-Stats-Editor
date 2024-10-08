#include "BaseStats.h"
#include "GoD-UI-Windows.h"
#include "Command/ModifyValue.h"
#include "Util/ItemSizeUtils.h"

#include "imgui/backends/ImGuiNotify.hpp"
#include "imgui/misc/cpp/imgui_stdlib.h"

BaseStatsInfo::BaseStatsInfo(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize) : UiSection(InWindowName, InPos, InSize)
{
	MinNeededLength = CalculateMinNeededLineLength();

	LargestLabelLength = CalculateLargestLabelLength();
	LargestElementLength = CalculateLargestElementLength();
}

void BaseStatsInfo::UpdateElement()
{
	//float MaxTextLength = -1.f;
	//for (auto& str : BaseStatStrings)
	//{
	//	MaxTextLength = std::max(ImGui::CalcTextSize(str.c_str()).x, MaxTextLength);
	//}

	UpdateStat(BaseHP, "HP", LargestLabelLength);
	UpdateStat(BaseAttack, "Attack", LargestLabelLength);
	UpdateStat(BaseDefense, "Defense", LargestLabelLength);
	UpdateStat(BaseSpecialAttack, "Sp. Atk", LargestLabelLength);
	UpdateStat(BaseSpecialDefense, "Sp. Def", LargestLabelLength);
	UpdateStat(BaseSpeed, "Speed", LargestLabelLength);

	std::string Total = "Total";
	std::string TotalNum = std::format("{}", *BaseHP + *BaseAttack + *BaseDefense + *BaseSpecialAttack + *BaseSpecialDefense + *BaseSpeed);
	auto TotalTextLength = ImGui::CalcTextSize(Total.c_str()).x;
	ImGui::Dummy(ImVec2(LargestLabelLength - TotalTextLength, 1));
	std::string TotalFormatted = std::format("{}:", Total);
	ImGui::SameLine();
	ImGui::Text(TotalFormatted.c_str());
	ImGui::SameLine();

	auto& Style = ImGui::GetStyle();

	auto IntInputTextSize = ImGui::CalcTextSize("999", 0, true).x;
	IntInputTextSize += Style.ItemInnerSpacing.x * 2;

	float ButtonSize = ImGui::GetFrameHeight();
	ButtonSize = (ButtonSize + Style.ItemInnerSpacing.x) * 2.f;

	const float MinInputIntSize = IntInputTextSize + ButtonSize;

	ImGui::PushItemWidth(MinInputIntSize);
	int32_t BSTInt = *BaseHP + *BaseAttack + *BaseDefense + *BaseSpecialAttack + *BaseSpecialDefense + *BaseSpeed;
	ImGui::BeginDisabled();
	ImGui::InputInt("##BST", &BSTInt, 0, 0);
	ImGui::PopItemWidth();
	ImGui::EndDisabled();
}

void BaseStatsInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
	UiSection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
	*BaseHP = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Base Stats HP");
	*BaseAttack = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Base Stats Attack");
	*BaseDefense = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Base Stats Defense");
	*BaseSpecialAttack = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Base Stats Sp.Atk");
	*BaseSpecialDefense = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Base Stats Sp.Def");
	*BaseSpeed = GoDUIWindowsInstance::instance.StatsCSV->GetIntAtKeyAndIndex(NewPokemonIndex, "Base Stats Speed");
}

void BaseStatsInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
	(*PokemonStatsJson)["Base Stats HP"] = std::format("{}", *BaseHP);
	(*PokemonStatsJson)["Base Stats Attack"] = std::format("{}", *BaseAttack);
	(*PokemonStatsJson)["Base Stats Defense"] = std::format("{}", *BaseDefense);
	(*PokemonStatsJson)["Base Stats Sp.Atk"] = std::format("{}", *BaseSpecialAttack);
	(*PokemonStatsJson)["Base Stats Sp.Def"] = std::format("{}", *BaseSpecialDefense);
	(*PokemonStatsJson)["Base Stats Speed"] = std::format("{}", *BaseSpeed);
}

void BaseStatsInfo::UpdateStat(std::shared_ptr<int32_t> Stat, const std::string& StatName, const float MaxTextLength)
{
	ImGui::Dummy(ImVec2(MaxTextLength - (ImGui::CalcTextSize(StatName.c_str()).x), 1));
	ImGui::SameLine();
	auto StatNameColon = std::format("{}:", StatName);
	ImGui::Text(StatNameColon.c_str());
	ImGui::SameLine();

	auto& Style = ImGui::GetStyle();
	auto LabelLength = ImGui::GetItemRectMax().x;

	auto SpaceAvailable = ImGui::GetContentRegionAvail().x;

	auto IntInputTextSize = ImGui::CalcTextSize("999", 0, true).x;
	IntInputTextSize += Style.ItemInnerSpacing.x * 2;

	float ButtonSize = ImGui::GetFrameHeight();
	ButtonSize = (ButtonSize + Style.ItemInnerSpacing.x) * 2.f;

	const float MinInputIntSize = IntInputTextSize + ButtonSize;

	ImGui::PushItemWidth(MinInputIntSize);

	const int32_t PrevVal = *Stat;
	std::string HiddenStatName = std::format("##{}", StatName);
	if (ImGui::InputInt(HiddenStatName.c_str(), Stat.get()))
	{
		Command::PushNewCommandAndExecute(std::make_shared<ModifyValueCommand<int32_t>>(shared_from_this(), Stat, PrevVal, *Stat));
	}

	auto InputIntLength = ImGui::GetItemRectMax().x;

	ImGui::PopItemWidth();

	// Animate a simple progress bar
	static float progress = 0.0f, progress_dir = 1.0f;
	progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
	if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
	if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }

	float Progress1 = (float)(*Stat) / 127.5f;
	float Progress2 = 0.f;

	if (Progress1 >= 1.f)
	{
		Progress1 = 1.f;
		Progress2 = ((float)(*Stat) - 127.5f) / 127.5f;
		if (Progress2 >= 1.f)
		{
			Progress2 = 1.f;
		}
		Progress2 *= 1.f / 3.f;
	}

	Progress1 *= 2.f / 3.f;

	Progress1 = std::clamp(Progress1 + Progress2, 0.0f, 1.0f);

	float RColor = 1.0 - Progress1;
	float GColor = 1.0 - abs(2.f * (Progress1 - 0.5));
	RColor = std::max(0.2f, RColor);
	GColor = std::max(0.2f, GColor);

	float BColor = Progress2 * 3;
	RColor += Progress2 * 1;
	GColor += Progress2 * 1;

	BColor = std::min(BColor, 0.9f);

	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(RColor, GColor, BColor, 1.0));

	ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);

	std::string StatRangeStr = std::format("( {:3d} - {:<3d} )", 999, 999);
	float RangeSize = ImGui::CalcTextSize(StatRangeStr.c_str(), 0, true).x;
	RangeSize += Style.ItemSpacing.x;

	// dont need to include label widgets becuase space avail was calced after label was drawn
	float StatsBarWidth = SpaceAvailable - MinInputIntSize - RangeSize - Style.ItemSpacing.x - (Style.FramePadding.x * 2);

	if (StatsBarWidth < 124.f)
	{
		StatsBarWidth = 124.f;
	}

	ImGui::ProgressBar(Progress1, ImVec2(StatsBarWidth, 0.f), "");

	ImGui::PopStyleColor();

	int32_t StatLow = -1;
	int32_t StatHigh = -1;

	ImGui::SameLine();

	if (StatName != "HP")
	{
		StatLow = std::floor(((*Stat * 2) + 5) * 0.9f);
		StatHigh = std::floor(((*Stat * 2) + 5 + 31 + 63) * 1.1f);
	}
	else 
	{
		StatLow = std::floor((*Stat * 2) + 110);
		StatHigh = std::floor((*Stat * 2) + 110 + 31 + 63);

		if (*Stat == 1)
		{
			StatLow = 1;
			StatHigh = 1;
		}
	}

	if (*Stat == 0)
	{
		StatLow = 0;
		StatHigh = 0;
	}

	if (StatLow > 999)
	{
		StatLow = 999;
	}

	if (StatHigh > 999)
	{
		StatHigh = 999;
	}

	std::string StatRange = std::format("( {:3d} - {:<3d} )", StatLow, StatHigh);
	ImGui::Text(StatRange.c_str());
}

float BaseStatsInfo::CalculateMinNeededLineLength() const
{
	float MaxLabelLength = CalculateLargestLabelLength();
	float MaxElementLength = CalculateLargestElementLength();

	if (MaxLabelLength < 0 && MaxElementLength < 0)
	{
		return -1;
	}

	MaxLabelLength = std::max(MaxLabelLength, 0.f);
	MaxElementLength = std::max(MaxElementLength, 0.f);

	return MaxLabelLength + MaxElementLength;
}

float BaseStatsInfo::CalculateLargestLabelLength() const
{
	// Base stat strings contain all the labels for this section, but we need to add a colon to each.
	auto WithColon = BaseStatStrings;
	for (auto& Label : WithColon)
	{
		Label = std::format("{}:", Label);
	}
	return GetMaxTextSize(WithColon).first;
}

float BaseStatsInfo::CalculateLargestElementLength() const
{
	// Each line contains a label (covered by the largest label length...
	// Then an int input...
	// Including its step buttons...
	// Then the pokemon stats progress bars...
	// then formatted text showing the base stat ranges.

	auto& Style = ImGui::GetStyle();
	auto IntInputTextSize = GetMaxTextSize<std::array<std::string, 1>>({ "999" }).first;
	IntInputTextSize += Style.ItemInnerSpacing.x * 2;

	float ButtonSize = ImGui::GetFrameHeight();
	ButtonSize = (ButtonSize + Style.ItemInnerSpacing.x) * 2.f;

	float BarSize = 255.f + Style.ItemSpacing.x;

	std::string StatRangeStr = std::format("( {:3d} - {:<3d} )", 999, 999);
	float RangeSize = ImGui::CalcTextSize(StatRangeStr.c_str(), 0, true).x;
	RangeSize += Style.ItemSpacing.x;

	return IntInputTextSize + ButtonSize + BarSize + RangeSize + (Style.FramePadding.x * 2);
}

void BaseStatsInfo::OnFontUpdated()
{
	UiSection::OnFontUpdated();
	MinNeededLength = CalculateMinNeededLineLength();

	LargestLabelLength = CalculateLargestLabelLength();
	LargestElementLength = CalculateLargestElementLength();
}

