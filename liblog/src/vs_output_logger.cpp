#ifdef _MSC_VER

#include "liblog/vs_output_logger.h"
#include <windows.h>
#include <string>
#include <algorithm>

liblog::VsOutputLogger::VsOutputLogger(LogLevel level)
{
	set_log_level(level);
}

void liblog::VsOutputLogger::write(const char* data, size_t size)
{
	std::string message(data, data + size);
	std::replace_if(message.begin(), message.end(), [](char ch) { return ch == '\0'; }, ' ');
	::OutputDebugString(message.c_str());
}

#endif
