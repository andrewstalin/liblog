#include "liblog/logger.h"
#include <memory>

bool PERSISTENCE_FLAG{ true };

liblog::ILogger::~ILogger() 
{
	PERSISTENCE_FLAG = false;
}

