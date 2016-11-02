#include "liblog/rotation_by_date_logger.h"
#include <filesystem>
#include <cassert>

namespace filesystem = std::tr2::sys;
using namespace liblog;

constexpr char* SPECIFICATOR_YEAR = "%y";
constexpr char* SPECIFICATOR_MONTH = "%m";
constexpr char* SPECIFICATOR_DAY = "%d";
constexpr char* SPECIFICATOR_HOUR = "%H";
constexpr char* SPECIFICATOR_MINUTE = "%M";
constexpr char* SPECIFICATOR_SECOND = "%S";

#define LIBLOG_REPLACE_TEMPLATE(tmpl, specificator, value) ReplaceTemplate(tmpl, specificator, std::to_string(static_cast<int>(value)));

void ReplaceTemplate(std::string& tmpl, const std::string& specificator, const std::string& value)
{
	auto pos = tmpl.find(specificator);

	if (pos != tmpl.npos)
	{
		tmpl.replace(pos, specificator.size(), value);
	}
}

RotationByDateLogger::RotationByDateLogger(std::string&& log_path, LogLevel level, std::string&& filename_template, DateTimePart rotation_date_parts)
	: log_path_(std::move(log_path)), filename_template_(std::move(filename_template)), rotation_date_parts_(rotation_date_parts)
{
	set_log_level(level);
	filesystem::create_directories(log_path_);

	assert(filesystem::exists(log_path_));
	assert(!(rotation_date_parts_ & DateTimePart::YEAR) || filename_template_.find(SPECIFICATOR_YEAR) != std::string::npos);
	assert(!(rotation_date_parts_ & DateTimePart::MONTH) || filename_template_.find(SPECIFICATOR_MONTH) != std::string::npos);
	assert(!(rotation_date_parts_ & DateTimePart::DAY) || filename_template_.find(SPECIFICATOR_DAY) != std::string::npos);
	assert(!(rotation_date_parts_ & DateTimePart::HOUR) || filename_template_.find(SPECIFICATOR_HOUR) != std::string::npos);
	assert(!(rotation_date_parts_ & DateTimePart::MINUTE) || filename_template_.find(SPECIFICATOR_MINUTE) != std::string::npos);
	assert(!(rotation_date_parts_ & DateTimePart::SECONDS) || filename_template_.find(SPECIFICATOR_SECOND) != std::string::npos);
}

void RotationByDateLogger::write(const char* data, size_t size)
{
	auto now_date = DateTime::now();

	if (file_logger_ == nullptr || current_date_.compare(now_date, rotation_date_parts_) != 0)
	{
		next_rotation(now_date);
	}

	if (file_logger_ != nullptr)
	{
		file_logger_->write(data, size);
	}
}

void RotationByDateLogger::next_rotation(const DateTime& new_date)
{
	auto filename = filesystem::path(log_path_).append(get_logfile_name(new_date)).string();
	std::lock_guard<std::mutex> _(mutex_);
	file_logger_ = std::make_unique<FileLogger>(std::move(filename), log_level());
	current_date_ = new_date;
}

std::string RotationByDateLogger::get_logfile_name(const DateTime& date) const
{
	auto filename = filename_template_;
	LIBLOG_REPLACE_TEMPLATE(filename, SPECIFICATOR_YEAR, date.year);
	LIBLOG_REPLACE_TEMPLATE(filename, SPECIFICATOR_MONTH, date.month);
	LIBLOG_REPLACE_TEMPLATE(filename, SPECIFICATOR_DAY, date.day);
	LIBLOG_REPLACE_TEMPLATE(filename, SPECIFICATOR_HOUR, date.hour);
	LIBLOG_REPLACE_TEMPLATE(filename, SPECIFICATOR_MINUTE, date.minute);
	LIBLOG_REPLACE_TEMPLATE(filename, SPECIFICATOR_SECOND, date.second);
	return filename;
}
