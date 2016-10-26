#ifndef _LIBLOG_TESTS_UTILS_LOGGER_H_
#define _LIBLOG_TESTS_UTILS_LOGGER_H_

#include <fstream>

namespace details
{
	constexpr size_t SMALL_SIZE = 256;
	constexpr size_t MIDDLE_SIZE = 100 * 1024;
	constexpr size_t BIG_SIZE = 1024 * 1024;

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

	bool contain(const std::string& string, const std::string& substring);

	std::string get_data(size_t size);
}

#endif