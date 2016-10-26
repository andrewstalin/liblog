#ifndef _LIBLOG_FILE_STREAM_H_
#define _LIBLOG_FILE_STREAM_H_

#include <fstream>
#include <memory>
#include <string>
#include "liblog/file.h"

namespace liblog
{
	class FileStreamImpl : public IFile
	{
	private:
		std::ofstream stream_;

	public:
		static std::unique_ptr<FileStreamImpl> open(const std::string& path, unsigned int flags)
		{
			auto file = std::unique_ptr<FileStreamImpl>(new FileStreamImpl());
			file->stream_.open(path, flags);
			return file;
		}

		void write(const char* data, size_t size) override
		{
			stream_.write(data, size);
		}
		
		void flush() override
		{
			stream_.flush();
		}

		bool is_open() const override
		{
			return stream_.is_open();
		}

	private:
		FileStreamImpl() = default;
	};
}
#endif