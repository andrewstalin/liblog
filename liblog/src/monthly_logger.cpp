#include "liblog/monthly_logger.h"
#include <filesystem>

namespace filesystem = std::tr2::sys;
using namespace liblog;

MonthlyLogger::MonthlyLogger(std::string&& log_path, LogLevel level, std::string&& filename_template)
	: log_path_(std::move(log_path)), filename_template_(std::move(filename_template))
{
	set_log_level(level);
	filesystem::create_directories(filesystem::path(log_path));
	
	/*if (filename_template_.find("%Y") == filename_template_.npos || filename_template_.find("%M") == filename_template_.npos)
	{
		throw std::invalid_argument("Bad filename template format. Must contain %M and %Y");
	}*/
}

void MonthlyLogger::write(const char* data, size_t size)
{
	auto now = std::time(nullptr);
	auto time = std::gmtime(&now);

	time->tm_year += 1900;
	time->tm_mon += 1;

	if (file_logger_ == nullptr || time->tm_year > year_ || time->tm_mon > month_)
	{
		next_rotation(static_cast<uint16_t>(time->tm_year), static_cast<uint8_t>(time->tm_mon));
	}

	if (file_logger_ != nullptr)
	{
		file_logger_->write(data, size);
	}
}

void MonthlyLogger::next_rotation(uint16_t year, uint8_t month)
{
	year_ = year;
	month_ = month;

	file_logger_ = std::make_unique<FileLogger>(filesystem::path(log_path_).append(get_logfile_name()).string(), log_level());
}

std::string liblog::MonthlyLogger::get_logfile_name() const
{
	auto year_string = std::to_string(year_);
	auto month_string = (month_ > 9 ? "" : "0") + std::to_string(month_);
	auto filename = filename_template_;

	auto year_template_position = filename_template_.find("%Y");

	if (year_template_position != filename_template_.npos)
	{
		filename.replace(year_template_position, 2, year_string);
	}

	auto month_template_position = filename_template_.find("%M");

	if (month_template_position != filename_template_.npos)
	{
		filename.replace(month_template_position, 2, month_string);
	}

	return filename;
}
