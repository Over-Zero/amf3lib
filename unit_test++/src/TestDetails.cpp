#include "TestDetails.h"

namespace UnitTest {

TestDetails::TestDetails(Char const* testName_, Char const* suiteName_, Char const* filename_, int lineNumber_)
    : suiteName(suiteName_)
    , testName(testName_)
    , filename(filename_)
    , lineNumber(lineNumber_)
{
}

TestDetails::TestDetails(const TestDetails& details, int lineNumber_)
    : suiteName(details.suiteName)
    , testName(details.testName)
    , filename(details.filename)
    , lineNumber(lineNumber_)
{
}


}
