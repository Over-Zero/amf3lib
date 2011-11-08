#include "../UnitTest++.h"
#include "../CurrentTest.h"
#include "RecordingReporter.h"
#include "ScopedCurrentTest.h"

namespace {

TEST(CheckSucceedsOnTrue)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);

        ScopedCurrentTest scopedResults(testResults);
        CHECK(true);

        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(!failure);
}

TEST(CheckFailsOnFalse)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK(false);
        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(FailureReportsCorrectTestName)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK(false);
    }

    CHECK_EQUAL(m_details.testName, reporter.lastFailedTest);
}

TEST(CheckFailureIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        const bool yaddayadda = false;
        CHECK(yaddayadda);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("yaddayadda")));
}

int ThrowingFunction()
{
    throw "Doh";
}

TEST(CheckFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK(ThrowingFunction() == 1);
        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckFailureBecauseOfExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK(ThrowingFunction() == 1);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("ThrowingFunction() == 1")));
}

TEST(CheckEqualSucceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK_EQUAL(1, 1);
        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(!failure);
}

TEST(CheckEqualFailsOnNotEqual)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK_EQUAL(1, 2);
        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckEqualFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK_EQUAL(ThrowingFunction(), 1);
        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckEqualFailureContainsCorrectDetails)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        UnitTest::TestDetails const testDetails(
            UNITTEST_TEXT("testName"),
            UNITTEST_TEXT("suiteName"),
            UNITTEST_TEXT("filename"),
            -1);
        ScopedCurrentTest scopedResults(testResults, &testDetails);

        CHECK_EQUAL(1, 123);    line = __LINE__;
    }

    CHECK_EQUAL(UNITTEST_TEXT("testName"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("suiteName"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("filename"), reporter.lastFailedFile);
    CHECK_EQUAL(line, reporter.lastFailedLine);
}

TEST(CheckEqualFailureBecauseOfExceptionContainsCorrectDetails)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        UnitTest::TestDetails const testDetails(
            UNITTEST_TEXT("testName"),
            UNITTEST_TEXT("suiteName"),
            UNITTEST_TEXT("filename"),
            -1);
        ScopedCurrentTest scopedResults(testResults, &testDetails);

        CHECK_EQUAL(ThrowingFunction(), 123);    line = __LINE__;
    }

    CHECK_EQUAL(UNITTEST_TEXT("testName"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("suiteName"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("filename"), reporter.lastFailedFile);
    CHECK_EQUAL(line, reporter.lastFailedLine);
}

TEST(CheckEqualFailureBecauseOfExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK_EQUAL(ThrowingFunction(), 123);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("ThrowingFunction()")));
    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("123")));
}

int g_sideEffect = 0;
int FunctionWithSideEffects()
{
    ++g_sideEffect;
    return 1;
}

TEST(CheckEqualDoesNotHaveSideEffectsWhenPassing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults;
        ScopedCurrentTest scopedResults(testResults);
        CHECK_EQUAL(1, FunctionWithSideEffects());
    }
    CHECK_EQUAL(1, g_sideEffect);
}

TEST(CheckEqualDoesNotHaveSideEffectsWhenFailing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults;
        ScopedCurrentTest scopedResults(testResults);
        CHECK_EQUAL(2, FunctionWithSideEffects());
    }
    CHECK_EQUAL(1, g_sideEffect);
}


TEST(CheckCloseSucceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK_CLOSE (1.0f, 1.001f, 0.01f);
        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(!failure);
}

