#include "LearnedMoves.h"
#include "GoD-UI-Windows.h"
#include "UiSubsections/UiSubsection.h"

#include "UiSubsections/LevelUpMoves.h"
#include "UiSubsections/Egg Moves.h"

#include "Util/ItemSizeUtils.h"
#include "imgui/misc/cpp/imgui_stdlib.h"


LearnedMovesInfo::LearnedMovesInfo(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize) : UiSection(InWindowName, InPos, InSize)
{
	// Combination of:
	// Level up moves
	// Egg moves

	Subsections.push_back(std::make_shared<LevelUpMovesInfo>(this, "Level Up Moves"));
	Subsections.push_back(std::make_shared<EggMovesInfo>(this, "Egg Moves"));

	MinNeededLength = CalculateMinNeededLineLength();

	LargestLabelLength = CalculateLargestLabelLength();
	LargestElementLength = CalculateLargestElementLength();

	for (auto& Subsection : Subsections)
	{
		LargestSubsectionLabelSize = std::max(LargestSubsectionLabelSize, Subsection->CalculateLargestLabelLength());
		MinSubsectionFieldSize = std::max(MinSubsectionFieldSize, Subsection->CalculateLargestElementLength());
	}
}

void LearnedMovesInfo::UpdateElement()
{
	//auto& Style = ImGui::GetStyle();
	//auto SpaceAvailable = ImGui::GetContentRegionAvail().x;

	//float SubsectionTextBoxWidth = SpaceAvailable - LargestSubsectionLabelSize - Style.ItemInnerSpacing.x - (Style.FramePadding.x * 2);

	//// Ensure we are never smaller than the min size needed
	//if (SubsectionTextBoxWidth < MinSubsectionFieldSize)
	//{
	//	SubsectionTextBoxWidth = MinSubsectionFieldSize;
	//}

	//ImGui::PushItemWidth(SubsectionTextBoxWidth);

	UiSection::UpdateElement();

	//ImGui::PopItemWidth();
}

void LearnedMovesInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
	UiSection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
}

void LearnedMovesInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
	UiSection::SaveToPokemonStatsJson(PokemonStatsJson);
}

float LearnedMovesInfo::CalculateMinNeededLineLength() const
{
	float MaxLabelLength = CalculateLargestLabelLength();
	float MaxElementLength = CalculateLargestElementLength();

	for (auto& Subsection : Subsections)
	{
		MaxLabelLength = std::max(MaxLabelLength, Subsection->CalculateLargestLabelLength());
		MaxElementLength = std::max(MaxElementLength, Subsection->CalculateLargestElementLength());
	}

	if (MaxLabelLength < 0 && MaxElementLength < 0)
	{
		return -1;
	}

	MaxLabelLength = std::max(MaxLabelLength, 0.f);
	MaxElementLength = std::max(MaxElementLength, 0.f);

	return MaxLabelLength + MaxElementLength;
}

float LearnedMovesInfo::CalculateLargestLabelLength() const
{
	// No labels in this section
	return 0.f;
}

float LearnedMovesInfo::CalculateLargestElementLength() const
{
	// No UI elements in this section
	return 0;
}

void LearnedMovesInfo::OnFontUpdated()
{
	UiSection::OnFontUpdated();
	MinNeededLength = CalculateMinNeededLineLength();

	LargestLabelLength = CalculateLargestLabelLength();
	LargestElementLength = CalculateLargestElementLength();

	LargestSubsectionLabelSize = -1;
	MinSubsectionFieldSize = -1;

	for (auto& Subsection : Subsections)
	{
		LargestSubsectionLabelSize = std::max(LargestSubsectionLabelSize, Subsection->CalculateLargestLabelLength());
		MinSubsectionFieldSize = std::max(MinSubsectionFieldSize, Subsection->CalculateLargestElementLength());
	}
}
