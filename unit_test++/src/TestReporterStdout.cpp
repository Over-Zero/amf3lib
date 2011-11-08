#include "TestReporterStdout.h"
#include <iostream>

#include "TestDetails.h"

#ifdef _UNICODE
#define UNITTEST_STDOUT std::wcout
#else
#define UNITTEST_STDOUT std::cout
#endif

namespace UnitTest {

void TestReporterStdout::ReportFailure(TestDetails const& details, Char const* failure)
{
#if defined(__APPLE__) || defined(__GNUG__)
    // "%s:%d: error: Failure in %s: %s\n"
#define UNITTEST_LINE_NUMBER_PREFIX UNITTEST_TEXT(":")
#define UNITTEST_LINE_NUMBER_POSTFIX UNITTEST_TEXT("")
#else
    // "%s(%d): error: Failure in %s: %s\n"
#define UNITTEST_LINE_NUMBER_PREFIX UNITTEST_TEXT("(")
#define UNITTEST_LINE_NUMBER_POSTFIX UNITTEST_TEXT(")")
#endif

    UNITTEST_STDOUT << details.filename
        << UNITTEST_LINE_NUMBER_PREFIX << details.lineNumber << UNITTEST_LINE_NUMBER_POSTFIX
        << UNITTEST_TEXT(": error: Failure in ") << details.testName
        << UNITTEST_TEXT(": ") << failure << std::endl;

#undef UNITTEST_LINE_NUMBER_PREFIX
#undef UNITTEST_LINE_NUMBER_POSTFIX
}

void TestReporterStdout::ReportTestStart(TestDetails const& /*test*/)
{
}

void TestReporterStdout::ReportTestFinish(TestDetails const& /*test*/, float)
{
}

void TestReporterStdout::ReportSummary(int const totalTestCount, int const failedTestCount,
                                       int const failureCount, float secondsElapsed)
{
    if (failureCount > 0)
    {
        UNITTEST_STDOUT << UNITTEST_TEXT("FAILURE: ") << failedTestCount
            << UNITTEST_TEXT(" out of ") << totalTestCount
            << UNITTEST_TEXT(" tests failed (") << failureCount
            << UNITTEST_TEXT(" failures).") << std::endl;
    }
    else
    {
        UNITTEST_STDOUT << UNITTEST_TEXT("Success: ") << totalTestCount
            << UNITTEST_TEXT(" tests passed.") << std::endl;
    }

    UNITTEST_STDOUT << UNITTEST_TEXT("Test time: ") << secondsElapsed
        << UNITTEST_TEXT(" seconds.") << std::endl;
}

}
