#ifndef UNITTEST_TEST_H
#define UNITTEST_TEST_H

#include "TestDetails.h"

namespace UnitTest {

class TestResults;
class TestList;

class Test
{
public:
    explicit Test(Char const* testName, Char const* suiteName = UNITTEST_TEXT("DefaultSuite"), Char const* filename = UNITTEST_TEXT(""), int lineNumber = 0);
    virtual ~Test();
    void Run();

    TestDetails const m_details;
    Test* next;
    mutable bool m_timeConstraintExempt;

    static TestList& GetTestList();

    virtual void RunImpl() const;

private:
	Test(Test const&);
    Test& operator =(Test const&);
};


}

#endif
