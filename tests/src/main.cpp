#include <stdio.h>
#include "gtest/gtest.h"
#include "liblog_environment.h"

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(new LiblogEnvironment);
    int ret = RUN_ALL_TESTS();

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--waitAnyKey") == 0)
        {
            std::puts("Press any key to exit");
            std::getchar();
            break;
        }
    }

    return ret;
}