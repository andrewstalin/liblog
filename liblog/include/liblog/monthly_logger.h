#ifndef _LIBLOG_MONTHLY_LOGGER_H_
#define _LIBLOG_MONTHLY_LOGGER_H_

#include "liblog/logger.h"
#include "liblog/file_logger.h"
#include <memory>

namespace liblog
{
	class MonthlyLogger : public ILogger
	{
	private:
		std::string log_path_;
		std::string filename_template_;
		std::unique_ptr<FileLogger> file_logger_;

		uint16_t year_;
		uint8_t month_;

	public:
		MonthlyLogger(std::string&& path, LogLevel level, std::string&& filename_template); // template filename string, for example "kp.%Y.%M.log"

		void write(const char* data, size_t size) override;

	private:
		void next_rotation(uint16_t year, uint8_t month);

		std::string get_logfile_name() const;
	};
}

#endif