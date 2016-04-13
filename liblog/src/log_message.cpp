#include "liblog\log_message.h"
#include <chrono>
#include <ctime>
#include <thread>
#include <iomanip>

const std::hash<std::thread::id> thread_id_hash;
const char* LOG_LEVEL_NAMES[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "" };

const char* LogLevelName(liblog::LogLevel log_level)
{
	auto level = static_cast<uint8_t>(log_level);
	return LOG_LEVEL_NAMES[level <= 5 ? level : 5];
}

liblog::LogMessage::LogMessage(ILogger * logger, const char* function, LogLevel log_level)
	: logger_(logger), log_level_(log_level), function_(function)
{
	initialize_log_message();
}

liblog::LogMessage::~LogMessage()
{
	try
	{
		writer_ << "\r\n";
		logger_->write(writer_.data(), writer_.size());
	}
	catch (...)
	{
	}
}
void liblog::LogMessage::initialize_log_message()
{
	auto now = std::chrono::system_clock::now();
	auto now_time_t = std::chrono::system_clock::to_time_t(now);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
	auto time = std::gmtime(&now_time_t);

	try
	{
		writer_ << fmt::format("{}-{:0>2}-{:0>2}T{:0>2}:{:0>2}:{:0>2}.{:0>3}", time->tm_year + 1900, time->tm_mon + 1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec, milliseconds);
		
		//writer_ << time->tm_year;
		//writer_ << (time->tm_mon >= 9 ? "-" : "-0") << time->tm_mon + 1;
		//writer_ << (time->tm_mday > 9 ? "-" : "-0") << time->tm_mday;
		//writer_ << (time->tm_hour > 9 ? "T" : "T0") << time->tm_hour;
		//writer_ << (time->tm_min > 9 ? ":" : ":0") << time->tm_min;
		//writer_ << (time->tm_sec > 9 ? ":" : ":0") << time->tm_sec << '.' << milliseconds;

		writer_ << " | " << thread_id_hash(std::this_thread::get_id());
		writer_ << " | " << LogLevelName(log_level_) << " | " << function_ << " | ";
	}
	catch (...)
	{
	}
}
