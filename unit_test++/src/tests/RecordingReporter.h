#ifndef UNITTEST_RECORDINGREPORTER_H
#define UNITTEST_RECORDINGREPORTER_H

#include "../TestReporter.h"
#include "../TestDetails.h"
#include "../Strings.h"

struct RecordingReporter : public UnitTest::TestReporter
{
private:
    enum { kMaxStringLength = 256 };

public:
    typedef UnitTest::Char Char;

    RecordingReporter()
        : testRunCount(0)
        , testFailedCount(0)
        , lastFailedLine(0)
        , testFinishedCount(0)
        , lastFinishedTestTime(0)
        , summaryTotalTestCount(0)
        , summaryFailedTestCount(0)
        , summaryFailureCount(0)
        , summarySecondsElapsed(0)
    {
        lastStartedSuite[0] = UNITTEST_TEXT('\0');
        lastStartedTest[0] = UNITTEST_TEXT('\0');
        lastFailedFile[0] = UNITTEST_TEXT('\0');
        lastFailedSuite[0] = UNITTEST_TEXT('\0');
        lastFailedTest[0] = UNITTEST_TEXT('\0');
        lastFailedMessage[0] = UNITTEST_TEXT('\0');
        lastFinishedSuite[0] = UNITTEST_TEXT('\0');
        lastFinishedTest[0] = UNITTEST_TEXT('\0');
    }

    virtual void ReportTestStart(UnitTest::TestDetails const& test)
    {
        ++testRunCount;
        UnitTest::Strings::StrCpy(lastStartedSuite, test.suiteName);
        UnitTest::Strings::StrCpy(lastStartedTest, test.testName);
    }

    virtual void ReportFailure(UnitTest::TestDetails const& test, Char const* failure)
    {
        ++testFailedCount;
        UnitTest::Strings::StrCpy(lastFailedFile, test.filename);
        lastFailedLine = test.lineNumber;
        UnitTest::Strings::StrCpy(lastFailedSuite, test.suiteName);
        UnitTest::Strings::StrCpy(lastFailedTest, test.testName);
        UnitTest::Strings::StrCpy(lastFailedMessage, failure);
    }

    virtual void ReportTestFinish(UnitTest::TestDetails const& test, float testDuration)
    {
        ++testFinishedCount;
        UnitTest::Strings::StrCpy(lastFinishedSuite, test.suiteName);
        UnitTest::Strings::StrCpy(lastFinishedTest, test.testName);
        lastFinishedTestTime = testDuration;
    }

    virtual void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed) 
    {
        summaryTotalTestCount = totalTestCount;
        summaryFailedTestCount = failedTestCount;
        summaryFailureCount = failureCount;
        summarySecondsElapsed = secondsElapsed;
    }

    int testRunCount;
    Char lastStartedSuite[kMaxStringLength];
    Char lastStartedTest[kMaxStringLength];

    int testFailedCount;
    Char lastFailedFile[kMaxStringLength];
    int lastFailedLine;
    Char lastFailedSuite[kMaxStringLength];
    Char lastFailedTest[kMaxStringLength];
    Char lastFailedMessage[kMaxStringLength];

    int testFinishedCount;
    Char lastFinishedSuite[kMaxStringLength];
    Char lastFinishedTest[kMaxStringLength];
    float lastFinishedTestTime;

    int summaryTotalTestCount;
    int summaryFailedTestCount;
    int summaryFailureCount;
    float summarySecondsElapsed;
};


#endif
