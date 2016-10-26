#ifndef _LIBLOG_ROTATION_BY_DATE_LOGGER_H_
#define _LIBLOG_ROTATION_BY_DATE_LOGGER_H_

#include "liblog/logger.h"
#include "liblog/file_logger.h"
#include "liblog/datetime.h"
#include <memory>

namespace liblog
{
	class RotationByDateLogger : public ILogger
	{
	private:
		std::string log_path_;
		std::string filename_template_;
		DateTimePart rotation_date_parts_;
		mutable std::mutex mutex_;

		DateTime current_date_;
		std::unique_ptr<FileLogger> file_logger_;
	public:
		RotationByDateLogger(std::string&& path, LogLevel level, std::string&& filename_template, DateTimePart rotation_date_parts = DateTimePart::YEAR | DateTimePart::MONTH); // template filename string, for example "kp.%y.%m.%d %H:%M:%S.log"

		void write(const char* data, size_t size) override;

	private:
		void next_rotation(const DateTime& new_date);

		std::string get_logfile_name(const DateTime& date) const;
	};
}

#endif