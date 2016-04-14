#include "gtest/gtest.h"
#include "utils.h"
#include "liblog_environment.h"
#include "tests_params.h"
#include "liblog/liblog.h"
#include "liblog/file_logger.h"

class LiblogTest : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		liblog::set_logger(nullptr);
		LiblogEnvironment::delete_file_and_check(parameters::test_log_filename);
	}

	virtual void TearDown() override
	{
		liblog::set_logger(nullptr);
	}
};

TEST_F(LiblogTest, create_file_log_test)
{
	liblog::FileLogger logger(parameters::test_log_filename, liblog::LogLevel::LOG_LEVEL_INFO);
	ASSERT_TRUE(filesystem::exists(parameters::test_log_filename));
}

TEST_F(LiblogTest, set_logger_test)
{
	auto expected = "check ok";
	liblog::set_logger(std::make_unique<liblog::FileLogger>(parameters::test_log_filename, liblog::LogLevel::LOG_LEVEL_INFO));
	ASSERT_TRUE(filesystem::exists(parameters::test_log_filename));
	LOG_ERROR << expected;
	auto actual = details::read_file<std::string>(parameters::test_log_filename);
	EXPECT_TRUE(details::contain(actual, expected)) << actual;
}

class LogLevelTest : public LiblogTest, public ::testing::WithParamInterface<int>
{};

TEST_P(LogLevelTest, log_level_test)
{
	static const std::vector<std::string> expected = { "error_level", "warn_level", "info_level", "debug" };
	static const std::vector<std::string> expected_level_description = { "ERROR", "WARN", "INFO", "DEBUG" };
	auto level = GetParam();
	liblog::set_logger(std::make_unique<liblog::FileLogger>(parameters::test_log_filename, static_cast<liblog::LogLevel>(level)));

	LOG_ERROR << expected[0];
	LOG_WARN << expected[1];
	LOG_INFO << expected[2];
	LOG_DEBUG << expected[3];

	auto actual = details::read_file<std::string>(parameters::test_log_filename);
	auto size = static_cast<int>(expected.size());
	auto size_must_contain = size - level + (level == 0 ? 0 : 1);
	auto start_must_not_contain = std::max(size_must_contain, 0);

	for (auto i = 0; i < size_must_contain; ++i)
	{
		EXPECT_TRUE(details::contain(actual, expected[i]));
		EXPECT_TRUE(details::contain(actual, expected_level_description[i]));
	}

	for (auto i = start_must_not_contain; i < size; ++i)
	{
		EXPECT_FALSE(details::contain(actual, expected[i]));
		EXPECT_FALSE(details::contain(actual, expected_level_description[i]));
	}

	EXPECT_FALSE(HasNonfatalFailure()) << actual;
}

INSTANTIATE_TEST_CASE_P(, LogLevelTest, ::testing::Range(0, 7));


TEST_F(LiblogTest, time_indicator)
{
	auto expected = "check ok";
	liblog::set_logger(std::make_unique<liblog::FileLogger>(parameters::test_log_filename, liblog::LogLevel::LOG_LEVEL_INFO));
	ASSERT_TRUE(filesystem::exists(parameters::test_log_filename));

	for (int i = 0; i < 1000; ++i)
	{
		LOG_ERROR << expected;
	}

	auto actual = details::read_file<std::string>(parameters::test_log_filename);
	EXPECT_TRUE(details::contain(actual, expected)) << actual;
}