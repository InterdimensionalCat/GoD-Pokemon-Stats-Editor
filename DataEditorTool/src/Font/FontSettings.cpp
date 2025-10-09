#include "include.h"
#include "Font/FontSettings.h"

FontSettings::FontSettings() : 
	SettingsSection(GetSectionName()),
	ENFont("EN Font", "Default"),
	JPFont("JP Font", "Default"),
	FontSize("Font Size", 13),
	JPFontSizeMultiplier("JP Font Size Multiplier", 1.5f),
	FontColor("Font Color", ImColor(217, 217, 217, 255))
{

}

void FontSettings::InitFromJson(const nlohmann::ordered_json& LayoutSettings)
{
	ENFont.LoadFromJsonOrUseDefault(LayoutSettings);
	JPFont.LoadFromJsonOrUseDefault(LayoutSettings);
	FontSize.LoadFromJsonOrUseDefault(LayoutSettings);
	JPFontSizeMultiplier.LoadFromJsonOrUseDefault(LayoutSettings);
	FontColor.LoadFromJsonOrUseDefault(LayoutSettings);
}

void FontSettings::InitFromDefaults()
{
	ENFont.LoadDefaultValue();
	JPFont.LoadDefaultValue();
	FontSize.LoadDefaultValue();
	JPFontSizeMultiplier.LoadDefaultValue();
	FontColor.LoadDefaultValue();
}

void FontSettings::SaveToJson(nlohmann::ordered_json& LayoutSettings) const
{
	ENFont.SaveToJson(LayoutSettings);
	JPFont.SaveToJson(LayoutSettings);
	FontSize.SaveToJson(LayoutSettings);
	JPFontSizeMultiplier.SaveToJson(LayoutSettings);
	FontColor.SaveToJson(LayoutSettings);
}

std::string FontSettings::GetSectionName()
{
	return "Font Settings";
}

std::string FontSettings::GetENFont() const
{
	return ENFont.GetValue();
}

std::string FontSettings::GetJPFont() const
{
	return JPFont.GetValue();
}

int32_t FontSettings::GetFontSize() const
{
	return FontSize.GetValue();
}

float FontSettings::GetJPFontSizeMultiplier() const
{
	return JPFontSizeMultiplier.GetValue();
}

ImColor FontSettings::GetFontColor() const
{
	return FontColor.GetValue();
}

void FontSettings::SetENFont(const std::string& NewCurrentFont)
{
	ENFont.SetValue(NewCurrentFont);
}

void FontSettings::SetJPFont(const std::string& NewCurrentFont)
{
	JPFont.SetValue(NewCurrentFont);
}

void FontSettings::SetFontSize(const int32_t NewFontSize)
{
	FontSize.SetValue(NewFontSize);
}

void FontSettings::SetJPFontSizeMultiplier(const float NewFontSizeMultiplier)
{
	JPFontSizeMultiplier.SetValue(NewFontSizeMultiplier);
}

void FontSettings::SetFontColor(const ImColor& NewFontColor)
{
	FontColor.SetValue(NewFontColor);
}
