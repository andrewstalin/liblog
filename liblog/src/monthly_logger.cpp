#include "liblog/monthly_logger.h"
#include "cppformat/format.h"
#include <filesystem>

namespace filesystem = std::tr2::sys;
using namespace liblog;

MonthlyLogger::MonthlyLogger(std::string&& log_path, LogLevel level, std::string&& filename_template)
	: log_path_(std::move(log_path)), filename_template_(std::move(filename_template))
{
	try
	{
		set_log_level(level);
		filesystem::create_directories(filesystem::path(log_path));
	}
	catch (...)
	{
	}
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

void MonthlyLogger::next_rotation(uint16_t year, uint8_t month) noexcept
{
	year_ = year;
	month_ = month;

	try
	{
		auto date_template = fmt::format(filename_template_, "{}", "{:0>2}");
		std::string file_name = fmt::format(date_template, year, month);
		file_logger_ = std::make_unique<FileLogger>(filesystem::path(log_path_).append(file_name).string(), log_level());
	}
	catch (...)
	{
	}
}
