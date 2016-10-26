#ifndef _LIBLOG_FILE_H_
#define _LIBLOG_FILE_H_

namespace liblog
{
	class IFile
	{
	public:
		IFile() = default;

		IFile(const IFile&) = delete;
		void operator=(const IFile&) = delete;

		virtual ~IFile() {}

		virtual void write(const char* data, size_t size) = 0;
		
		virtual void flush() = 0;

		virtual bool is_open() const = 0;
	};
}

#endif // !_LIBLOG_FILE_H_
