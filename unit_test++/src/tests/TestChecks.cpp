#include "../UnitTest++.h"
#include "RecordingReporter.h"

using namespace UnitTest;


namespace {

using UnitTest::Char;
using UnitTest::Strings;

TestDetails EmptyTestDetails()
{
    return TestDetails(UNITTEST_TEXT(""), UNITTEST_TEXT(""), UNITTEST_TEXT(""), 0);
}

TEST(CheckEqualWithUnsignedLong)
{
    TestResults results;
    unsigned long something = 2;
    CHECK_EQUAL(something, something);
}

TEST(CheckEqualsWithStringsFailsOnDifferentStrings)
{
    Char txt1[] = UNITTEST_TEXT("Hello");
    Char txt2[] = UNITTEST_TEXT("Hallo");
    TestResults results;
    CheckEqual(results, txt1, txt2, EmptyTestDetails());
    CHECK_EQUAL(1, results.GetFailureCount());
}

Char txt1[] = UNITTEST_TEXT("Hello"); // non-const on purpose so no folding of duplicate data
Char txt2[] = UNITTEST_TEXT("Hello");

TEST(CheckEqualsWithStringsWorksOnContentsNonConstNonConst)
{
    Char const* const p1 = txt1;
    Char const* const p2 = txt2;
    TestResults results;
    CheckEqual(results, p1, p2, EmptyTestDetails());
    CHECK_EQUAL(0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsConstConst)
{
    Char* const p1 = txt1;
    Char* const p2 = txt2;
    TestResults results;
    CheckEqual(results, p1, p2, EmptyTestDetails());
    CHECK_EQUAL(0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsNonConstConst)
{
    Char* const p1 = txt1;
    Char const* const p2 = txt2;
    TestResults results;
    CheckEqual(results, p1, p2, EmptyTestDetails());
    CHECK_EQUAL(0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsConstNonConst)
{
    Char const* const p1 = txt1;
    Char* const p2 = txt2;
    TestResults results;
    CheckEqual(results, p1, p2, EmptyTestDetails());
    CHECK_EQUAL(0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsWithALiteral)
{
    Char const* const p1 = txt1;
    TestResults results;
    CheckEqual(results, UNITTEST_TEXT("Hello"), p1, EmptyTestDetails());
    CHECK_EQUAL(0, results.GetFailureCount());
}

TEST(CheckEqualFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    const int something = 2;
    CheckEqual(results, 1, something, EmptyTestDetails());

    CHECK(Strings::StrStr(reporter.lastFailedMessage, UNITTEST_TEXT("xpected 1")));
    CHECK(Strings::StrStr(reporter.lastFailedMessage, UNITTEST_TEXT("was 2")));
}

TEST(CheckEqualFailureIncludesCheckExpectedAndActualStrings)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    UnitTest::TestResults testResults(&reporter);
    CheckEqual(results, UNITTEST_TEXT("ABC"), UNITTEST_TEXT("123"), EmptyTestDetails());

    CHECK(Strings::StrStr(reporter.lastFailedMessage, UNITTEST_TEXT("xpected ABC")));
    CHECK(Strings::StrStr(reporter.lastFailedMessage, UNITTEST_TEXT("was 123")));
}

TEST(CheckEqualFailureIncludesDetails)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails const details(
        UNITTEST_TEXT("mytest"),
        UNITTEST_TEXT("mysuite"),
        UNITTEST_TEXT("file.h"),
        101);

    CheckEqual(results, 1, 2, details);

    CHECK_EQUAL(UNITTEST_TEXT("mytest"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("mysuite"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("file.h"), reporter.lastFailedFile);
    CHECK_EQUAL(101, reporter.lastFailedLine);
}

TEST(CheckCloseTrue)
{
    TestResults results;
    CheckClose(results, 3.001f, 3.0f, 0.1f, EmptyTestDetails());
    CHECK_EQUAL(0, results.GetFailureCount());
}

TEST(CheckCloseFalse)
{
    TestResults results;
    CheckClose(results, 3.12f, 3.0f, 0.1f, EmptyTestDetails());
    CHECK_EQUAL(1, results.GetFailureCount());
}

TEST(CheckCloseWithZeroEpsilonWorksForSameNumber)
{
    TestResults results;
    CheckClose(results, 0.1f, 0.1f, 0, EmptyTestDetails());
    CHECK_EQUAL(0, results.GetFailureCount());
}

TEST(CheckCloseWithNaNFails)
{
    union
    {
        unsigned int bitpattern;
        float nan;
    };
    bitpattern = 0xFFFFFFFF;
    TestResults results;
    CheckClose(results, 3.0f, nan, 0.1f, EmptyTestDetails());
    CHECK_EQUAL(1, results.GetFailureCount());
}

TEST(CheckCloseWithNaNAgainstItselfFails)
{
    union
    {
        unsigned int bitpattern;
        float nan;
    };
    bitpattern = 0xFFFFFFFF;
    TestResults results;
    CheckClose(results, nan, nan, 0.1f, EmptyTestDetails());
    CHECK_EQUAL(1, results.GetFailureCount());
}

TEST(CheckCloseFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    const float expected = 0.9f;
    const float actual = 1.1f;
    CheckClose(results, expected, actual, 0.01f, EmptyTestDetails());

    CHECK(Strings::StrStr(reporter.lastFailedMessage, UNITTEST_TEXT("xpected 0.9")));
    CHECK(Strings::StrStr(reporter.lastFailedMessage, UNITTEST_TEXT("was 1.1")));
}

TEST(CheckCloseFailureIncludesTolerance)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    CheckClose(results, 2, 3, 0.01f, EmptyTestDetails());

    CHECK(Strings::StrStr(reporter.lastFailedMessage, UNITTEST_TEXT("0.01")));
}

TEST(CheckCloseFailureIncludesDetails)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails const details(
        UNITTEST_TEXT("mytest"),
        UNITTEST_TEXT("mysuite"),
        UNITTEST_TEXT("header.h"),
        10);

    CheckClose(results, 2, 3, 0.01f, details);

    CHECK_EQUAL(UNITTEST_TEXT("mytest"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("mysuite"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("header.h"), reporter.lastFailedFile);
    CHECK_EQUAL(10, reporter.lastFailedLine);
}


TEST(CheckArrayEqualTrue)
{
    TestResults results;

    int const array[3] = { 1, 2, 3 };
    CheckArrayEqual(results, array, array, 3, EmptyTestDetails());
    CHECK_EQUAL(0, results.GetFailureCount());
}

TEST(CheckArrayEqualFalse)
{
    TestResults results;

    int const array1[3] = { 1, 2, 3 };
    int const array2[3] = { 1, 2, 2 };
    CheckArrayEqual(results, array1, array2, 3, EmptyTestDetails());
    CHECK_EQUAL(1, results.GetFailureCount());
}

TEST(CheckArrayCloseTrue)
{
    TestResults results;

    float const array1[3] = { 1.0f, 1.5f, 2.0f };
    float const array2[3] = { 1.01f, 1.51f, 2.01f };
    CheckArrayClose(results, array1, array2, 3, 0.02f, EmptyTestDetails());
    CHECK_EQUAL(0, results.GetFailureCount());
}

TEST(CheckArrayCloseFalse)
{
    TestResults results;

    float const array1[3] = { 1.0f, 1.5f, 2.0f };
    float const array2[3] = { 1.01f, 1.51f, 2.01f };
    CheckArrayClose(results, array1, array2, 3, 0.001f, EmptyTestDetails());
    CHECK_EQUAL(1, results.GetFailureCount());
}

TEST(CheckArrayCloseFailureIncludesDetails)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails const details(
        UNITTEST_TEXT("arrayCloseTest"),
        UNITTEST_TEXT("arrayCloseSuite"),
        UNITTEST_TEXT("file"),
        1337);

    float const array1[3] = { 1.0f, 1.5f, 2.0f };
    float const array2[3] = { 1.01f, 1.51f, 2.01f };
    CheckArrayClose(results, array1, array2, 3, 0.001f, details);

    CHECK_EQUAL(UNITTEST_TEXT("arrayCloseTest"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("arrayCloseSuite"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("file"), reporter.lastFailedFile);
    CHECK_EQUAL(1337, reporter.lastFailedLine);
}


TEST(CheckArray2DCloseTrue)
{
    TestResults results;

    float const array1[3][3] = { { 1.0f, 1.5f, 2.0f },
                                 { 2.0f, 2.5f, 3.0f },
                                 { 3.0f, 3.5f, 4.0f } };
    float const array2[3][3] = { { 1.01f, 1.51f, 2.01f },
                                 { 2.01f, 2.51f, 3.01f },
                                 { 3.01f, 3.51f, 4.01f } };
    CheckArray2DClose(results, array1, array2, 3, 3, 0.02f, EmptyTestDetails());
    CHECK_EQUAL(0, results.GetFailureCount());
}

TEST(CheckArray2DCloseFalse)
{
    TestResults results;

    float const array1[3][3] = { { 1.0f, 1.5f, 2.0f },
                                 { 2.0f, 2.5f, 3.0f },
                                 { 3.0f, 3.5f, 4.0f } };
    float const array2[3][3] = { { 1.01f, 1.51f, 2.01f },
                                 { 2.01f, 2.51f, 3.01f },
                                 { 3.01f, 3.51f, 4.01f } };
    CheckArray2DClose(results, array1, array2, 3, 3, 0.001f, EmptyTestDetails());
    CHECK_EQUAL(1, results.GetFailureCount());
}

TEST(CheckCloseWithDoublesSucceeds)
{
    CHECK_CLOSE(0.5, 0.5, 0.0001);
}

TEST(CheckArray2DCloseFailureIncludesDetails)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails const details(
        UNITTEST_TEXT("array2DCloseTest"),
        UNITTEST_TEXT("array2DCloseSuite"),
        UNITTEST_TEXT("file"),
        1234);

    float const array1[3][3] = { { 1.0f, 1.5f, 2.0f },
                                 { 2.0f, 2.5f, 3.0f },
                                 { 3.0f, 3.5f, 4.0f } };
    float const array2[3][3] = { { 1.01f, 1.51f, 2.01f },
                                 { 2.01f, 2.51f, 3.01f },
                                 { 3.01f, 3.51f, 4.01f } };
    CheckArray2DClose(results, array1, array2, 3, 3, 0.001f, details);

    CHECK_EQUAL(UNITTEST_TEXT("array2DCloseTest"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("array2DCloseSuite"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("file"), reporter.lastFailedFile);
    CHECK_EQUAL(1234, reporter.lastFailedLine);
}

}
