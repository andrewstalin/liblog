#include "liblog/datetime.h"

using namespace liblog;

#if (defined(_MSC_VER) && (_MSC_VER >= 1600)) //Visual Studio 2010

std::tm local_time(time_t ticks)
{
	std::tm time = { 0 };
	
	if (localtime_s(&time, &ticks) != 0)
	{
		// TODO: ??
	}
	
	return time;
}

std::tm gmtime(time_t ticks)
{
	std::tm time = { 0 };

	if (gmtime_s(&time, &ticks) != 0)
	{
		// TODO: ??
	}

	return time;
}

#endif //_MSC_VER

#define COMPARE_IF_NEED_AND_RETURN_IF_NOT_EQUAL(condition, member, obj) if (condition) { if (member != obj.member) { return static_cast<int>(member - obj.member);} }

int DateTime::compare(const DateTime& date, DateTimePart parts)
{
	COMPARE_IF_NEED_AND_RETURN_IF_NOT_EQUAL(parts & DateTimePart::YEAR, year, date);
	COMPARE_IF_NEED_AND_RETURN_IF_NOT_EQUAL(parts & DateTimePart::MONTH, month, date);
	COMPARE_IF_NEED_AND_RETURN_IF_NOT_EQUAL(parts & DateTimePart::DAY, day, date);
	COMPARE_IF_NEED_AND_RETURN_IF_NOT_EQUAL(parts & DateTimePart::HOUR, hour, date);
	COMPARE_IF_NEED_AND_RETURN_IF_NOT_EQUAL(parts & DateTimePart::MINUTE, minute, date);
	COMPARE_IF_NEED_AND_RETURN_IF_NOT_EQUAL(parts & DateTimePart::SECONDS, second, date);
	COMPARE_IF_NEED_AND_RETURN_IF_NOT_EQUAL(parts & DateTimePart::MILLISECOND, millisecond, date);
	return 0;
}

DateTime DateTime::now()
{
	return create(std::chrono::system_clock::now());
}

DateTime DateTime::create(const std::chrono::system_clock::time_point & point)
{
	auto ticks = std::chrono::system_clock::to_time_t(point);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(point.time_since_epoch()).count() % 1000;
	auto time = gmtime(ticks);
	return DateTime::create(time, milliseconds);
}

DateTime DateTime::create(const std::tm & time, uint64_t millisecond)
{
	return DateTime(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec, millisecond);
}