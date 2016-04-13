#ifndef _LIBLOG_FILE_LOGGER_H_
#define _LIBLOG_FILE_LOGGER_H_

#include "liblog/logger.h"
#include <fstream>
#include <mutex>

namespace liblog
{
	class FileLogger : public ILogger
	{
	private:
		std::ofstream stream_;
		std::string path_;
		mutable std::mutex mutex_;

	public:
		FileLogger(std::string&& path, LogLevel level);

		virtual void write(const char* data, size_t size) override;

	private:
		void open_file_stream() noexcept;
	};
}

#endif