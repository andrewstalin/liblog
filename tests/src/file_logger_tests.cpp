#include "gtest/gtest.h"
#include "utils.h"
#include "tests_params.h"
#include "liblog/file_logger.h"
#include <filesystem>

namespace filesystem = std::tr2::sys;

TEST(file_logger_case, open_russian)
{	
	auto expected = std::string("тестовая запись лога");
	liblog::FileLogger filelogger(parameters::russian_directory_name, liblog::LogLevel::LOG_LEVEL_INFO);
	filelogger.write(expected.data(), expected.size());
	
	ASSERT_TRUE(filesystem::exists(parameters::russian_directory_name));

	auto actual = details::read_file<std::string>(parameters::russian_directory_name);
	EXPECT_TRUE(details::contain(actual, expected)) << actual;
}

TEST(file_logger_case, open_russian_utf8)
{
	auto expected = std::string(u8"тестовая запись лога");
	liblog::FileLogger filelogger(parameters::russian_directory_name_utf8, liblog::LogLevel::LOG_LEVEL_INFO);
	filelogger.write(expected.data(), expected.size());

	ASSERT_TRUE(filesystem::exists(parameters::russian_directory_name_utf8));

	auto actual = details::read_file<std::string>(parameters::russian_directory_name_utf8);
	EXPECT_TRUE(details::contain(actual, expected)) << actual;
}

TEST(file_logger_case, append)
{
	std::string old_message{ "old log message" };
	std::string new_message{ "new log message" };

	ASSERT_TRUE(filesystem::exists(parameters::exists_log_filename));

	liblog::FileLogger filelogger(parameters::exists_log_filename, liblog::LogLevel::LOG_LEVEL_INFO);
	filelogger.write(new_message.data(), new_message.size());

	auto actual = details::read_file<std::string>(parameters::exists_log_filename);
	auto pos = actual.find(old_message);
	EXPECT_NE(actual.npos, pos) << actual;
	pos = actual.find(new_message, pos + old_message.size());
	EXPECT_NE(actual.npos, pos) << actual;
}

TEST(file_logger_case, time_indicator)
{
	std::string expected = "2016-04-14T16:03:01.635 | 3056120262 | ERROR | LiblogTest_time_test_Test::TestBody | check ok";
	liblog::FileLogger filelogger(parameters::test_log_filename, liblog::LogLevel::LOG_LEVEL_INFO);
	ASSERT_TRUE(filesystem::exists(parameters::test_log_filename));

	for (int i = 0; i < 2000; ++i)
	{
		filelogger.write(expected.data(), expected.size());
	}

	auto actual = details::read_file<std::string>(parameters::test_log_filename);
	EXPECT_TRUE(details::contain(actual, expected)) << actual;
}