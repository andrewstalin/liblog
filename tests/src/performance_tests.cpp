#include "gtest/gtest.h"
#include "utils.h"
#include "tests_params.h"
#include "liblog_environment.h"
#include "liblog/liblog.h"
#include "liblog/file_logger.h"

std::thread CreateLogRoutine(const std::string& data, size_t iteration_count)
{
	std::thread th([data, iteration_count]()
	{
		for (size_t i = 0; i < iteration_count; ++i)
		{
			LOG_ERROR << data;
		}
	});
	return th;
}

void InitializePerformanceTest()
{
	liblog::set_logger(nullptr);
	LiblogEnvironment::delete_file_and_check(parameters::test_log_filename);
	liblog::set_logger(std::make_unique<liblog::FileLogger>(parameters::test_log_filename, liblog::LogLevel::LOG_LEVEL_INFO));
	ASSERT_TRUE(filesystem::exists(parameters::test_log_filename));
}

void CheckPerformanceTest(const std::string& data)
{
	auto actual = details::read_file<std::string>(parameters::test_log_filename);
	EXPECT_TRUE(details::contain(actual, data)) << actual;
}

void PerformanceTest(const std::string& data, size_t iteration_count)
{
	InitializePerformanceTest();
	CreateLogRoutine(data, iteration_count).join();
	CheckPerformanceTest(data);
}

void PerformanceTestAsync(const std::string& data, size_t iteration_count, size_t threads_count)
{
	InitializePerformanceTest();
	std::vector<std::thread> threads;

	for (size_t i = 0; i < threads_count; ++i)
	{
		threads.push_back(CreateLogRoutine(data, iteration_count));
	}

	for (auto& th : threads)
	{
		th.join();
	}

	CheckPerformanceTest(data);
}

TEST(performance_case, small_data)
{
	auto data = details::get_data(details::SMALL_SIZE);
	PerformanceTest(data, 4000);
}

TEST(performance_case, middle_data)
{
	auto data = details::get_data(details::MIDDLE_SIZE);
	PerformanceTest(data, 500);
}

TEST(performance_case, big_data)
{
	auto data = details::get_data(details::BIG_SIZE);
	PerformanceTest(data, 100);
}

TEST(performance_case, small_data_async)
{
	auto data = details::get_data(details::SMALL_SIZE);
	PerformanceTestAsync(data, 500, 10);
}

TEST(performance_case, middle_data_async)
{
	auto data = details::get_data(details::MIDDLE_SIZE);
	PerformanceTestAsync(data, 300, 5);
}

TEST(performance_case, big_data_async)
{
	auto data = details::get_data(details::BIG_SIZE);
	PerformanceTestAsync(data, 200, 4);
}
