#ifndef UNITTEST_ASSERTEXCEPTION_H
#define UNITTEST_ASSERTEXCEPTION_H

#include "Strings.h"


namespace UnitTest {

class AssertException
{
public:
    AssertException(Char const* description, Char const* filename, int lineNumber);
    virtual ~AssertException() throw();

    Char const* What() const throw();
    Char const* Filename() const throw();
    int LineNumber() const throw();

private:
    Char m_description[512];
    Char m_filename[256];
    int m_lineNumber;
};

}

#endif
