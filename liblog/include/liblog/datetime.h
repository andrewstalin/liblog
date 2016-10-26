#ifndef _LIBLOG_DATETIME_H_
#define _LIBLOG_DATETIME_H_

#include <chrono>

namespace liblog
{
	enum class DateTimePart : uint32_t
	{
		YEAR = 1,
		MONTH = 2,
		DAY = 4,
		HOUR = 8,
		MINUTE = 16,
		SECONDS = 32,
		MILLISECOND = 64,
		ALL = 127,
	};

	inline DateTimePart operator|(DateTimePart first, DateTimePart second)
	{
		return static_cast<DateTimePart>(static_cast<uint32_t>(first) | static_cast<uint32_t>(second));
	}

	inline bool operator&(DateTimePart first, DateTimePart second)
	{
		return (static_cast<uint32_t>(first) & static_cast<uint32_t>(second)) != 0;
	}

	struct DateTime
	{
	public:
		uint16_t year{ 0 };
		uint8_t month{ 0 };
		uint8_t day{ 0 };
		uint8_t hour{ 0 };
		uint8_t minute{ 0 };
		uint8_t second{ 0 };
		uint64_t millisecond{ 0 };

		DateTime() = default;

		DateTime(uint16_t year, uint8_t month = 1, uint8_t day = 1, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0, uint64_t millisecond = 0)
			: year(year), month(month), day(day), hour(hour), minute(minute), second(second), millisecond(millisecond)
		{}

		int compare(const DateTime& date, DateTimePart parts = DateTimePart::ALL);

		static DateTime now();

		static DateTime create(const std::chrono::system_clock::time_point& point);

		static DateTime create(const std::tm& time, uint64_t millisecond = 0);
	};
}
#endif