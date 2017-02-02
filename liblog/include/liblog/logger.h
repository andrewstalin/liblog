#ifndef _LIBLOG_LOGGER_H_
#define _LIBLOG_LOGGER_H_

#include <cstdint>

namespace liblog
{
	enum class LogLevel : uint8_t
	{
		LOG_LEVEL_TRACE = 0,
		LOG_LEVEL_DEBUG = 1,
		LOG_LEVEL_INFO = 2,
		LOG_LEVEL_WARN = 3,
		LOG_LEVEL_ERROR = 4,
		LOG_LEVEL_UNDEFINED = 5
	};

	class ILogger
	{
	private:
		uint8_t log_level_{ static_cast<uint8_t>(LogLevel::LOG_LEVEL_WARN) };

	public:
		virtual ~ILogger() {}

		virtual void write(const char* data, size_t size) = 0;

		LogLevel log_level() const { return static_cast<LogLevel>(log_level_); }
		void set_log_level(LogLevel val) { log_level_ = static_cast<uint8_t>(val); }

		bool check_log_level(LogLevel level) const { return log_level_ <= static_cast<uint8_t>(level); }
	};
}

#endif