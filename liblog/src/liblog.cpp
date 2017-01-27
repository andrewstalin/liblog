#include "liblog/liblog.h"
#include <sstream>
#include <iomanip>

liblog::ILogger* liblog::LOGGER{ nullptr };

void liblog::set_logger(ILogger* logger)
{
	liblog::LOGGER = logger;
}

std::string liblog::to_hex_string(const uint8_t* data, size_t size)
{
	std::stringstream ss;

	for (auto i = 0u; i < size; ++i)
	{
		ss << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(data[i]);
	}

	return ss.str();
}