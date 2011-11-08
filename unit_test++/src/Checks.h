#ifndef UNITTEST_CHECKS_H
#define UNITTEST_CHECKS_H

#include "Config.h"
#include "Strings.h"
#include "TestResults.h"
#include "MemoryOutStream.h"

namespace UnitTest {

template< typename Value >
bool Check(Value const value)
{
    return !!value; // doing double negative to avoid silly VS warnings
}

template< typename Expected, typename Actual >
void CheckEqual(TestResults& results, Expected const& expected,
                Actual const& actual, TestDetails const& details)
{
    if (!(expected == actual))
    {
        UnitTest::MemoryOutStream stream;
        stream << UNITTEST_TEXT("Expected ") << expected
            << UNITTEST_TEXT(" but was ") << actual;

        results.OnTestFailure(details, stream.GetText());
    }
}

void CheckEqual(TestResults& results, Char const* expected,
                Char const* actual, TestDetails const& details);

void CheckEqual(TestResults& results, Char* expected,
                Char* actual, TestDetails const& details);

void CheckEqual(TestResults& results, Char* expected,
                Char const* actual, TestDetails const& details);

void CheckEqual(TestResults& results, Char const* expected,
                Char* actual, TestDetails const& details);

template< typename Expected, typename Actual, typename Tolerance >
bool AreClose(Expected const& expected, Actual const& actual, Tolerance const& tolerance)
{
    return (actual >= (expected - tolerance)) && (actual <= (expected + tolerance));
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckClose(TestResults& results, Expected const& expected,
                Actual const& actual, Tolerance const& tolerance,
                TestDetails const& details)
{
    if (!AreClose(expected, actual, tolerance))
    { 
        UnitTest::MemoryOutStream stream;
        stream << UNITTEST_TEXT("Expected ") << expected << UNITTEST_TEXT(" +/- ")
            << tolerance << UNITTEST_TEXT(" but was ") << actual;

        results.OnTestFailure(details, stream.GetText());
    }
}


template< typename Expected, typename Actual >
void CheckArrayEqual(TestResults& results, Expected const& expected, Actual const& actual,
    int const count, TestDetails const& details)
{
    bool equal = true;
    for (int i = 0; i < count; ++i)
        equal &= (expected[i] == actual[i]);

    if (!equal)
    {
        UnitTest::MemoryOutStream stream;

        stream << UNITTEST_TEXT("Expected [ ");

        for (int expectedIndex = 0; expectedIndex < count; ++expectedIndex)
            stream << expected[expectedIndex] << UNITTEST_TEXT(" ");

        stream << UNITTEST_TEXT("] but was [ ");

        for (int actualIndex = 0; actualIndex < count; ++actualIndex)
            stream << actual[actualIndex] << UNITTEST_TEXT(" ");

        stream << UNITTEST_TEXT("]");

        results.OnTestFailure(details, stream.GetText());
    }
}

template< typename Expected, typename Actual, typename Tolerance >
bool ArrayAreClose(Expected const& expected, Actual const& actual, int const count, Tolerance const& tolerance)
{
    bool equal = true;
    for (int i = 0; i < count; ++i)
        equal &= AreClose(expected[i], actual[i], tolerance);
    return equal;
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckArrayClose(TestResults& results, Expected const& expected, Actual const& actual,
    int const count, Tolerance const& tolerance, TestDetails const& details)
{
    bool equal = ArrayAreClose(expected, actual, count, tolerance);

    if (!equal)
    {
        UnitTest::MemoryOutStream stream;

        stream << UNITTEST_TEXT("Expected [ ");
        for (int expectedIndex = 0; expectedIndex < count; ++expectedIndex)
            stream << expected[expectedIndex] << UNITTEST_TEXT(" ");
        stream << UNITTEST_TEXT("] +/- ") << tolerance << UNITTEST_TEXT(" but was [ ");

        for (int actualIndex = 0; actualIndex < count; ++actualIndex)
            stream << actual[actualIndex] << UNITTEST_TEXT(" ");
        stream << UNITTEST_TEXT("]");

        results.OnTestFailure(details, stream.GetText());
    }
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckArray2DClose(TestResults& results, Expected const& expected, Actual const& actual,
    int const rows, int const columns, Tolerance const& tolerance, TestDetails const& details)
{
    bool equal = true;
    for (int i = 0; i < rows; ++i)
        equal &= ArrayAreClose(expected[i], actual[i], columns, tolerance);

    if (!equal)
    {
        UnitTest::MemoryOutStream stream;

        stream << UNITTEST_TEXT("Expected [ ");    

        for (int expectedRow = 0; expectedRow < rows; ++expectedRow)
        {
            stream << UNITTEST_TEXT("[ ");
            for (int expectedColumn = 0; expectedColumn < columns; ++expectedColumn)
                stream << expected[expectedRow][expectedColumn] << UNITTEST_TEXT(" ");
            stream << UNITTEST_TEXT("] ");
        }

        stream << UNITTEST_TEXT("] +/- ") << tolerance << UNITTEST_TEXT(" but was [ ");

        for (int actualRow = 0; actualRow < rows; ++actualRow)
        {
            stream << UNITTEST_TEXT("[ ");
            for (int actualColumn = 0; actualColumn < columns; ++actualColumn)
                stream << actual[actualRow][actualColumn] << UNITTEST_TEXT(" ");
            stream << UNITTEST_TEXT("] ");
        }

        stream << UNITTEST_TEXT("]");

        results.OnTestFailure(details, stream.GetText());
    }
}

}

#endif
