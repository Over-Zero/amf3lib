#ifndef UNITTEST_TESTDETAILS_H
#define UNITTEST_TESTDETAILS_H

#include "Strings.h"

namespace UnitTest {

class TestDetails
{
public:
    TestDetails(Char const* testName, Char const* suiteName, Char const* filename, int lineNumber);
    TestDetails(const TestDetails& details, int lineNumber);

    Char const* const suiteName;
    Char const* const testName;
    Char const* const filename;
    int const lineNumber;

    TestDetails(TestDetails const&); // Why is it public? --> http://gcc.gnu.org/bugs.html#cxx_rvalbind
private:
    TestDetails& operator=(TestDetails const&);
};

}

#endif
