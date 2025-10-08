/*****************************************************************//**
 * \file   Logger.h
 * \brief  Static class for logging messages to console and file, as well as pushing notifications to the UI.
 * 
 * \author Bennett Thomas
 * \date   August 2025
 *********************************************************************/
#pragma once

template <typename... Args>
using FormatString = spdlog::format_string_t<Args...>;

/**
 * \brief  Static class for logging messages to console and file, as well as pushing notifications to the UI.
 */
class ICLogger
{
public:

	/**
	 * Construct an IC logger, initializing all sinks we want for the logger.
	 * 
	 * Currently we use three sinks:
	 * 
	 * 1) A colored console sink for outputting to the console window.
	 * 2) A daily file sink that outputs a dated log file every time we run the program.
	 *	- Once a maximum number of log files has been reached, we will delete the oldest files
	 * 3) A basic file sink that saves the log from the latest session.
	 */
	ICLogger();

	/** Initialize the global logger instance. */
	static void InitLogger();

	/**
	 * Shutdown the global logger instance. 
	 * This will cause old log files to be deleted if necessary.
	 */
	static void ExitLogger();

	/** Log a trace severity message. */
	template <typename... Args>
	inline static void Trace(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::trace(FormatString, std::forward<Args>(FormatArgs)...);
	}

	/** Log a debug severity message. */
	template <typename... Args>
	inline static void Debug(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::debug(FormatString, std::forward<Args>(FormatArgs)...);
	}

	/** Log an info severity message. */
	template <typename... Args>
	inline static void Info(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::info(FormatString, std::forward<Args>(FormatArgs)...);
	}

	/** Log a warn severity message. */
	template <typename... Args>
	inline static void Warn(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::warn(FormatString, std::forward<Args>(FormatArgs)...);
	}

	/** Log an error severity message. */
	template <typename... Args>
	inline static void Error(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::error(FormatString, std::forward<Args>(FormatArgs)...);
	}

	/** Log a critical severity message. */
	template <typename... Args>
	inline static void Critical(const FormatString<Args...> FormatString, Args &&...FormatArgs) 
	{
		spdlog::critical(FormatString, std::forward<Args>(FormatArgs)...);
	}

	/**
	 * Push an info severity notification to the UI and log it to file/console.
	 * 
	 * \param NotificationTitle The title of the notification.
	 * \param NotificationDuration The duration of the notification in milliseconds.
	 * \param FormatString The format string for the notification content.
	 * \param FormatArgs The arguments for the format string.
	 */
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

		toast->setContent("%s", MessageContent.c_str());
		ImGui::InsertNotification(*toast);
	}

	/**
	 * Push a warning severity notification to the UI and log it to file/console.
	 * 
	 * \param NotificationTitle The title of the notification.
	 * \param NotificationDuration The duration of the notification in milliseconds.
	 * \param FormatString The format string for the notification content.
	 * \param FormatArgs The arguments for the format string.
	 */
	template <typename... Args>
	inline static void PushWarnNotification(
		const std::string& NotificationTitle,
		const uint32_t NotificationDuration,
		const std::format_string<Args...> FormatString,
		Args &&...FormatArgs)
	{
		const std::string MessageContent = std::format(FormatString, std::forward<Args>(FormatArgs)...);

		// First log the message.
		spdlog::warn(MessageContent);

		// Then push the notification.
		std::shared_ptr<ImGuiToast> toast = std::make_shared<ImGuiToast>(ImGuiToastType::Warning, NotificationDuration);
		toast->setTitle(NotificationTitle.c_str());

		toast->setContent("%s", MessageContent.c_str());
		ImGui::InsertNotification(*toast);
	}

	/**
	 * Push an error severity notification to the UI and log it to file/console.
	 * 
	 * \param NotificationTitle The title of the notification.
	 * \param NotificationDuration The duration of the notification in milliseconds.
	 * \param FormatString The format string for the notification content.
	 * \param FormatArgs The arguments for the format string.
	 */
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

	/** Delete old log files if we have exceeded the maximum number of log files allowed. */
	void CleanUpOldLogs();

	/** spdlog logger object that all our log sinks write to. */
	std::shared_ptr<spdlog::logger> ConsoleAndFileLog;

	/** The global instance of the ICLogger. */
	static std::shared_ptr<ICLogger> Instance;

	/** The maximum number of dated log files to keep on disk. */
	const uint32_t MaxLogFiles = 10;
};