#include "amf3_tests_pch.h"
#include <tchar.h>
#include <iostream>
#include <UnitTest++.h>
#include <TestReporterStdout.h>

int _tmain(int /*argc*/, _TCHAR* /*argv[]*/)
{
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);

    if (runner.RunTestsIf(UnitTest::Test::GetTestList(), NULL, UnitTest::True(), 0) > 0)
    {
#ifdef UNICODE
        std::wcin.get();
#else
        std::cin.get();
#endif
    }

    return 0;
}
