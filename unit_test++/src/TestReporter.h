#ifndef UNITTEST_TESTREPORTER_H
#define UNITTEST_TESTREPORTER_H

#include "Strings.h"

namespace UnitTest {

class TestDetails;

class TestReporter
{
public:
    virtual ~TestReporter();

    virtual void ReportTestStart(TestDetails const& test) = 0;
    virtual void ReportFailure(TestDetails const& test, Char const* failure) = 0;
    virtual void ReportTestFinish(TestDetails const& test, float secondsElapsed) = 0;
    virtual void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed) = 0;
};

}
#endif
