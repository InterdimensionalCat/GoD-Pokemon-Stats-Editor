#pragma once

#include "Settings/SettingsSection/SettingsSection.h"
#include "Settings/AppSetting.h"
#include "Util/JsonHelpers.h"

class FontSettings : public SettingsSection
{
public:

	FontSettings();

	void InitFromJson(const nlohmann::json& LayoutSettings) override;

	void InitFromDefaults() override;

	void SaveToJson(nlohmann::json& LayoutSettings) const override;

	static std::string GetSectionName();

	std::string GetCurrentENFont() const;
	std::string GetCurrentJPFont() const;
	int32_t GetFontSize() const;
	ImColor GetFontColor() const;

	void SetCurrentENFont(const std::string& NewCurrentFont);
	void SetCurrentJPFont(const std::string& NewCurrentFont);
	void SetFontSize(const int32_t NewFontSize);
	void SetFontColor(const ImColor& NewFontColor);

private:

	AppSetting<std::string> CurrentENFont;
	AppSetting<std::string> CurrentJPFont;
	AppSetting<int32_t>     FontSize;
	AppSetting<ImColor>     FontColor;
};
