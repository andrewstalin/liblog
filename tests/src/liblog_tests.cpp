#include "gtest/gtest.h"
#include "liblog/liblog.h"
#include "liblog/file_logger.h"
#include "utils.h"
#include <filesystem>
#include <fstream>

namespace filesystem = std::tr2::sys;

class LiblogTest : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		liblog::set_logger(nullptr);
		filesystem::remove(log_file_name);
		ASSERT_FALSE(filesystem::exists(log_file_name)) 
			<< "Can't delete " << log_file_name << ". Please, do it manually";
	}

	virtual void TearDown() override
	{
	}

	const std::string log_file_name = "test.log";
};

TEST_F(LiblogTest, create_file_log_test)
{
	liblog::FileLogger logger(std::string(log_file_name), liblog::LogLevel::LOG_LEVEL_INFO);
	ASSERT_TRUE(filesystem::exists(log_file_name));
}

TEST_F(LiblogTest, set_logger_test)
{
	auto expected = "жду чуда";
	liblog::set_logger(std::make_unique<liblog::FileLogger>(std::string(log_file_name), liblog::LogLevel::LOG_LEVEL_INFO));
	ASSERT_TRUE(filesystem::exists(log_file_name));
	LOG_ERROR << expected;
	auto actual = details::read_file<std::string>(log_file_name);
	EXPECT_TRUE(actual.find(expected) != actual.npos) << actual;

}