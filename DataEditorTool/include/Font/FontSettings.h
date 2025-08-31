#pragma once

#include "Settings/SettingsSection/SettingsSection.h"
#include "Settings/AppSetting.h"
#include "Util/JsonHelpers.h"

class FontSettings : public SettingsSection
{
public:

	FontSettings();

	void InitFromJson(const nlohmann::ordered_json& LayoutSettings) override;

	void InitFromDefaults() override;

	void SaveToJson(nlohmann::ordered_json& LayoutSettings) const override;

	static std::string GetSectionName();

	std::string GetENFont() const;
	std::string GetJPFont() const;
	int32_t GetFontSize() const;
	float GetJPFontSizeMultiplier() const;
	ImColor GetFontColor() const;

	void SetENFont(const std::string& NewCurrentFont);
	void SetJPFont(const std::string& NewCurrentFont);
	void SetFontSize(const int32_t NewFontSize);
	void SetJPFontSizeMultiplier(const float NewFontSizeMultiplier);
	void SetFontColor(const ImColor& NewFontColor);

private:

	AppSetting<std::string> ENFont;
	AppSetting<std::string> JPFont;
	AppSetting<int32_t>     FontSize;
	AppSetting<float>       JPFontSizeMultiplier;
	AppSetting<ImColor>     FontColor;
};
