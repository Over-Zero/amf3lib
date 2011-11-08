#ifndef UNITTEST_EXECUTE_TEST_H
#define UNITTEST_EXECUTE_TEST_H

#include "TestDetails.h"
#include "MemoryOutStream.h"
#include "AssertException.h"
#include "CurrentTest.h"
#include "Strings.h"

#ifdef UNITTEST_POSIX
#include "Posix/SignalTranslator.h"
#endif

namespace UnitTest {

template< typename T >
void ExecuteTest(T& testObject, TestDetails const& details)
{
    CurrentTest::Details() = &details;

    try
    {
#ifdef UNITTEST_POSIX
        UNITTEST_THROW_SIGNALS
#endif
            testObject.RunImpl();
    }
    catch (AssertException const& e)
    {
        CurrentTest::Results()->OnTestFailure(
            TestDetails(details.testName, details.suiteName, e.Filename(), e.LineNumber()), e.What());
    }
    catch (std::exception const& e)
    {
        MemoryOutStream stream;
        stream << UNITTEST_TEXT("Unhandled exception: ") << Strings::Make(e.what());
        CurrentTest::Results()->OnTestFailure(details, stream.GetText());
    }
    catch (...)
    {
        CurrentTest::Results()->OnTestFailure(details, UNITTEST_TEXT("Unhandled exception: Crash!"));
    }
}

}

#endif
