#include "include.h"

#include "UiSections/SpeciesInfo.h"
#include "UiSections/PokemonList.h"
#include "UiSections/UiSubsections/IdentificationInfo.h"
#include "UiSections/UiSubsections/TypeInfo.h"
#include "UiSections/UiSubsections/AbilityInfo.h"
#include "UiSections/UiSubsections/WildItemInfo.h"
#include "UiSections/UiSubsections/EVYieldInfo.h"
#include "UiSections/UiSubsections/MiscInfo.h"

#include "Command/ModifyValue.h"
#include "Util/TextureLoader.h"
#include "Util/ItemSizeUtils.h"
#include "GoD-UI-Windows.h"

std::deque<GLuint> SpeciesInfo::PokefaceData;

SpeciesInfo::SpeciesInfo(const std::string& InWindowName, const ImVec2& InPos, const ImVec2& InSize) : UiSection(InWindowName, InPos, InSize)
{
    // Combination of:
    // Identification info
    // Type info
    // Ability info
    // Wild Items info
    // EV yield
    // Misc info

	SpeciesLabel = "Species";

    Subsections.push_back(std::make_shared<IdentificationInfo>(this, "Identification Info"));
    Subsections.push_back(std::make_shared<TypeInfo>(this, "Type Info"));
    Subsections.push_back(std::make_shared<AbilityInfo>(this, "Ability Info"));
    Subsections.push_back(std::make_shared<WildItemInfo>(this, "Wild Items Info"));
    Subsections.push_back(std::make_shared<EVYieldInfo>(this, "EV Yields"));
    Subsections.push_back(std::make_shared<MiscInfo>(this, "Misc Info"));

	auto& Style = ImGui::GetStyle();

	MinTextBoxSize = GetMaxTextSize(GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey("Entry Name", false)).first + (float)Style.FramePadding.x + (float)Style.ItemInnerSpacing.x;

	MinNeededLength = CalculateMinNeededLineLength();

	LargestLabelLength = CalculateLargestLabelLength();
	LargestElementLength = CalculateLargestElementLength();

	for (auto& Subsection : Subsections)
	{
		LargestSubsectionLabelSize = std::max(LargestSubsectionLabelSize, Subsection->CalculateLargestLabelLength());
		MinSubsectionFieldSize = std::max(MinSubsectionFieldSize, Subsection->CalculateLargestElementLength());
	}

	if (PokefaceData.size() == 0)
	{
		auto PokemonList = GoDUIWindowsInstance::instance.StatsCSV->GetPokemonList();
		PokefaceData = std::deque<GLuint>(PokemonList.size(), 0);
	}

	InitPokefaceData();
}

void SpeciesInfo::UpdateElement()
{

	ImGui::Text(SpeciesLabel.c_str());
	ImGui::SameLine();

	auto TextLength = ImGui::GetItemRectMax().x;

	auto& Style = ImGui::GetStyle();

	//auto SpaceAvailable = ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x;
	auto SpaceAvailable = ImGui::GetContentRegionAvail().x;

	bool bShowPokefaceOnNextLine = false;

	float SpeciesTextBoxWidth = SpaceAvailable - PokefaceImageSize - (Style.ItemSpacing.x) - (Style.FramePadding.x * 2);

	// Ensure we are never smaller than the min size needed
	if (SpeciesTextBoxWidth < MinTextBoxSize)
	{
		SpeciesTextBoxWidth = MinTextBoxSize;
		bShowPokefaceOnNextLine = true;
	}

	ImGui::BeginDisabled();
    ImGui::PushItemWidth(SpeciesTextBoxWidth);

    std::string CurrentlySelectedPokemon = GoDUIWindowsInstance::instance.CurrentPokemonList->GetPokemonListItems().at(GetCurrentPokemonIndex());
    ImGui::InputText("##SelectedSpecies", &CurrentlySelectedPokemon);

	ImGui::PopItemWidth();
    ImGui::EndDisabled();

    if (PokefaceData.size() != 0)
    {
		if (PokefaceData.at(GetCurrentPokemonIndex()) != 0)
		{
			//ImGui::Dummy(ImVec2(ImGui::GetContentRegionAvail().x - 100, 100));
			GLuint TextureData = PokefaceData.at(GetCurrentPokemonIndex());
			if (!bShowPokefaceOnNextLine)
			{
				ImGui::SameLine();
			}
			ImGui::Image((void*)(intptr_t)TextureData, ImVec2(PokefaceImageSize, PokefaceImageSize));
			ImGui::Separator();
		}
    }

	float SubsectionTextBoxWidth = SpaceAvailable - LargestSubsectionLabelSize - Style.ItemInnerSpacing.x - (Style.FramePadding.x * 2);

	// Ensure we are never smaller than the min size needed
	if (SubsectionTextBoxWidth < MinSubsectionFieldSize)
	{
		SubsectionTextBoxWidth = MinSubsectionFieldSize;
	}

	ImGui::PushItemWidth(SubsectionTextBoxWidth);

	UiSection::UpdateElement();

	ImGui::PopItemWidth();
}

