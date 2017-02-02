#ifndef _LIBLOG_FILE_WIN_H_
#define _LIBLOG_FILE_WIN_H_

#ifdef _WIN32

#include <Windows.h>
#include "liblog/file.h"
#include <memory>
#include <string>

namespace liblog
{
	class FileWinImpl : public IFile
	{
	private:
		HANDLE handle_{ INVALID_HANDLE_VALUE };

	public:
		static std::unique_ptr<FileWinImpl> open(const std::string& path);

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