#ifndef _LIBLOG_FILE_WIN_H_
#define _LIBLOG_FILE_WIN_H_

#ifdef _WIN32

#include <Windows.h>
#include "liblog/file.h"
#include <memory>
#include <string>

namespace liblog
{
	enum class FileAccess : uint8_t
	{
		READ,
		WRITE,
		READ_WRITE
	};

	enum class FileMode : uint8_t
	{
		F_CREATE_NEW,
		F_CREATE_ALWAYS,
		F_OPEN_EXISTING,
		F_OPEN_ALWAYS,
		F_TRUNCATE_EXISTING
	};

	enum class FileShare
	{
		NONE = 0,
		SHARE_DELETE = FILE_SHARE_DELETE,
		SHARE_READ = FILE_SHARE_READ,
		SHARE_WRITE = FILE_SHARE_WRITE,
		SHARE_READ_WRITE = FILE_SHARE_WRITE | FILE_SHARE_READ
	};

	class FileWinImpl : public IFile
	{
	private:
		HANDLE handle_{ INVALID_HANDLE_VALUE };

	public:
		static std::unique_ptr<FileWinImpl> open(const std::string& path, FileAccess access, FileShare share, FileMode mode, uint32_t flags);

		~FileWinImpl() override;

		void write(const char* data, size_t size) override;
		
		void flush() override;

		bool is_open() const override;

		void seek_to_end();
	private:
		FileWinImpl(HANDLE handle);
	};
}

#endif // _WIN32

#endif