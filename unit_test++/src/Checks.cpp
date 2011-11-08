#include "Checks.h"
#include <cstring>

namespace UnitTest {

namespace {

void CheckStringsEqual(TestResults& results, Char const* expected, Char const* actual, 
                       TestDetails const& details)
{
    if (Strings::StrCmp(expected, actual))
    {
        UnitTest::MemoryOutStream stream;
        stream << UNITTEST_TEXT("Expected ") << expected
            << UNITTEST_TEXT(" but was ") << actual;

        results.OnTestFailure(details, stream.GetText());
    }
}

}


void CheckEqual(TestResults& results, Char const* expected, Char const* actual,
                TestDetails const& details)
{
    CheckStringsEqual(results, expected, actual, details);
}

void CheckEqual(TestResults& results, Char* expected, Char* actual,
                TestDetails const& details)
{
    CheckStringsEqual(results, expected, actual, details);
}

void CheckEqual(TestResults& results, Char* expected, Char const* actual,
                TestDetails const& details)
{
    CheckStringsEqual(results, expected, actual, details);
}

void CheckEqual(TestResults& results, Char const* expected, Char* actual,
                TestDetails const& details)
{
    CheckStringsEqual(results, expected, actual, details);
}


}
