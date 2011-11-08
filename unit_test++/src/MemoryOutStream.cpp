#include "MemoryOutStream.h"

#ifndef UNITTEST_USE_CUSTOM_STREAMS


namespace UnitTest {

Char const* MemoryOutStream::GetText() const
{
    m_text = this->str();
    return m_text.c_str();
}


}


#else

#include <cstdio>

namespace UnitTest {

namespace {

    template<typename ValueType>
    void FormatToStream(MemoryOutStream& stream, Char const* format, ValueType const& value)
    {
        Char txt[32];
#ifdef _UNICODE
        swprintf(txt, format, value);
#else
        sprintf(txt, format, value);
#endif
        stream << txt;
    }

    int RoundUpToMultipleOfPow2Number (int n, int pow2Number)
    {
        return (n + (pow2Number - 1)) & ~(pow2Number - 1);
    }

}


MemoryOutStream::MemoryOutStream(int const size)
    : m_capacity (0)
    , m_buffer (0)

{
    GrowBuffer(size);
}

MemoryOutStream::~MemoryOutStream()
{
    delete [] m_buffer;
}

Char const* MemoryOutStream::GetText() const
{
    return m_buffer;
}

MemoryOutStream& MemoryOutStream::operator << (Char const* txt)
{
    int const bytesLeft = m_capacity - (int)Strings::StrLen(m_buffer);
    int const bytesRequired = (int)Strings::StrLen(txt) + 1;

    if (bytesRequired > bytesLeft)
    {
        int const requiredCapacity = bytesRequired + m_capacity - bytesLeft;
        GrowBuffer(requiredCapacity);
    }

    Strings::StrCat(m_buffer, txt);
    return *this;
}

MemoryOutStream& MemoryOutStream::operator << (int const n)
{
    FormatToStream(*this, UNITTEST_TEXT("%i"), n);
    return *this;
}

MemoryOutStream& MemoryOutStream::operator << (long const n)
{
    FormatToStream(*this, UNITTEST_TEXT("%li"), n);
    return *this;
}

MemoryOutStream& MemoryOutStream::operator << (unsigned long const n)
{
    FormatToStream(*this, UNITTEST_TEXT("%lu"), n);
    return *this;
}

MemoryOutStream& MemoryOutStream::operator << (float const f)
{
    FormatToStream(*this, UNITTEST_TEXT("%ff"), f);
    return *this;    
}

MemoryOutStream& MemoryOutStream::operator << (void const* p)
{
    FormatToStream(*this, UNITTEST_TEXT("%p"), p);
    return *this;    
}

MemoryOutStream& MemoryOutStream::operator << (unsigned int const s)
{
    FormatToStream(*this, UNITTEST_TEXT("%u"), s);
    return *this;    
}

MemoryOutStream& MemoryOutStream::operator <<(double const d)
{
    FormatToStream(*this, UNITTEST_TEXT("%f"), d);
    return *this;
}

MemoryOutStream& MemoryOutStream::operator << (const String& txt)
{
    *this << txt.c_str();
    return *this;
}

int MemoryOutStream::GetCapacity() const
{
    return m_capacity;
}


void MemoryOutStream::GrowBuffer(int const desiredCapacity)
{
    int const newCapacity = RoundUpToMultipleOfPow2Number(desiredCapacity, GROW_CHUNK_SIZE);

    Char* buffer = new Char[newCapacity];
    if (m_buffer)
        Strings::StrCpy(buffer, m_buffer);
    else
        Strings::StrCpy(buffer, UNITTEST_TEXT(""));

    delete [] m_buffer;
    m_buffer = buffer;
    m_capacity = newCapacity;
}

}


#endif
