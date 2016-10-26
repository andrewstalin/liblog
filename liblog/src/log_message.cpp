#include "liblog/log_message.h"
#include "liblog/datetime.h"
#include <chrono>
#include <ctime>
#include <thread>

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
	try
	{
		auto now_time = DateTime::now();
		writer_ << now_time.year;
		writer_ << (now_time.month > 9 ? "-" : "-0") << now_time.month;
		writer_ << (now_time.day > 9 ? "-" : "-0") << now_time.day;
		writer_ << (now_time.hour > 9 ? "T" : "T0") << now_time.hour;
		writer_ << (now_time.minute > 9 ? ":" : ":0") << now_time.minute;
		writer_ << (now_time.second > 9 ? ":" : ":0") << now_time.second << '.' << now_time.millisecond;

		writer_ << " | " << thread_id_hash(std::this_thread::get_id());
		writer_ << " | " << LogLevelName(log_level_) << " | " << function_ << " | ";
	}
	catch (...)
	{
	}
}
