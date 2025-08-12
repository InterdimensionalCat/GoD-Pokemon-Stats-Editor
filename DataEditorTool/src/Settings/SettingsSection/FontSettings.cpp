#include "include.h"
#include "Settings/SettingsSection/FontSettings.h"

FontSettings::FontSettings() : 
	SettingsSection(GetSectionName()),
	CurrentENFont("Current EN Font", "Default"),
	CurrentJPFont("Current JP Font", "Default"),
	FontSize("Font Size", 13),
	FontColor("Font Color", ImColor(217, 217, 217, 255))
{

}

void FontSettings::InitFromJson(const nlohmann::json& LayoutSettings)
{
	CurrentENFont.LoadFromJsonOrUseDefault(LayoutSettings);
	CurrentJPFont.LoadFromJsonOrUseDefault(LayoutSettings);
	FontSize.LoadFromJsonOrUseDefault(LayoutSettings);
	FontColor.LoadFromJsonOrUseDefault(LayoutSettings);
}

void FontSettings::InitFromDefaults()
{
	CurrentENFont.LoadDefaultValue();
	CurrentJPFont.LoadDefaultValue();
	FontSize.LoadDefaultValue();
	FontColor.LoadDefaultValue();
}

void FontSettings::SaveToJson(nlohmann::json& LayoutSettings) const
{
	CurrentENFont.SaveToJson(LayoutSettings);
	CurrentJPFont.SaveToJson(LayoutSettings);
	FontSize.SaveToJson(LayoutSettings);
	FontColor.SaveToJson(LayoutSettings);
}

std::string FontSettings::GetSectionName()
{
	return "Font Settings";
}

std::string FontSettings::GetCurrentENFont() const
{
	return CurrentENFont.GetValue();
}

std::string FontSettings::GetCurrentJPFont() const
{
	return CurrentJPFont.GetValue();
}

int32_t FontSettings::GetFontSize() const
{
	return FontSize.GetValue();
}

ImColor FontSettings::GetFontColor() const
{
	return FontColor.GetValue();
}

void FontSettings::SetCurrentENFont(const std::string& NewCurrentFont)
{
	ICLogger::PushInfoNotification(
		"EN Font Changed",
		3000,
		"EN Font Changed to {}",
		NewCurrentFont
	);

	CurrentENFont.SetValue(NewCurrentFont);
}

void FontSettings::SetCurrentJPFont(const std::string& NewCurrentFont)
{
	ICLogger::PushInfoNotification(
		"JP Font Changed",
		3000,
		"JP Font Changed to {}",
		NewCurrentFont
	);

	CurrentJPFont.SetValue(NewCurrentFont);
}

void FontSettings::SetFontSize(const int32_t NewFontSize)
{
	ICLogger::PushInfoNotification(
		"Font Size Changed",
		3000,
		"Font Size Changed to {}",
		NewFontSize
	);

	FontSize.SetValue(NewFontSize);
}

void FontSettings::SetFontColor(const ImColor& NewFontColor)
{
	FontColor.SetValue(NewFontColor);
}
