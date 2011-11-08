#include "../UnitTest++.h"
#include "../TestList.h"

using namespace UnitTest;

namespace {


TEST (TestListIsEmptyByDefault)
{
    TestList list;
    CHECK (list.GetHead() == 0);
}

TEST (AddingTestSetsHeadToTest)
{
    Test test(UNITTEST_TEXT("test"));
    TestList list;
    list.Add(&test);

    CHECK (list.GetHead() == &test);
    CHECK (test.next == 0);
}

TEST (AddingSecondTestAddsItToEndOfList)
{
    Test test1(UNITTEST_TEXT("test1"));
    Test test2(UNITTEST_TEXT("test2"));

    TestList list;
    list.Add(&test1);
    list.Add(&test2);

    CHECK (list.GetHead() == &test1);
    CHECK (test1.next == &test2);
    CHECK (test2.next == 0);
}

TEST (ListAdderAddsTestToList)
{
    TestList list;

    Test test(UNITTEST_TEXT(""));    
    ListAdder adder(list, &test);

    CHECK (list.GetHead() == &test);
    CHECK (test.next == 0);
}

}
