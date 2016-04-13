#include "liblog/file_logger.h"

liblog::FileLogger::FileLogger(std::string && path, LogLevel level)
	: path_(std::move(path))
{
	set_log_level(level);
	open_file_stream();
}

void liblog::FileLogger::write(const char* data, size_t size)
{
	std::lock_guard<std::mutex> _(mutex_);

	if (!stream_.is_open())
	{
		open_file_stream();
	}

	stream_.write(data, size);
	stream_.flush();  // ???
}

void liblog::FileLogger::open_file_stream() noexcept
{
	stream_.open(path_, std::ios::out | std::ios::ate);
}
