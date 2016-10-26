#ifndef _LIBLOG_VS_OUTPUT_LOGGER_H_
#define _LIBLOG_VS_OUTPUT_LOGGER_H_

#ifdef _MSC_VER 

#include "liblog/logger.h"

namespace liblog
{
	class VsOutputLogger : public ILogger
	{
	public:
		VsOutputLogger(LogLevel level);

		virtual void write(const char* data, size_t size) override;
	};
}


#endif
#endif