#include "../UnitTest++.h"
#include "../AssertException.h"
#include "../ReportAssert.h"

using namespace UnitTest;

namespace {

TEST(ReportAssertThrowsAssertException)
{
    bool caught = false;

    try
    {
        ReportAssert(UNITTEST_TEXT(""), UNITTEST_TEXT(""), 0);
    }
    catch (AssertException const&)
    {
        caught = true;
    }

    CHECK(true == caught);
}

TEST(ReportAssertSetsCorrectInfoInException)
{
    const int lineNumber = 12345;
    const Char* description = UNITTEST_TEXT("description");
    const Char* filename = UNITTEST_TEXT("filename");

    try
    {
        ReportAssert(description, filename, lineNumber);
    }
    catch (AssertException const& e)
    {
        CHECK_EQUAL(description, e.What());
        CHECK_EQUAL(filename, e.Filename());
        CHECK_EQUAL(lineNumber, e.LineNumber());
    }
}


}
