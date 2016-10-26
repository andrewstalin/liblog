#include "gtest/gtest.h"
#include "utils.h"
#include "tests_params.h"
#include "liblog_environment.h"
#include "liblog/liblog.h"
#include "liblog/rotation_by_date_logger.h"

constexpr int COUNT_OF_FILES = 10;

TEST(rotation_by_date_logger_case, working)
{
	auto directory = filesystem::path(parameters::rotation_test_directory);

	if (filesystem::exists(directory))
	{
		filesystem::remove_all(directory);
	}

	ASSERT_FALSE(filesystem::exists(directory));

	auto logger = std::make_unique<liblog::RotationByDateLogger>(directory.string(), liblog::LogLevel::LOG_LEVEL_INFO, "LL.%y.%m.%d-%H.%M.%S.log", liblog::DateTimePart::ALL);
	liblog::set_logger(std::move(logger));

	auto data = details::get_data(details::SMALL_SIZE);

	for (size_t i = 0; i < COUNT_OF_FILES; ++i)
	{
		LOG_ERROR << data;
		std::this_thread::sleep_for(std::chrono::milliseconds(1010));
	}

	size_t count{ 0 };

	for (auto& file : filesystem::directory_iterator(directory))
	{
		if (file.status().type() == filesystem::file_type::regular)
		{
			auto actual = details::read_file<std::string>(file.path().string());
			EXPECT_TRUE(details::contain(actual, data)) << actual;
			++count;
		}
	}

	EXPECT_EQ(COUNT_OF_FILES, count);
}