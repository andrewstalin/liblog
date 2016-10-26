#include "file_win.h"
#include <cassert>
#include <filesystem>

std::unique_ptr<liblog::FileWinImpl> liblog::FileWinImpl::open(const std::string& path, FileAccess access, FileShare share, FileMode mode, uint32_t flags)
{
	DWORD desired_access{ 0 };
	DWORD creation_disposition{ 0 };

	switch (access)
	{
	case FileAccess::READ:
		desired_access = FILE_GENERIC_READ;
		break;
	case FileAccess::WRITE:
		desired_access = FILE_GENERIC_WRITE;
		break;
	case FileAccess::READ_WRITE:
		desired_access = FILE_GENERIC_WRITE | FILE_GENERIC_READ;
		break;
	}

	switch (mode)
	{
	case FileMode::F_CREATE_ALWAYS:
		creation_disposition = CREATE_ALWAYS;
		break;
	case FileMode::F_CREATE_NEW:
		creation_disposition = CREATE_NEW;
		break;
	case FileMode::F_OPEN_EXISTING:
		creation_disposition = OPEN_EXISTING;
		break;
	case FileMode::F_OPEN_ALWAYS:
		creation_disposition = OPEN_ALWAYS;
		break;
	case FileMode::F_TRUNCATE_EXISTING:
		creation_disposition = TRUNCATE_EXISTING;
		break;
	}

	DWORD attributes = flags == 0 ? FILE_ATTRIBUTE_NORMAL : static_cast<DWORD>(flags);
	auto handle = ::CreateFileW(std::tr2::sys::path(path).wstring().c_str(), desired_access, static_cast<DWORD>(share), nullptr, creation_disposition, attributes, nullptr);
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
