#pragma once
#include "nlohmann/json.hpp"
#include <memory>

class FontSettings;
class LayoutSettings;

class AppSettings 
{
public:
	AppSettings();

	void Init();

	void Exit();

	void LoadDefaultSettings();

	std::shared_ptr<FontSettings> GetFontSettings();

	std::shared_ptr<LayoutSettings> GetLayoutSettings();

	void PushSettingsErrorMsg(const std::string& ErrorTitle, const std::string& ErrorMsg);

private:

	nlohmann::json SettingsJson;

	std::shared_ptr<FontSettings> CurrentFontSettings;
	std::shared_ptr<LayoutSettings> CurrentLayoutSettings;
};
