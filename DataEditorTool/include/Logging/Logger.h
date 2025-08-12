/*****************************************************************//**
 * \file   Logger.h
 * \brief  
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

template <typename... Args>
using FormatString = spdlog::format_string_t<Args...>;

class ICLogger
{
public:

	ICLogger();

	static void InitLogger();

	static void ExitLogger();

	template <typename... Args>
	inline static void Trace(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::trace(FormatString, std::forward<Args>(FormatArgs)...);
	}

	template <typename... Args>
	inline static void Debug(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::debug(FormatString, std::forward<Args>(FormatArgs)...);
	}

	template <typename... Args>
	inline static void Info(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::info(FormatString, std::forward<Args>(FormatArgs)...);
	}

	template <typename... Args>
	inline static void Warn(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::warn(FormatString, std::forward<Args>(FormatArgs)...);
	}

	template <typename... Args>
	inline static void Error(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::error(FormatString, std::forward<Args>(FormatArgs)...);
	}

	template <typename... Args>
	inline static void Critical(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::critical(FormatString, std::forward<Args>(FormatArgs)...);
	}

	template <typename... Args>
	inline static void PushInfoNotification(
		const std::string& NotificationTitle, 
		const uint32_t NotificationDuration,
		const std::format_string<Args...> FormatString, 
		Args &&...FormatArgs) 
	{
		const std::string MessageContent = std::format(FormatString, std::forward<Args>(FormatArgs)...);

		// First log the message.
		spdlog::info(MessageContent);

		// Then push the notification.
		std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Info, NotificationDuration);
		toast->setTitle(NotificationTitle.c_str());

		// const std::string MessageContent = std::format(FormatString, std::forward<Args>(FormatArgs)...);
		toast->setContent("%s", MessageContent.c_str());
		ImGui::InsertNotification(*toast);
	}

	template <typename... Args>
	inline static void PushErrorNotification(
		const std::string& NotificationTitle,
		const uint32_t NotificationDuration,
		const std::format_string<Args...> FormatString,
		Args &&...FormatArgs)
	{
		const std::string MessageContent = std::format(FormatString, std::forward<Args>(FormatArgs)...);

		// First log the message.
		spdlog::error(MessageContent);

		// Then push the notification.
		std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Error, NotificationDuration);
		toast->setTitle(NotificationTitle.c_str());

		toast->setContent("%s", MessageContent.c_str());
		ImGui::InsertNotification(*toast);
	}

private:

	void CleanUpOldLogs();

	std::shared_ptr<spdlog::logger> ConsoleAndFileLog;

	static std::shared_ptr<ICLogger> Instance;

	const uint32_t MaxLogFiles = 3;
};