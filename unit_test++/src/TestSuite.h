#ifndef UNITTEST_TESTSUITE_H
#define UNITTEST_TESTSUITE_H

#include "Strings.h"

namespace UnitTestSuite {

    inline UnitTest::Char const* GetSuiteName()
    {
        return UNITTEST_TEXT("DefaultSuite");
    }

}

#endif

