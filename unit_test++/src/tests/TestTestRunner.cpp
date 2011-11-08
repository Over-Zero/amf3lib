#include "../UnitTest++.h"
#include "RecordingReporter.h"
#include "../ReportAssert.h"
#include "../TestList.h"
#include "../TimeHelpers.h"
#include "../TimeConstraint.h"

using namespace UnitTest;

namespace
{

struct MockTest : public Test
{
    MockTest(Char const* testName, bool const success_, bool const assert_, int const count_ = 1)
        : Test(testName)
        , success(success_)
        , asserted(assert_)
        , count(count_)
    {
    }

    virtual void RunImpl(TestResults& testResults_) const
    {
        for (int i=0; i < count; ++i)
        {
            if (asserted)
                ReportAssert(UNITTEST_TEXT("desc"), UNITTEST_TEXT("file"), 0);
            else if (!success)
                testResults_.OnTestFailure(m_details, UNITTEST_TEXT("message"));
        }
    }

    bool const success;
    bool const asserted;
    int const count;
};


struct TestRunnerFixture
{
    TestRunnerFixture()
        : runner(reporter)
    {
    }

    RecordingReporter reporter;
    TestList list;
    TestRunner runner;
};

TEST_FIXTURE(TestRunnerFixture, TestStartIsReportedCorrectly)
{
    MockTest test(UNITTEST_TEXT("goodtest"), true, false);
    list.Add(&test);

    runner.RunTestsIf(list, NULL, True(), 0);
    CHECK_EQUAL(1, reporter.testRunCount);
    CHECK_EQUAL(UNITTEST_TEXT("goodtest"), reporter.lastStartedTest);
}

TEST_FIXTURE(TestRunnerFixture, TestFinishIsReportedCorrectly)
{
    MockTest test(UNITTEST_TEXT("goodtest"), true, false);
    list.Add(&test);

    runner.RunTestsIf(list, NULL, True(), 0);
    CHECK_EQUAL(1, reporter.testFinishedCount);
    CHECK_EQUAL(UNITTEST_TEXT("goodtest"), reporter.lastFinishedTest);
}

class SlowTest : public Test
{
public:
    SlowTest() : Test(UNITTEST_TEXT("slow"),
        UNITTEST_TEXT("somesuite"),
        UNITTEST_TEXT("filename"), 123) {}
    virtual void RunImpl(TestResults&) const
    {
        TimeHelpers::SleepMs(20);
    }
};

TEST_FIXTURE(TestRunnerFixture, TestFinishIsCalledWithCorrectTime)
{
    SlowTest test;
    list.Add(&test);

    runner.RunTestsIf(list, NULL, True(), 0);
    CHECK(reporter.lastFinishedTestTime >= 0.005f && reporter.lastFinishedTestTime <= 0.050f);
}

TEST_FIXTURE(TestRunnerFixture, FailureCountIsZeroWhenNoTestsAreRun)
{
    CHECK_EQUAL(0, runner.RunTestsIf(list, NULL, True(), 0));
    CHECK_EQUAL(0, reporter.testRunCount);
    CHECK_EQUAL(0, reporter.testFailedCount);
}

TEST_FIXTURE(TestRunnerFixture, CallsReportFailureOncePerFailingTest)
{
    MockTest test1(UNITTEST_TEXT("test"), false, false);
    list.Add(&test1);
    MockTest test2(UNITTEST_TEXT("test"), true, false);
    list.Add(&test2);
    MockTest test3(UNITTEST_TEXT("test"), false, false);
    list.Add(&test3);

    CHECK_EQUAL(2, 	runner.RunTestsIf(list, NULL, True(), 0));
    CHECK_EQUAL(2, reporter.testFailedCount);
}

TEST_FIXTURE(TestRunnerFixture, TestsThatAssertAreReportedAsFailing)
{
    MockTest test(UNITTEST_TEXT("test"), true, true);
    list.Add(&test);

    runner.RunTestsIf(list, NULL, True(), 0);
    CHECK_EQUAL(1, reporter.testFailedCount);
}


TEST_FIXTURE(TestRunnerFixture, ReporterNotifiedOfTestCount)
{
    MockTest test1(UNITTEST_TEXT("test"), true, false);
    MockTest test2(UNITTEST_TEXT("test"), true, false);
    MockTest test3(UNITTEST_TEXT("test"), true, false);
    list.Add(&test1);
    list.Add(&test2);
    list.Add(&test3);

    runner.RunTestsIf(list, NULL, True(), 0);
    CHECK_EQUAL(3, reporter.summaryTotalTestCount);
}

TEST_FIXTURE(TestRunnerFixture, ReporterNotifiedOfFailedTests)
{
    MockTest test1(UNITTEST_TEXT("test"), false, false, 2);
    MockTest test2(UNITTEST_TEXT("test"), true, false);
    MockTest test3(UNITTEST_TEXT("test"), false, false, 3);
    list.Add(&test1);
    list.Add(&test2);
    list.Add(&test3);

    runner.RunTestsIf(list, NULL, True(), 0);
    CHECK_EQUAL(2, reporter.summaryFailedTestCount);
}

TEST_FIXTURE(TestRunnerFixture, ReporterNotifiedOfFailures)
{
    MockTest test1(UNITTEST_TEXT("test"), false, false, 2);
    MockTest test2(UNITTEST_TEXT("test"), true, false);
    MockTest test3(UNITTEST_TEXT("test"), false, false, 3);
    list.Add(&test1);
    list.Add(&test2);
    list.Add(&test3);

    runner.RunTestsIf(list, NULL, True(), 0);
    CHECK_EQUAL(5, reporter.summaryFailureCount);
}

TEST_FIXTURE(TestRunnerFixture, SlowTestPassesForHighTimeThreshold)
{
    SlowTest test;
    list.Add(&test);

    runner.RunTestsIf(list, NULL, True(), 0);
    CHECK_EQUAL(0, reporter.testFailedCount);
}

TEST_FIXTURE(TestRunnerFixture, SlowTestFailsForLowTimeThreshold)
{
    SlowTest test;
    list.Add(&test);

    runner.RunTestsIf(list, NULL, True(), 3);
    CHECK_EQUAL(1, reporter.testFailedCount);
}

TEST_FIXTURE(TestRunnerFixture, SlowTestHasCorrectFailureInformation)
{
    SlowTest test;
    list.Add(&test);

    runner.RunTestsIf(list, NULL, True(), 3);

    CHECK_EQUAL(test.m_details.testName, reporter.lastFailedTest);
    CHECK(Strings::StrStr(test.m_details.filename, reporter.lastFailedFile));
    CHECK_EQUAL(test.m_details.lineNumber, reporter.lastFailedLine);

    CHECK(Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("Global time constraint failed")));
    CHECK(Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("3ms")));
}

