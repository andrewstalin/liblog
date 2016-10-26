#include "utils.h"

bool details::contain(const std::string& string, const std::string& substring)
{
	return string.find(substring) != string.npos;
}

std::string details::get_data(size_t size)
{
	std::string data{ "check ok! " };

	while (data.size() < size)
	{
		data.append(data);
	}

	return data;
}