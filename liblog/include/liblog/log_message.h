#ifndef _LIBLOG_LOG_MESSAGE_H_
#define _LIBLOG_LOG_MESSAGE_H_

#include "liblog/logger.h"
#include "cppformat/format.h"

namespace liblog
{
	class LogMessage
	{
	private:
		ILogger* logger_;
		LogLevel log_level_;
		const char* function_;
		fmt::MemoryWriter writer_;

	public:
		LogMessage(ILogger* logger, const char* function, LogLevel log_level);

		~LogMessage();

		template<typename T>
		LogMessage& operator<<(const T& value)
		{
			try
			{
				writer_ << value;
			}
			catch (...)
			{
			}

			return *this;
		}

	private:
		void initialize_log_message();
	};
}

#endif