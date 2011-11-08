#include "AssertException.h"
#include <sstream>

namespace UnitTest {

AssertException::AssertException(Char const* description, Char const* filename, int lineNumber)
    : m_lineNumber(lineNumber)
{
    Strings::StrCpy(m_description, description);
    Strings::StrCpy(m_filename, filename);
}

AssertException::~AssertException() throw()
{
}

Char const* AssertException::What() const throw()
{
    return m_description;
}

Char const* AssertException::Filename() const throw()
{
    return m_filename;
}

int AssertException::LineNumber() const throw()
{
    return m_lineNumber;
}

}
