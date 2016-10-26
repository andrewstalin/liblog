#ifndef _LIBLOG_FILE_LOGGER_H_
#define _LIBLOG_FILE_LOGGER_H_

#include "liblog/logger.h"
#include "liblog/file.h"
#include <mutex>

namespace liblog
{
	class FileLogger : public ILogger
	{
	private:
		std::unique_ptr<IFile> file_;
		std::string path_;
		bool need_flush_{ false };
		mutable std::mutex mutex_;

	public:
		FileLogger(std::string&& path, LogLevel level);

		virtual void write(const char* data, size_t size) override;

	private:
		void open_file() noexcept;
	};
}

#endif