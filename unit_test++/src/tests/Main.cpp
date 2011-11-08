#include "../UnitTest++.h"
#include "../TestReporterStdout.h"
#include <iostream>


int main(int, char const *[])
{
    if (UnitTest::RunAllTests() > 0)
    {
        std::wcin.get();
    }
    return 0;
}