void SpeciesInfo::CurrentPokemonUpdated(const int32_t NewPokemonIndex, const bool ShouldSave)
{
    UiSection::CurrentPokemonUpdated(NewPokemonIndex, ShouldSave);
}

void SpeciesInfo::SaveToPokemonStatsJson(std::shared_ptr<nlohmann::json> PokemonStatsJson)
{
    UiSection::SaveToPokemonStatsJson(PokemonStatsJson);
}

float SpeciesInfo::CalculateMinNeededLineLength() const
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

float SpeciesInfo::CalculateLargestLabelLength() const
{
	// The largest (and only) label is the species text box label
	return GetMaxTextSize<std::array<std::string, 1>>(std::array<std::string, 1>{SpeciesLabel}).first;
}

float SpeciesInfo::CalculateLargestElementLength() const
{
	// The largest (and only) line has a text input box for the entry name stat, and a pokeface picture
	return MinTextBoxSize + PokefaceImageSize; // +(ImGuiStyleVar_FramePadding * 4);
}

void SpeciesInfo::OnFontUpdated()
{
	UiSection::OnFontUpdated();
	auto& Style = ImGui::GetStyle();

	MinTextBoxSize = GetMaxTextSize(GoDUIWindowsInstance::instance.StatsCSV->GetAllEntriesOfKey("Entry Name", false)).first + (float)Style.FramePadding.x + (float)Style.ItemInnerSpacing.x;

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

void SpeciesInfo::InitPokefaceData()
{
	try
	{
		std::filesystem::path BasePath = std::filesystem::current_path();
		BasePath /= "Resources";
		BasePath /= "PokeFace";

		if (!std::filesystem::is_directory(BasePath))
		{
			std::string ErrorMessage = std::format("{} is not a directory", BasePath.string());
			throw std::exception(ErrorMessage.c_str());
			return;
		}

		auto PokemonList = GoDUIWindowsInstance::instance.StatsCSV->GetPokemonList();
		//PokefaceData = std::deque<GLuint>(PokemonList.size(), 0);

		for (int32_t i = 0; i < PokemonList.size(); i++)
		{
			if (PokefaceData.at(i) != 0)
			{
				continue;
			}
			try
			{
				const std::string& Filename = std::format("face_{:03}.png", i);

				std::filesystem::path PathToFace = BasePath / Filename;
				if (!std::filesystem::exists(PathToFace))
				{
					std::string ErrorMessage = std::format("File {} not found", Filename);
					throw std::exception(ErrorMessage.c_str());
					continue;
				}

				int Width = 0;
				int Height = 0;

				bool Success = LoadTextureFromFile(PathToFace.string().c_str(), &PokefaceData.at(i), &Width, &Height);
				if (!Success)
				{
					std::string ErrorMessage = std::format("Error parsing file {}", Filename);
					throw std::exception(ErrorMessage.c_str());
					continue;
				}
			}
			catch (const std::exception& e)
			{
				HandlePokefaceLoadingException(i, e);
				continue;
			}
		}
	} 
	catch (const std::exception& e)
	{
		PokefaceData.clear();
		HandlePokefaceLoadingException(-1, e);
	}
}

void SpeciesInfo::HandlePokefaceLoadingException(const int32_t index, const std::exception& e)
{
	if (index < 0)
	{
		std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
		const std::string TitleMsg = "Pokeface loading failed";
		toast->setTitle(TitleMsg.c_str());
		const std::string ErrorMsg = std::format("Pokeface images will not be displayed: {}", e.what());
		std::cout << TitleMsg << ": " << ErrorMsg << "\n";
		toast->setContent("%s", ErrorMsg.c_str());
		ImGui::InsertNotification(*toast);
	}
	else
	{
		std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, 2000);
		const std::string TitleMsg = std::format("Pokeface #{} loading failed", index);
		toast->setTitle(TitleMsg.c_str());
		const std::string ErrorMsg = std::format("Pokeface for pokemon #{} will not be displayed: {}", index, e.what());
		std::cout << TitleMsg << ": " << ErrorMsg << "\n";
		toast->setContent("%s", ErrorMsg.c_str());
		ImGui::InsertNotification(*toast);
	}
}
