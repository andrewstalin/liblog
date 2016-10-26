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
	std::lock_guard<std::mutex> _(mutex_);

	if (file_ == nullptr || !file_->is_open())
	{
		open_file();
	}

	file_->write(data, size);

	if (need_flush_)
	{
		file_->flush();
	}
}

void liblog::FileLogger::open_file() noexcept
{
#ifdef LIBLOG_USE_WINAPI
	auto file = FileWinImpl::open(path_, FileAccess::WRITE, FileShare::SHARE_READ_WRITE, FileMode::F_OPEN_ALWAYS, FILE_FLAG_WRITE_THROUGH | FILE_ATTRIBUTE_NORMAL);
	file->seek_to_end();
	file_ = std::move(file);
#else
	file_ = FileStreamImpl::open(path_, std::ios::ate | std::ios::binary | std::ios::app);
	need_flush_ = true;
#endif // LIBLOG_USE_WINAPI
}
