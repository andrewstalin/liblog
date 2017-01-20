#include "liblog/liblog.h"
#include <sstream>
#include <iomanip>

void liblog::set_logger(std::unique_ptr<ILogger>&& logger)
{
	liblog::LOGGER = std::move(logger);
}

std::unique_ptr<liblog::ILogger> liblog::LOGGER{ nullptr };

std::string liblog::to_hex_string(const uint8_t* data, size_t size)
{
	std::stringstream ss;

	for (auto i = 0u; i < size; ++i)
	{
		ss << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(data[i]);
	}

	return ss.str();
}