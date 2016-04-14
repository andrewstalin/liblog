#ifndef _LIBLOG_TESTS_UTILS_LOGGER_H_
#define _LIBLOG_TESTS_UTILS_LOGGER_H_

#include <fstream>

namespace details
{
	template<typename T>
	T read_file(const std::string& filename)
	{
		std::ifstream input(filename, std::ios::ate | std::ios::binary);

		if (!input.is_open())
		{
			throw std::runtime_error("Can't open file");
		}

		auto size = static_cast<std::streamsize>(input.tellg());

		input.seekg(0);
		T data;
		data.resize(static_cast<size_t>(size));
		input.read((char*)(data.data()), size);

		if (input.gcount() != size)
		{
			throw std::runtime_error("can't read all data from file");
		}

		input.close();
		return data;
	}

	inline bool contain(const std::string& string, const std::string& substring)
	{
		return string.find(substring) != string.npos;
	}
}

#endif