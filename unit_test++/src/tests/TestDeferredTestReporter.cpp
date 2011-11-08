#include "../UnitTest++.h"
#include "../DeferredTestReporter.h"
#include "../Config.h"
#include <cstring>

namespace UnitTest
{

namespace 
{

struct MockDeferredTestReporter : public DeferredTestReporter
{
    virtual void ReportSummary(int, int, int, float) 
    {
    }
};

struct DeferredTestReporterFixture
{
    DeferredTestReporterFixture()
        : testName(UNITTEST_TEXT("UniqueTestName"))
        , testSuite(UNITTEST_TEXT("UniqueTestSuite"))
        , fileName(UNITTEST_TEXT("filename.h"))
        , lineNumber(12)
        , details(testName.c_str(), testSuite.c_str(), fileName.c_str(), lineNumber)
    {
    }

    MockDeferredTestReporter reporter;
    String const testName;
    String const testSuite;
    String const fileName;
    int const lineNumber;
    TestDetails const details;
};

TEST_FIXTURE(DeferredTestReporterFixture, ReportTestStartCreatesANewDeferredTest)
{
    reporter.ReportTestStart(details);
    CHECK_EQUAL(1, (int)reporter.GetResults().size());
}

TEST_FIXTURE(DeferredTestReporterFixture, ReportTestStartCapturesTestNameAndSuite)
{
    reporter.ReportTestStart(details);

    DeferredTestResult const& result = reporter.GetResults().at(0);
    CHECK_EQUAL(testName.c_str(), result.testName);
    CHECK_EQUAL(testSuite.c_str(), result.suiteName);
}

TEST_FIXTURE(DeferredTestReporterFixture, ReportTestEndCapturesTestTime)
{
    float const elapsed = 123.45f;
    reporter.ReportTestStart(details);
    reporter.ReportTestFinish(details, elapsed);

    DeferredTestResult const& result = reporter.GetResults().at(0);
    CHECK_CLOSE(elapsed, result.timeElapsed, 0.0001f);
}

TEST_FIXTURE(DeferredTestReporterFixture, ReportFailureSavesFailureDetails)
{
    Char const* failure = UNITTEST_TEXT("failure");

    reporter.ReportTestStart(details);
    reporter.ReportFailure(details, failure);

    DeferredTestResult const& result = reporter.GetResults().at(0);
    CHECK(result.failed == true);
    CHECK_EQUAL(fileName.c_str(), result.failureFile);
}

TEST_FIXTURE(DeferredTestReporterFixture, ReportFailureSavesFailureDetailsForMultipleFailures)
{
    Char const* failure1 = UNITTEST_TEXT("failure 1");
    Char const* failure2 = UNITTEST_TEXT("failure 2");

    reporter.ReportTestStart(details);
    reporter.ReportFailure(details, failure1);
    reporter.ReportFailure(details, failure2);

    DeferredTestResult const& result = reporter.GetResults().at(0);
    CHECK_EQUAL(2, (int)result.failures.size());
    CHECK_EQUAL(failure1, result.failures[0].second);
    CHECK_EQUAL(failure2, result.failures[1].second);
}

TEST_FIXTURE(DeferredTestReporterFixture, DeferredTestReporterTakesCopyOfFailureMessage)
{
    reporter.ReportTestStart(details);

    Char failureMessage[128];
    Char const* goodStr = UNITTEST_TEXT("Real failure message");
    Char const* badStr = UNITTEST_TEXT("Bogus failure message");
    
    Strings::StrCpy(failureMessage, goodStr);
    reporter.ReportFailure(details, failureMessage);
    Strings::StrCpy(failureMessage, badStr);

    DeferredTestResult const& result = reporter.GetResults().at(0);
    DeferredTestResult::Failure const& failure = result.failures.at(0);
    CHECK_EQUAL(goodStr, failure.second);
}

}}
