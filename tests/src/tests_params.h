#ifndef _LIBLOG_TESTS_TESTS_PARAMS_LOGGER_H_
#define _LIBLOG_TESTS_TESTS_PARAMS_LOGGER_H_

namespace parameters
{
	constexpr char* samples_directory = "../samples/";
	
	constexpr char* russian_file_name = "имя на русском.log";
	constexpr char* russian_file_name_utf8 = u8"имя на русском utf8.log";

	constexpr char* russian_directory_name = "имя на русском";
	constexpr char* russian_directory_name_utf8 = u8"имя на русском utf8";
	
	constexpr char* test_log_filename = "test.log";
	constexpr char* exists_log_filename = "exists.log";
}

#endif