#ifndef UNITTEST_CHECKMACROS_H 
#define UNITTEST_CHECKMACROS_H

#include "Checks.h"
#include "AssertException.h"
#include "MemoryOutStream.h"
#include "TestDetails.h"
#include "CurrentTest.h"

#ifdef CHECK
    #error UnitTest++ redefines CHECK
#endif

#ifdef CHECK_EQUAL
    #error UnitTest++ redefines CHECK_EQUAL
#endif

#ifdef CHECK_CLOSE
    #error UnitTest++ redefines CHECK_CLOSE
#endif

#ifdef CHECK_ARRAY_EQUAL
    #error UnitTest++ redefines CHECK_ARRAY_EQUAL
#endif

#ifdef CHECK_ARRAY_CLOSE
    #error UnitTest++ redefines CHECK_ARRAY_CLOSE
#endif

#ifdef CHECK_ARRAY2D_CLOSE
    #error UnitTest++ redefines CHECK_ARRAY2D_CLOSE
#endif

#define UNITTEST_GET_TEST_DETAILS()                                       \
    UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__)

#define CHECK(value)                                                      \
    do                                                                    \
    {                                                                     \
        try {                                                             \
            if (!UnitTest::Check(value))                                  \
                UnitTest::CurrentTest::Results()->OnTestFailure(          \
                    UNITTEST_GET_TEST_DETAILS(),                          \
                    UNITTEST_TEXT(#value));                               \
        }                                                                 \
        catch (...) {                                                     \
            UnitTest::CurrentTest::Results()->OnTestFailure(              \
                UNITTEST_GET_TEST_DETAILS(),                              \
                UNITTEST_TEXT("Unhandled exception in CHECK(")            \
                UNITTEST_TEXT(#value) UNITTEST_TEXT(")"));                \
        }                                                                 \
    } while (0)

#define CHECK_EQUAL(expected, actual)                                     \
    do                                                                    \
    {                                                                     \
        try {                                                             \
            UnitTest::CheckEqual(*UnitTest::CurrentTest::Results(),       \
                expected, actual, UNITTEST_GET_TEST_DETAILS());           \
        }                                                                 \
        catch (...) {                                                     \
            UnitTest::CurrentTest::Results()->OnTestFailure(              \
                UNITTEST_GET_TEST_DETAILS(),                              \
                UNITTEST_TEXT("Unhandled exception in CHECK_EQUAL(")      \
                UNITTEST_TEXT(#expected) UNITTEST_TEXT(", ")              \
                UNITTEST_TEXT(#actual) UNITTEST_TEXT(")"));               \
        }                                                                 \
    } while (0)

#define CHECK_CLOSE(expected, actual, tolerance)                          \
    do                                                                    \
    {                                                                     \
        try {                                                             \
            UnitTest::CheckClose(*UnitTest::CurrentTest::Results(),       \
                expected, actual, tolerance,                              \
                UNITTEST_GET_TEST_DETAILS());                             \
        }                                                                 \
        catch (...) {                                                     \
            UnitTest::CurrentTest::Results()->OnTestFailure(              \
                UNITTEST_GET_TEST_DETAILS(),                              \
                UNITTEST_TEXT("Unhandled exception in CHECK_CLOSE(")      \
                UNITTEST_TEXT(#expected) UNITTEST_TEXT(", ")              \
                UNITTEST_TEXT(#actual) UNITTEST_TEXT(")"));               \
        }                                                                 \
    } while (0)

#define CHECK_ARRAY_EQUAL(expected, actual, count)                        \
    do                                                                    \
    {                                                                     \
        try {                                                             \
            UnitTest::CheckArrayEqual(*UnitTest::CurrentTest::Results(),  \
                expected, actual, count,                                  \
                UNITTEST_GET_TEST_DETAILS());                             \
        }                                                                 \
        catch (...) {                                                     \
            UnitTest::CurrentTest::Results()->OnTestFailure(              \
                UNITTEST_GET_TEST_DETAILS(),                              \
                UNITTEST_TEXT("Unhandled exception in CHECK_ARRAY_EQUAL(")\
                UNITTEST_TEXT(#expected) UNITTEST_TEXT(", ")              \
                UNITTEST_TEXT(#actual) UNITTEST_TEXT(")"));               \
        }                                                                 \
    } while (0)

#define CHECK_ARRAY_CLOSE(expected, actual, count, tolerance)             \
    do                                                                    \
    {                                                                     \
        try {                                                             \
            UnitTest::CheckArrayClose(*UnitTest::CurrentTest::Results(),  \
                expected, actual, count, tolerance,                       \
                UNITTEST_GET_TEST_DETAILS());                             \
        }                                                                 \
        catch (...) {                                                     \
            UnitTest::CurrentTest::Results()->OnTestFailure(              \
                UNITTEST_GET_TEST_DETAILS(),                              \
                UNITTEST_TEXT("Unhandled exception in CHECK_ARRAY_CLOSE(")\
                UNITTEST_TEXT(#expected) UNITTEST_TEXT(", ")              \
                UNITTEST_TEXT(#actual) UNITTEST_TEXT(")"));               \
        }                                                                 \
    } while (0)

#define CHECK_ARRAY2D_CLOSE(expected, actual, rows, columns, tolerance)   \
    do                                                                    \
    {                                                                     \
        try {                                                             \
            UnitTest::CheckArray2DClose(*UnitTest::CurrentTest::Results(),\
                expected, actual, rows, columns, tolerance,               \
                UNITTEST_GET_TEST_DETAILS());                             \
        }                                                                 \
        catch (...) {                                                     \
            UnitTest::CurrentTest::Results()->OnTestFailure(              \
                UNITTEST_GET_TEST_DETAILS(),                              \
                UNITTEST_TEXT("Unhandled exception in CHECK_ARRAY_CLOSE(")\
                UNITTEST_TEXT(#expected) UNITTEST_TEXT(", ")              \
                UNITTEST_TEXT(#actual) UNITTEST_TEXT(")"));               \
        }                                                                 \
    } while (0)


#define CHECK_THROW(expression, ExpectedExceptionType)                    \
    do                                                                    \
    {                                                                     \
        bool caught_ = false;                                             \
        try { expression; }                                               \
        catch (ExpectedExceptionType const&) { caught_ = true; }          \
        catch (...) {}                                                    \
        if (!caught_)                                                     \
            UnitTest::CurrentTest::Results()->OnTestFailure(              \
                UNITTEST_GET_TEST_DETAILS(),                              \
                UNITTEST_TEXT("Expected exception: \"")                   \
                UNITTEST_TEXT(#ExpectedExceptionType)                     \
                UNITTEST_TEXT("\" not thrown"));                          \
    } while(0)

#define CHECK_ASSERT(expression)                                          \
    CHECK_THROW(expression, UnitTest::AssertException);

#endif
