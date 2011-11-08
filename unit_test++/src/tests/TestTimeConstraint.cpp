#include "../UnitTest++.h"
#include "../TestResults.h"
#include "../TimeHelpers.h"
#include "RecordingReporter.h"
#include "ScopedCurrentTest.h"

using namespace UnitTest;

namespace
{

TestDetails EmptyTestDetails()
{
    return TestDetails(UNITTEST_TEXT(""), UNITTEST_TEXT(""), UNITTEST_TEXT(""), 0);
}

TEST(TimeConstraintSucceedsWithFastTest)
{
    TestResults result;
    {
        ScopedCurrentTest scopedResult(result);
        TimeConstraint t(200, EmptyTestDetails());
        TimeHelpers::SleepMs(5);
    }
    CHECK_EQUAL(0, result.GetFailureCount());
}

TEST(TimeConstraintFailsWithSlowTest)
{
    TestResults result;
    {
        ScopedCurrentTest scopedResult(result);
        TimeConstraint t(10, EmptyTestDetails());
        TimeHelpers::SleepMs(20);
    }
    CHECK_EQUAL(1, result.GetFailureCount());
}

TEST(TimeConstraintFailureIncludesCorrectData)
{
    RecordingReporter reporter;
    TestResults result(&reporter);
    {
        ScopedCurrentTest scopedResult(result);

        TestDetails const details(
            UNITTEST_TEXT("testname"),
            UNITTEST_TEXT("suitename"),
            UNITTEST_TEXT("filename"),
            10);
        TimeConstraint t(10, details);
        TimeHelpers::SleepMs(20);
    }

    using namespace std;

    CHECK(Strings::StrStr(reporter.lastFailedFile, UNITTEST_TEXT("filename")));
    CHECK_EQUAL(10, reporter.lastFailedLine);
    CHECK(Strings::StrStr(reporter.lastFailedTest, UNITTEST_TEXT("testname")));
}

TEST(TimeConstraintFailureIncludesTimeoutInformation)
{
    RecordingReporter reporter;
    TestResults result(&reporter);
    {
        ScopedCurrentTest scopedResult(result);
        TimeConstraint t(10, EmptyTestDetails());
        TimeHelpers::SleepMs(20);
    }

    CHECK(Strings::StrStr(reporter.lastFailedMessage, UNITTEST_TEXT("ime constraint")));
    CHECK(Strings::StrStr(reporter.lastFailedMessage, UNITTEST_TEXT("under 10ms")));
}

}
