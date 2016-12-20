#ifndef _TOOLBOX_V3_LOGGER_H_
#define _TOOLBOX_V3_LOGGER_H_

#include "liblog/logger.h"
#include "liblog/log_message.h"
#include <memory>

#define LOG(level) liblog::LogMessage(liblog::LOGGER.get(), __FUNCTION__, level)
#define LOG_IF(level, condition) !(condition) ? (void)0 : LOG(level)

#define LOG_WARN LOG_IF(liblog::LogLevel::LOG_LEVEL_WARN, liblog::LOGGER != nullptr && liblog::LOGGER->check_log_level(liblog::LogLevel::LOG_LEVEL_WARN))
#define LOG_INFO LOG_IF(liblog::LogLevel::LOG_LEVEL_INFO, liblog::LOGGER != nullptr && liblog::LOGGER->check_log_level(liblog::LogLevel::LOG_LEVEL_INFO))
#define LOG_DEBUG LOG_IF(liblog::LogLevel::LOG_LEVEL_DEBUG, liblog::LOGGER != nullptr && liblog::LOGGER->check_log_level(liblog::LogLevel::LOG_LEVEL_DEBUG))
#define LOG_ERROR LOG_IF(liblog::LogLevel::LOG_LEVEL_ERROR, liblog::LOGGER != nullptr && liblog::LOGGER->check_log_level(liblog::LogLevel::LOG_LEVEL_ERROR))

#define LOG_CONTEXT(level, context) liblog::LogMessage(liblog::LOGGER.get(), context, level)
#define LOG_IF_CONTEXT(level, condition, context) !(condition) ? (void)0 : LOG(level, context)

#define LOG_WARN_CONTEXT(context) LOG_IF_CONTEXT(liblog::LogLevel::LOG_LEVEL_WARN, liblog::LOGGER != nullptr && liblog::LOGGER->check_log_level(liblog::LogLevel::LOG_LEVEL_WARN), context)
#define LOG_INFO_CONTEXT(context) LOG_IF_CONTEXT(liblog::LogLevel::LOG_LEVEL_INFO, liblog::LOGGER != nullptr && liblog::LOGGER->check_log_level(liblog::LogLevel::LOG_LEVEL_INFO), context)
#define LOG_DEBUG_CONTEXT(context) LOG_IF_CONTEXT(liblog::LogLevel::LOG_LEVEL_DEBUG, liblog::LOGGER != nullptr && liblog::LOGGER->check_log_level(liblog::LogLevel::LOG_LEVEL_DEBUG), context)
#define LOG_ERROR_CONTEXT(context) LOG_IF_CONTEXT(liblog::LogLevel::LOG_LEVEL_ERROR, liblog::LOGGER != nullptr && liblog::LOGGER->check_log_level(liblog::LogLevel::LOG_LEVEL_ERROR), context)

namespace liblog
{
	void set_logger(std::unique_ptr<ILogger>&& logger);

	extern std::unique_ptr<ILogger> LOGGER;
}

#endif