TEST_FIXTURE(TestRunnerFixture, SlowTestWithTimeExemptionPasses)
{
    class SlowExemptedTest : public Test
    {
    public:
        SlowExemptedTest() : Test(UNITTEST_TEXT("slowexempted"), UNITTEST_TEXT(""), 0) {}
        virtual void RunImpl(TestResults&) const
        {
            UNITTEST_TIME_CONSTRAINT_EXEMPT();
            TimeHelpers::SleepMs(20);
        }
    };

    SlowExemptedTest test;
    list.Add(&test);

    runner.RunTestsIf(list, NULL, True(), 3);
    CHECK_EQUAL(0, reporter.testFailedCount);
}

struct TestSuiteFixture
{
    TestSuiteFixture()
        : test1(UNITTEST_TEXT("TestInDefaultSuite"))
        , test2(UNITTEST_TEXT("TestInOtherSuite"), UNITTEST_TEXT("OtherSuite"))
        , test3(UNITTEST_TEXT("SecondTestInDefaultSuite"))
        , runner(reporter)
    {
        list.Add(&test1);
        list.Add(&test2);
    }

    Test test1;
    Test test2;
    Test test3;
    RecordingReporter reporter;
    TestList list;
    TestRunner runner;
};

TEST_FIXTURE(TestSuiteFixture, TestRunnerRunsAllSuitesIfNullSuiteIsPassed)
{
    runner.RunTestsIf(list, NULL, True(), 0);
    CHECK_EQUAL(2, reporter.summaryTotalTestCount);
}

TEST_FIXTURE(TestSuiteFixture,TestRunnerRunsOnlySpecifiedSuite)
{
    runner.RunTestsIf(list, UNITTEST_TEXT("OtherSuite"), True(), 0);
    CHECK_EQUAL(1, reporter.summaryTotalTestCount);
    CHECK_EQUAL(UNITTEST_TEXT("TestInOtherSuite"), reporter.lastFinishedTest);
}

struct RunTestIfNameIs
{
    RunTestIfNameIs(Char const* name_)
        : name(name_)
    {		
    }

    bool operator()(const Test* const test) const
    {
        return (0 == Strings::StrCmp(test->m_details.testName, name));
    }

    Char const* name;
};

TEST(TestMockPredicateBehavesCorrectly)
{
    RunTestIfNameIs predicate(UNITTEST_TEXT("pass"));

    Test pass(UNITTEST_TEXT("pass"));
    Test fail(UNITTEST_TEXT("fail"));

    CHECK(predicate(&pass));
    CHECK(!predicate(&fail));	
}

TEST_FIXTURE(TestRunnerFixture, TestRunnerRunsTestsThatPassPredicate)
{
    Test should_run(UNITTEST_TEXT("goodtest"));
    list.Add(&should_run);

    Test should_not_run(UNITTEST_TEXT("badtest"));
    list.Add(&should_not_run);

    runner.RunTestsIf(list, NULL, RunTestIfNameIs(UNITTEST_TEXT("goodtest")), 0);
    CHECK_EQUAL(1, reporter.testRunCount);
    CHECK_EQUAL(UNITTEST_TEXT("goodtest"), reporter.lastStartedTest);
}

TEST_FIXTURE(TestRunnerFixture, TestRunnerOnlyRunsTestsInSpecifiedSuiteAndThatPassPredicate)
{
    Test runningTest1(UNITTEST_TEXT("goodtest"), UNITTEST_TEXT("suite"));
    Test skippedTest2(UNITTEST_TEXT("goodtest"));
    Test skippedTest3(UNITTEST_TEXT("badtest"), UNITTEST_TEXT("suite"));
    Test skippedTest4(UNITTEST_TEXT("badtest"));

    list.Add(&runningTest1);
    list.Add(&skippedTest2);
    list.Add(&skippedTest3);
    list.Add(&skippedTest4);   

    runner.RunTestsIf(list, UNITTEST_TEXT("suite"),
        RunTestIfNameIs(UNITTEST_TEXT("goodtest")), 0);

    CHECK_EQUAL(1, reporter.testRunCount);
    CHECK_EQUAL(UNITTEST_TEXT("goodtest"), reporter.lastStartedTest); 
    CHECK_EQUAL(UNITTEST_TEXT("suite"), reporter.lastStartedSuite);    
}

}
