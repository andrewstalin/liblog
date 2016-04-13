#include "liblog/liblog.h"

void liblog::set_logger(std::unique_ptr<ILogger>&& logger)
{
	liblog::LOGGER = std::move(logger);
}

std::unique_ptr<liblog::ILogger> liblog::LOGGER{ nullptr };