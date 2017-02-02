#include "liblog/file_logger.h"
#include "file_stream.h"
#include "file_win.h"

liblog::FileLogger::FileLogger(std::string && path, LogLevel level)
	: path_(std::move(path))
{
	set_log_level(level);
	open_file();
}

void liblog::FileLogger::write(const char* data, size_t size)
{
	if (file_ == nullptr || !file_->is_open())
	{
		open_file();
	}

	file_->write(data, size);
}

void liblog::FileLogger::open_file() noexcept
{
	auto file = FileWinImpl::open(path_);
	file->seek_to_end();
	file_ = std::move(file);
}