TEST(CheckCloseFailsOnNotEqual)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK_CLOSE (1.0f, 1.1f, 0.01f);
        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckCloseFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK_CLOSE ((float)ThrowingFunction(), 1.0001f, 0.1f);
        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckCloseFailureContainsCorrectDetails)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        UnitTest::TestDetails testDetails(
            UNITTEST_TEXT("test"),
            UNITTEST_TEXT("suite"),
            UNITTEST_TEXT("filename"),
            -1);
        ScopedCurrentTest scopedResults(testResults, &testDetails);

        CHECK_CLOSE (1.0f, 1.1f, 0.01f);    line = __LINE__;
    }

    CHECK_EQUAL(UNITTEST_TEXT("test"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("suite"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("filename"), reporter.lastFailedFile);
    CHECK_EQUAL(line, reporter.lastFailedLine);
}

TEST(CheckCloseFailureBecauseOfExceptionContainsCorrectDetails)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        UnitTest::TestDetails testDetails(
            UNITTEST_TEXT("closeTest"),
            UNITTEST_TEXT("closeSuite"),
            UNITTEST_TEXT("filename"),
            -1);
        ScopedCurrentTest scopedResults(testResults, &testDetails);
        CHECK_CLOSE ((float)ThrowingFunction(), 1.0001f, 0.1f);    line = __LINE__;
    }

    CHECK_EQUAL(UNITTEST_TEXT("closeTest"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("closeSuite"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("filename"), reporter.lastFailedFile);
    CHECK_EQUAL(line, reporter.lastFailedLine);
}

TEST(CheckCloseFailureBecauseOfExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        CHECK_CLOSE ((float)ThrowingFunction(), 1.0001f, 0.1f);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("(float)ThrowingFunction()")));
    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("1.0001f")));
}

TEST(CheckCloseDoesNotHaveSideEffectsWhenPassing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults;
        ScopedCurrentTest scopedResults(testResults);
        CHECK_CLOSE (1, FunctionWithSideEffects(), 0.1f);
    }
    CHECK_EQUAL(1, g_sideEffect);
}

TEST(CheckCloseDoesNotHaveSideEffectsWhenFailing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults;
        ScopedCurrentTest scopedResults(testResults);
        CHECK_CLOSE (2, FunctionWithSideEffects(), 0.1f);
    }
    CHECK_EQUAL(1, g_sideEffect);
}


class ThrowingObject
{
public:
    float operator[](int) const
    {
        throw "Test throw";
    }
};


TEST(CheckArrayCloseSucceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);
        const float data[4] = { 0, 1, 2, 3 };
        CHECK_ARRAY_CLOSE (data, data, 4, 0.01f);
        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(!failure);
}

TEST(CheckArrayCloseFailsOnNotEqual)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        int const data1[4] = { 0, 1, 2, 3 };
        int const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 4, 0.01f);

        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckArrayCloseFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        int const data1[4] = { 0, 1, 2, 3 };
        int const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE(data1, data2, 4, 0.01f);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("xpected [ 0 1 2 3 ]")));
    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("was [ 0 1 3 3 ]")));
}

TEST(CheckArrayCloseFailureContainsCorrectDetails)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        UnitTest::TestDetails testDetails(
            UNITTEST_TEXT("arrayCloseTest"),
            UNITTEST_TEXT("arrayCloseSuite"),
            UNITTEST_TEXT("filename"),
            -1);
        ScopedCurrentTest scopedResults(testResults, &testDetails);

        int const data1[4] = { 0, 1, 2, 3 };
        int const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 4, 0.01f);     line = __LINE__;
    }

    CHECK_EQUAL(UNITTEST_TEXT("arrayCloseTest"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("arrayCloseSuite"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("filename"), reporter.lastFailedFile);
    CHECK_EQUAL(line, reporter.lastFailedLine);
}

TEST(CheckArrayCloseFailureBecauseOfExceptionContainsCorrectDetails)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        UnitTest::TestDetails testDetails(
            UNITTEST_TEXT("arrayCloseTest"),
            UNITTEST_TEXT("arrayCloseSuite"),
            UNITTEST_TEXT("filename"),
            -1);
        ScopedCurrentTest scopedResults(testResults, &testDetails);

        int const data[4] = { 0, 1, 2, 3 };
        CHECK_ARRAY_CLOSE (data, ThrowingObject(), 4, 0.01f);     line = __LINE__;
    }

    CHECK_EQUAL(UNITTEST_TEXT("arrayCloseTest"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("arrayCloseSuite"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("filename"), reporter.lastFailedFile);
    CHECK_EQUAL(line, reporter.lastFailedLine);
}

TEST(CheckArrayCloseFailureIncludesTolerance)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        float const data1[4] = { 0, 1, 2, 3 };
        float const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 4, 0.01f);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("0.01")));
}


