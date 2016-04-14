#ifndef _LIBLOG_TESTS_LIBLOG_ENVIRONMENT_LOGGER_H_
#define _LIBLOG_TESTS_LIBLOG_ENVIRONMENT_LOGGER_H_

#include "gtest/gtest.h"
#include "tests_params.h"
#include <filesystem>

namespace filesystem = std::tr2::sys;

class LiblogEnvironment : public ::testing::Environment
{
public:
	virtual void SetUp() override
	{
		auto current_path = filesystem::current_path();
		delete_file_and_check(parameters::exists_log_filename);
		delete_file_and_check(parameters::test_log_filename);
		
		delete_file_and_check(parameters::russian_file_name);
		delete_file_and_check(parameters::russian_file_name_utf8);

		delete_directory_and_check(parameters::russian_directory_name);
		delete_directory_and_check(parameters::russian_directory_name_utf8);

		auto exist_log_path = filesystem::path(parameters::samples_directory).append(parameters::exists_log_filename);
		ASSERT_TRUE(filesystem::exists(exist_log_path))
			<< "Can't find test sample " << parameters::exists_log_filename << ". Please, fix it";

		ASSERT_TRUE(filesystem::copy_file(exist_log_path, parameters::exists_log_filename))
			<< "Can't copy " << parameters::exists_log_filename << ". Please, fix it";
	}

	static void delete_file_and_check(const std::string& filename)
	{
		filesystem::remove(filename);
		ASSERT_FALSE(filesystem::exists(filename))
			<< "Can't delete " << filename << ". Please, do it manually";
	}

	static void delete_directory_and_check(const std::string& path)
	{
		filesystem::remove_all(path);
		ASSERT_FALSE(filesystem::is_directory(path))
			<< "Can't delete " << path << ". Please, do it manually";
	}
};

#endif