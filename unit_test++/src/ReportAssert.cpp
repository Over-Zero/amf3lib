#include "AssertException.h"

namespace UnitTest {

void ReportAssert(Char const* description, Char const* filename, int lineNumber)
{
    throw AssertException(description, filename, lineNumber);
}

}
