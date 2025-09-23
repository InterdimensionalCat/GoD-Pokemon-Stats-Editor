#include "include.h"
#include "Logging/Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/logger.h"

// TODO: Add support for file-specific log catagories (IE: LogUiTab)

// TODO: Allow logger to route crash info for std::exceptions (using std::terminate) and other crashes (such as assert or segfaults)

std::shared_ptr<ICLogger> ICLogger::Instance = nullptr;

using SinkList = std::initializer_list<std::shared_ptr<spdlog::sinks::sink>>;

ICLogger::ICLogger()
{

	auto ConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	ConsoleSink->set_level(spdlog::level::debug);
	ConsoleSink->set_pattern("[%H:%M:%S.%e] [%^%=8l%$]: %v");

	auto DailyFileSink = std::make_shared<spdlog::sinks::daily_file_format_sink_mt>("Logs/Log_%Y-%m-%d_%H.%M.%S.log", 0, 0, false, 0);
	DailyFileSink->set_level(spdlog::level::debug);
	DailyFileSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=8l%$]: %v");

	fs::path LatestPath = fs::current_path() / "Logs" / "Latest.log";

	auto LatestSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(LatestPath.make_preferred().string(), true);
	LatestSink->set_level(spdlog::level::debug);
	LatestSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=8l%$]: %v");

	ConsoleAndFileLog = std::make_shared<spdlog::logger>("ConsoleAndFileLog", SinkList{ ConsoleSink, DailyFileSink, LatestSink });
	ConsoleAndFileLog->set_level(spdlog::level::debug);
	spdlog::register_logger(ConsoleAndFileLog);

	spdlog::set_default_logger(ConsoleAndFileLog);
	spdlog::flush_on(spdlog::level::debug);
}

void ICLogger::CleanUpOldLogs()
{
	fs::path LogPath = fs::current_path() / "Logs";
	ICLogger::Debug("Cleaning up logs at path: {}", LogPath.string());

	std::vector<fs::path> LogFiles;

	try 
	{
		for (const auto& entry : fs::directory_iterator(LogPath)) 
		{
			if (fs::is_regular_file(entry.path())) 
			{
				if (entry.path().extension() == ".log" && entry.path().filename() != "Latest.log")
				{
					LogFiles.push_back(entry.path());
				}
			}
		}

		if (LogFiles.size() > MaxLogFiles)
		{
			// Sort alphabetically, which will show oldest first
			std::sort(LogFiles.begin(), LogFiles.end());
			uint32_t LogFilesToRemove = LogFiles.size() - MaxLogFiles;
			for (uint32_t i = 0; i < LogFilesToRemove; i++)
			{
				ICLogger::Debug("Deleting log {}", LogFiles.at(i).filename().string());
				spdlog::details::os::remove_if_exists(spdlog::filename_t(LogFiles.at(i).string()));
			}
		}

	}
	catch (const fs::filesystem_error& e) {
		ICLogger::Error("Filesystem Error Cleaning up logs: {}", e.what());
	}
}

void ICLogger::InitLogger()
{
	Instance = std::make_shared<ICLogger>();
}

void ICLogger::ExitLogger()
{
	Instance->CleanUpOldLogs();
	spdlog::shutdown();
}
