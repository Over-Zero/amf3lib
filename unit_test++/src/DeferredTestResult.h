#ifndef UNITTEST_DEFERREDTESTRESULT_H
#define UNITTEST_DEFERREDTESTRESULT_H

#include "Strings.h"
#include <vector>

namespace UnitTest
{

struct DeferredTestResult
{
    DeferredTestResult();
    DeferredTestResult(Char const* suite, Char const* test);

    UnitTest::String suiteName;
    UnitTest::String testName;
    UnitTest::String failureFile;
    
    typedef std::pair< int, UnitTest::String > Failure;
    typedef std::vector< Failure > FailureVec;
    FailureVec failures;
    
    float timeElapsed;
	bool failed;
};

}

#endif //UNITTEST_DEFERREDTESTRESULT_H