TEST(CheckArrayCloseFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_CLOSE (data, obj, 3, 0.01f);

        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckArrayCloseFailureOnExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_CLOSE (data, obj, 3, 0.01f);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("data")));
    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("obj")));
}


TEST(CheckArrayEqualSuceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        const float data[4] = { 0, 1, 2, 3 };
        CHECK_ARRAY_EQUAL (data, data, 4);

        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(!failure);
}

TEST(CheckArrayEqualFailsOnNotEqual)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        int const data1[4] = { 0, 1, 2, 3 };
        int const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_EQUAL (data1, data2, 4);

        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckArrayEqualFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        int const data1[4] = { 0, 1, 2, 3 };
        int const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_EQUAL (data1, data2, 4);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("xpected [ 0 1 2 3 ]")));
    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("was [ 0 1 3 3 ]")));
}

TEST(CheckArrayEqualFailureContainsCorrectInfo)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        int const data1[4] = { 0, 1, 2, 3 };
        int const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_EQUAL (data1, data2, 4);     line = __LINE__;
    }

    CHECK_EQUAL(UNITTEST_TEXT("CheckArrayEqualFailureContainsCorrectInfo"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT(__FILE__), reporter.lastFailedFile);
    CHECK_EQUAL(line, reporter.lastFailedLine);
}

TEST(CheckArrayEqualFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_EQUAL (data, obj, 3);

        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckArrayEqualFailureOnExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_EQUAL (data, obj, 3);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("data")));
    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("obj")));
}

float const* FunctionWithSideEffects2()
{
    ++g_sideEffect;
    static float const data[] = {1,2,3,4};
    return data;
}

TEST(CheckArrayCloseDoesNotHaveSideEffectsWhenPassing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults;
        ScopedCurrentTest scopedResults(testResults);

        const float data[] = { 0, 1, 2, 3 };
        CHECK_ARRAY_CLOSE (data, FunctionWithSideEffects2(), 4, 0.01f);
    }
    CHECK_EQUAL(1, g_sideEffect);
}

TEST(CheckArrayCloseDoesNotHaveSideEffectsWhenFailing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults;
        ScopedCurrentTest scopedResults(testResults);

        const float data[] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data, FunctionWithSideEffects2(), 4, 0.01f);
    }

    CHECK_EQUAL(1, g_sideEffect);
}

class ThrowingObject2D
{
public:
    float* operator[](int) const
    {
        throw "Test throw";
    }
};


TEST(CheckArray2DCloseSucceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        const float data[2][2] = { {0, 1}, {2, 3} };
        CHECK_ARRAY2D_CLOSE (data, data, 2, 2, 0.01f);

        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(!failure);
}

TEST(CheckArray2DCloseFailsOnNotEqual)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        int const data1[2][2] = { {0, 1}, {2, 3} };
        int const data2[2][2] = { {0, 1}, {3, 3} };
        CHECK_ARRAY2D_CLOSE (data1, data2, 2, 2, 0.01f);

        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckArray2DCloseFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        int const data1[2][2] = { {0, 1}, {2, 3} };
        int const data2[2][2] = { {0, 1}, {3, 3} };

        CHECK_ARRAY2D_CLOSE (data1, data2, 2, 2, 0.01f);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("xpected [ [ 0 1 ] [ 2 3 ] ]")));
    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("was [ [ 0 1 ] [ 3 3 ] ]")));
}

