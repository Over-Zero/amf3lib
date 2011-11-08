#include "DeferredTestResult.h"
#include "Config.h"

namespace UnitTest
{

DeferredTestResult::DeferredTestResult()
	: suiteName(UNITTEST_TEXT(""))
	, testName(UNITTEST_TEXT(""))
	, failureFile(UNITTEST_TEXT(""))
	, timeElapsed(0.0f)
	, failed(false)
{
}

DeferredTestResult::DeferredTestResult(Char const* suite, Char const* test)
	: suiteName(suite)
	, testName(test)
	, failureFile(UNITTEST_TEXT(""))
	, timeElapsed(0.0f)
	, failed(false)
{
}

}
