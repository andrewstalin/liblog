#include "file_win.h"
#include <cassert>
#include <filesystem>

std::unique_ptr<liblog::FileWinImpl> liblog::FileWinImpl::open(const std::string& path)
{
	auto p = std::tr2::sys::u8path(path);
	auto str = p.wstring();
	auto handle = ::CreateFileW(str.c_str(), FILE_GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS, FILE_FLAG_WRITE_THROUGH, nullptr);
	return std::unique_ptr<FileWinImpl>(new FileWinImpl(handle));
}

liblog::FileWinImpl::~FileWinImpl()
{
	if (handle_ != INVALID_HANDLE_VALUE)
	{
		auto result = ::CloseHandle(handle_);
		assert(result != 0);
		handle_ = INVALID_HANDLE_VALUE;
	}
}

void liblog::FileWinImpl::write(const char* data, size_t size)
{
	DWORD written_bytes{ 0 };
	::WriteFile(handle_, data, size, &written_bytes, nullptr);
}

void liblog::FileWinImpl::flush()
{
	::FlushFileBuffers(handle_);
}

bool liblog::FileWinImpl::is_open() const
{
	return handle_ != INVALID_HANDLE_VALUE;
}

void liblog::FileWinImpl::seek_to_end()
{
	::SetFilePointer(handle_, 0, NULL, FILE_END);
}

liblog::FileWinImpl::FileWinImpl(HANDLE handle)
	: handle_(handle)
{
	assert(handle_ != INVALID_HANDLE_VALUE);
}