TEST(CheckArray2DCloseFailureContainsCorrectDetails)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        UnitTest::TestDetails testDetails(
            UNITTEST_TEXT("array2DCloseTest"),
            UNITTEST_TEXT("array2DCloseSuite"),
            UNITTEST_TEXT("filename"),
            -1);
        ScopedCurrentTest scopedResults(testResults, &testDetails);

        int const data1[2][2] = { {0, 1}, {2, 3} };
        int const data2[2][2] = { {0, 1}, {3, 3} };
        CHECK_ARRAY2D_CLOSE (data1, data2, 2, 2, 0.01f);     line = __LINE__;
    }

    CHECK_EQUAL(UNITTEST_TEXT("array2DCloseTest"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("array2DCloseSuite"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("filename"), reporter.lastFailedFile);
    CHECK_EQUAL(line, reporter.lastFailedLine);
}

TEST(CheckArray2DCloseFailureBecauseOfExceptionContainsCorrectDetails)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        UnitTest::TestDetails testDetails(
            UNITTEST_TEXT("array2DCloseTest"),
            UNITTEST_TEXT("array2DCloseSuite"),
            UNITTEST_TEXT("filename"),
            -1);
        ScopedCurrentTest scopedResults(testResults, &testDetails);

        const float data[2][2] = { {0, 1}, {2, 3} };
        CHECK_ARRAY2D_CLOSE (data, ThrowingObject2D(), 2, 2, 0.01f);   line = __LINE__;
    }

    CHECK_EQUAL(UNITTEST_TEXT("array2DCloseTest"), reporter.lastFailedTest);
    CHECK_EQUAL(UNITTEST_TEXT("array2DCloseSuite"), reporter.lastFailedSuite);
    CHECK_EQUAL(UNITTEST_TEXT("filename"), reporter.lastFailedFile);
    CHECK_EQUAL(line, reporter.lastFailedLine);
}

TEST(CheckArray2DCloseFailureIncludesTolerance)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        float const data1[2][2] = { {0, 1}, {2, 3} };
        float const data2[2][2] = { {0, 1}, {3, 3} };
        CHECK_ARRAY2D_CLOSE (data1, data2, 2, 2, 0.01f);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("0.01")));
}

TEST(CheckArray2DCloseFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        const float data[2][2] = { {0, 1}, {2, 3} };
        ThrowingObject2D obj;
        CHECK_ARRAY2D_CLOSE (data, obj, 2, 2, 0.01f);

        failure = (testResults.GetFailureCount() > 0);
    }

    CHECK(failure);
}

TEST(CheckArray2DCloseFailureOnExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults(&reporter);
        ScopedCurrentTest scopedResults(testResults);

        const float data[2][2] = { {0, 1}, {2, 3} };
        ThrowingObject2D obj;
        CHECK_ARRAY2D_CLOSE (data, obj, 2, 2, 0.01f);
    }

    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("data")));
    CHECK(UnitTest::Strings::StrStr(reporter.lastFailedMessage,
        UNITTEST_TEXT("obj")));
}

float const* const* FunctionWithSideEffects3()
{
    ++g_sideEffect;
    static float const data1[] = {0,1};
    static float const data2[] = {2,3};
    static const float* const data[] = {data1, data2};
    return data;
}

TEST(CheckArray2DCloseDoesNotHaveSideEffectsWhenPassing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults;
        ScopedCurrentTest scopedResults(testResults);

        const float data[2][2] = { {0, 1}, {2, 3} };
        CHECK_ARRAY2D_CLOSE (data, FunctionWithSideEffects3(), 2, 2, 0.01f);
    }
    CHECK_EQUAL(1, g_sideEffect);
}

TEST(CheckArray2DCloseDoesNotHaveSideEffectsWhenFailing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults;
        ScopedCurrentTest scopedResults(testResults);

        const float data[2][2] = { {0, 1}, {3, 3} };
        CHECK_ARRAY2D_CLOSE (data, FunctionWithSideEffects3(), 2, 2, 0.01f);
    }
    CHECK_EQUAL(1, g_sideEffect);
}

}
